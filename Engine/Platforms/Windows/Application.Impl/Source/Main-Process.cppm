/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <cassert>

#include "PonyEngine/Log/Log.h"
#include "PonyEngine/Macro/Text.h"

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#include <avrt.h>
#include <KnownFolders.h>

export module PonyEngine.Application.Impl.Windows:Process;

import std;

import PonyEngine.Application.Impl;
import PonyEngine.Chrono;
import PonyEngine.FileSystem.WinAPI;
import PonyEngine.Log;

import :ThreadRole;

export namespace PonyEngine::Application
{
	/// @brief Windows process.
	class Process : private IProcess
	{
	public:
		Process(const Process&) = delete;
		Process(Process&&) = delete;

		virtual ~Process() noexcept = default;

		/// @brief Runs the process.
		/// @return Exit code.
		[[nodiscard("Must be returned from main")]]
		int Run();

		Process& operator =(const Process&) = delete;
		Process& operator =(Process&&) = delete;

	protected:
		/// @brief Creates a process.
		/// @param commandLine Command line.
		[[nodiscard("Pure constructor")]]
		explicit Process(std::span<const std::string_view> commandLine);

		/// @brief Creates and/or sets up a console.
		virtual void CreateConsole() noexcept {}
		/// @brief Destroys a console.
		virtual void DestroyConsole() noexcept {}

		/// @brief Adds the process interfaces to the application.
		virtual void AddProcessInterfaces() {}
		/// @brief Removes the process interfaces from the application.
		virtual void RemoveProcessInterfaces() {}

		/// @brief Ticks the platform.
		/// @return Exit code or nullopt if the process shouldn't exit.
		[[nodiscard("Must be used")]]
		virtual void TickPlatform() = 0;

		/// @brief Gets the application.
		/// @return Application.
		[[nodiscard("Pure function")]]
		App& Application() const noexcept;

	private:
		[[nodiscard("Pure function")]] 
		virtual std::thread CreateThread(std::move_only_function<void()> func, const ThreadParams& params) override final;

		/// @brief Gets a list of thread roles.
		/// @return Thread roles.
		[[nodiscard("Pure function")]]
		static std::vector<std::string_view> GetThreadRoles();

		/// @brief Gets a path to the executable.
		/// @return Path to the executable.
		[[nodiscard("Pure function")]]
		static std::filesystem::path GetExecutablePath();
		/// @brief Gets a path to the project local data directory.
		/// @return Path to the project local data directory.
		[[nodiscard("Pure function")]]
		static std::filesystem::path GetLocalDataDirectory();
		/// @brief Gets a path to the project user data directory.
		/// @return Path to the project user data directory.
		[[nodiscard("Pure function")]]
		static std::filesystem::path GetUserDataDirectory();
		/// @brief Gets a path to the project temp data directory.
		/// @return Path to the project temp data directory.
		[[nodiscard("Pure function")]]
		static std::filesystem::path GetTempDataDirectory();

		/// @brief Sets this process priority.
		void SetProcessPriority() const noexcept;

		/// @brief Finds a thread role.
		/// @param role Thread role name. Empty means no role.
		/// @return Thread role. Nullptr if the @p role is empty.
		[[nodiscard("Pure function")]]
		static const ThreadRole* FindThreadRole(std::string_view role);
		/// @brief Sets the thread role.
		/// @param thread Target thread.
		/// @param role Role to set.
		/// @param logService Log service.
		/// @return MMCSS handle. May be nullptr. If it's not nullptr, you must call @p RevertMmcss on the caller thread before setting another role or thread destruction.
		[[nodiscard("Must be used")]]
		static HANDLE SetThreadRole(HANDLE thread, const ThreadRole& role, const Log::ILogService* logService) noexcept;
		/// @brief Reverts the mmcss task.
		/// @param mmcssHandle MMCSS handle. May be nullptr. In this case, the function does nothing.
		/// @param logService Log service.
		static void RevertMmcss(HANDLE mmcssHandle, const Log::ILogService* logService) noexcept;

		/// @brief Initializes the application.
		void Initialize();
		/// @brief Finalizes the application.
		void Finalize();
		/// @brief Runs the main loop.
		/// @return Exit code.
		[[nodiscard("Pure function")]]
		int RunMainLoop();

		/// @brief Logs basic info.
		void LogProcessBasicInfo() const noexcept;

		/// @brief Sets the main thread role.
		void SetMainThreadRole();
		/// @brief Reverts the main thread mmcss if it's set.
		void RevertMainThreadMmcss() noexcept;

		/// @brief Creates a main loop timer.
		void CreateMainLoopTimer() noexcept;
		/// @brief Destroys a main loop timer.
		void DestroyMainLoopTimer() noexcept;
		/// @brief Waits for the next frame to start.
		void WaitForNextFrame() const noexcept;

		HANDLE mainThreadMmcss; ///< Main thread mmcss.
		HANDLE mainThreadTimer; ///< Main loop timer handle.

		std::unique_ptr<App> application; ///< Application.
	};
}

namespace PonyEngine::Application
{
	Process::Process(const std::span<const std::string_view> commandLine) :
		mainThreadMmcss{nullptr},
		mainThreadTimer{nullptr},
		application(std::make_unique<App>(commandLine, GetThreadRoles(), GetExecutablePath(), GetLocalDataDirectory(), GetUserDataDirectory(), GetTempDataDirectory(), 
			static_cast<IProcess&>(*this)))
	{
	}

	int Process::Run()
	{
		assert(std::this_thread::get_id() == application->MainThreadID() && "Wrong thread.");

		int exitCode;

		Initialize();

		try
		{
			exitCode = RunMainLoop();
		}
		catch (...)
		{
			Finalize();
			throw;
		}

		Finalize();

		return exitCode;
	}

	App& Process::Application() const noexcept
	{
		return *application;
	}

	std::thread Process::CreateThread(std::move_only_function<void()> func, const ThreadParams& params)
	{
		const ThreadRole* const threadRole = FindThreadRole(params.role);
		if (!threadRole)
		{
			return std::thread(std::move(func));
		}

		return std::thread([f = std::move(func), tr = threadRole, ls = params.logService]() mutable
		{
			const HANDLE mmcssHandle = SetThreadRole(GetCurrentThread(), *tr, ls);
			f();
			RevertMmcss(mmcssHandle, ls);
		});
	}

	std::vector<std::string_view> Process::GetThreadRoles()
	{
		constexpr auto roleView = std::views::keys(ThreadRoles);
		return std::vector<std::string_view>(roleView.cbegin(), roleView.cend());
	}

	std::filesystem::path Process::GetExecutablePath()
	{
		return FileSystem::GetModulePath(nullptr).lexically_normal();
	}

	std::filesystem::path Process::GetLocalDataDirectory()
	{
		return AddTail(FileSystem::GetKnownPath(FOLDERID_LocalAppData));
	}

	std::filesystem::path Process::GetUserDataDirectory()
	{
		return AddTail(FileSystem::GetKnownPath(FOLDERID_SavedGames));
	}

	std::filesystem::path Process::GetTempDataDirectory()
	{
		return AddTail(FileSystem::GetTemporaryPath());
	}

	void Process::SetProcessPriority() const noexcept
	{
		PONY_LOG(application->LogService(), Log::LogType::Info, "Setting process priority. Priority: '{}'.", PONY_ENGINE_APPLICATION_PROCESS_PRIORITY);
		if (!SetPriorityClass(GetCurrentProcess(), PONY_ENGINE_APPLICATION_PROCESS_PRIORITY)) [[unlikely]]
		{
			PONY_LOG(application->LogService(), Log::LogType::Error, std::current_exception(), "Failed to set process priority. ErrorCode: '0x{:X}'.", GetLastError());
		}
	}

	const ThreadRole* Process::FindThreadRole(const std::string_view role)
	{
		if (role.empty())
		{
			return nullptr;
		}

		const auto roleDesc = ThreadRoles.find(role);
		if (roleDesc == ThreadRoles.cend()) [[unlikely]]
		{
			throw std::invalid_argument("Invalid role");
		}

		return &roleDesc->second;
	}

	HANDLE Process::SetThreadRole(const HANDLE thread, const ThreadRole& role, const Log::ILogService* const logService) noexcept
	{
		PONY_LOG(logService, Log::LogType::Info, "Setting thread role. ThreadID: '{}'; Priority: '0x{:X}'; MMCSS task name: '{}'; MMCSS priority: {}.", 
			GetThreadId(thread), role.threadPriority, role.mmcssTask, std::to_underlying(role.mmcssPriority));

		if (!SetThreadPriority(thread, role.threadPriority)) [[unlikely]]
		{
			PONY_LOG(logService, Log::LogType::Error, "Failed to set thread priority. Priority: '0x{:X}'; Error code: '0x{:X}'.", role.threadPriority, GetLastError());
		}

		if (role.mmcssTask.empty())
		{
			return nullptr;
		}

		DWORD index = 0;
		const HANDLE mmcssHandle = AvSetMmThreadCharacteristicsA(role.mmcssTask.data(), &index);
		if (!mmcssHandle) [[unlikely]]
		{
			PONY_LOG(logService, Log::LogType::Error, "Failed to set mmcss thread task. Task: '{}'; Error code: '0x{:X}'.", role.mmcssTask, GetLastError());
			return nullptr;
		}
		PONY_LOG(logService, Log::LogType::Info, "MMCSS task set to thread. ThreadID: '{}'; Task handle: '0x{:X}'.", 
			GetThreadId(thread), reinterpret_cast<std::uintptr_t>(mmcssHandle));

		if (!AvSetMmThreadPriority(mmcssHandle, role.mmcssPriority)) [[unlikely]]
		{
			PONY_LOG(logService, Log::LogType::Error, "Failed to set mmcss thread priority. Task: '{}'; Priority: '{}'; Error code: '0x{:X}'.", 
				role.mmcssTask, std::to_underlying(role.mmcssPriority), GetLastError());
		}

		return mmcssHandle;
	}

	void Process::RevertMmcss(const HANDLE mmcssHandle, const Log::ILogService* const logService) noexcept
	{
		if (mmcssHandle)
		{
			PONY_LOG(logService, Log::LogType::Info, "Reverting thread MMCSS task. Task handle: '0x{:X}'.", reinterpret_cast<std::uintptr_t>(mmcssHandle));

			if (!AvRevertMmThreadCharacteristics(mmcssHandle)) [[unlikely]]
			{
				PONY_LOG(logService, Log::LogType::Error, "Failed to revert mmcss task. Error code: '0x{:X}'.", GetLastError());
			}
		}
	}

	void Process::Initialize()
	{
		application->InitializeEarly();
		CreateConsole();
		LogProcessBasicInfo();
		SetProcessPriority();
		try
		{
			SetMainThreadRole();
			CreateMainLoopTimer();
			try
			{
				AddProcessInterfaces();
				try
				{
					application->InitializeNormal();
					try
					{
						application->InitializeLate();
					}
					catch (...)
					{
						application->FinalizeNormal();
						throw;
					}
				}
				catch (...)
				{
					RemoveProcessInterfaces();
					throw;
				}
			}
			catch (...)
			{
				DestroyMainLoopTimer();
				RevertMainThreadMmcss();
				throw;
			}
		}
		catch (...)
		{
			DestroyConsole();
			application->FinalizeEarly();
			throw;
		}
	}

	void Process::Finalize()
	{
		application->FinalizeLate();
		application->FinalizeNormal();
		RemoveProcessInterfaces();
		DestroyMainLoopTimer();
		RevertMainThreadMmcss();
		DestroyConsole();
		application->FinalizeEarly();
	}

	int Process::RunMainLoop()
	{
		std::optional<int> exitCode;

		application->Begin();

		try
		{
			do
			{
				WaitForNextFrame();
				application->BeginFrame();
				TickPlatform();
				application->Tick();
				application->EndFrame();
				exitCode = application->ExitCode();
			} while (!exitCode);
		}
		catch (...)
		{
			application->End();
			throw;
		}

		application->End();

		return *exitCode;
	}

	void Process::LogProcessBasicInfo() const noexcept
	{
		application->LogBasicInfo();
		PONY_LOG(application->LogService(), Log::LogType::Info, "PID: '{}'.", GetCurrentProcessId());
	}

	void Process::SetMainThreadRole()
	{
		constexpr std::string_view mainThreadRole = PONY_STRINGIFY_VALUE(PONY_ENGINE_APPLICATION_MAIN_THREAD_ROLE);

		PONY_LOG(application->LogService(), Log::LogType::Info, "Setting main thread role. Role: '{}'.", mainThreadRole);
		try
		{
			const ThreadRole* const role = FindThreadRole(mainThreadRole);
			mainThreadMmcss = role ? SetThreadRole(GetCurrentThread(), *role, application->LogService()) : nullptr;
		}
		catch (...)
		{
			PONY_LOG(application->LogService(), Log::LogType::Error, std::current_exception(), "On setting main thread role.");
			throw;
		}
	}

	void Process::RevertMainThreadMmcss() noexcept
	{
		if (mainThreadMmcss)
		{
			PONY_LOG(application->LogService(), Log::LogType::Info, "Reverting main thread mmcss.");
			RevertMmcss(mainThreadMmcss, application->LogService());
			mainThreadMmcss = nullptr;
		}
	}

	void Process::CreateMainLoopTimer() noexcept
	{
		PONY_LOG(application->LogService(), Log::LogType::Info, "Creating main loop timer.");

		mainThreadTimer = CreateWaitableTimerExA(nullptr, nullptr, CREATE_WAITABLE_TIMER_HIGH_RESOLUTION, TIMER_MODIFY_STATE | SYNCHRONIZE);
		if (!mainThreadTimer) [[unlikely]]
		{
			PONY_LOG(application->LogService(), Log::LogType::Error, "Failed to create main loop timer. Error code: '0x{:X}'.", GetLastError());
		}
	}

	void Process::DestroyMainLoopTimer() noexcept
	{
		if (mainThreadTimer) [[likely]]
		{
			PONY_LOG(application->LogService(), Log::LogType::Info, "Destroying main loop timer.");

			if (!CloseHandle(mainThreadTimer)) [[unlikely]]
			{
				PONY_LOG(application->LogService(), Log::LogType::Error, "Failed to destroy main loop timer. Error code: '0x{:X}'.", GetLastError());
			}

			mainThreadTimer = nullptr;
		}
	}

	void Process::WaitForNextFrame() const noexcept
	{
		if (!mainThreadTimer) [[unlikely]]
		{
			return;
		}

		constexpr std::chrono::nanoseconds busySpinLength = Chrono::ToDuration<std::chrono::nanoseconds>(double{PONY_ENGINE_APPLICATION_NEXT_FRAME_BUSY_SPIN_LENGTH});
		const std::chrono::time_point<std::chrono::steady_clock> nextFrameTimePoint = application->NextFrameTimePoint();
		const std::chrono::time_point<std::chrono::steady_clock> waitTill = nextFrameTimePoint - busySpinLength;
		const std::chrono::nanoseconds waitLength = std::chrono::duration_cast<std::chrono::nanoseconds>(waitTill - std::chrono::steady_clock::now());
		const auto waitTime = LARGE_INTEGER{.QuadPart = -waitLength.count() / 100ll};
		if (waitTime.QuadPart >= 0ll)
		{
			return;
		}

		if (!SetWaitableTimer(mainThreadTimer, &waitTime, 0, nullptr, nullptr, FALSE)) [[unlikely]]
		{
			PONY_LOG(application->LogService(), Log::LogType::Error, "Failed to set a high resolution waitable timer. Error code: '0x{:X}'.", GetLastError());
		}
		if (const DWORD result = WaitForSingleObject(mainThreadTimer, INFINITE); result != WAIT_OBJECT_0) [[unlikely]]
		{
			if (result == WAIT_FAILED)
			{
				PONY_LOG(application->LogService(), Log::LogType::Error, "Failed to wait for a high resolution waitable timer. Error code: '0x{:X}'.", GetLastError());
			}
			else
			{
				PONY_LOG(application->LogService(), Log::LogType::Error, "Failed to wait for a high resolution waitable timer. Result: '0x{:X}'.", result);
			}
		}
	}
}
