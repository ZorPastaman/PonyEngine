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

export module PonyEngine.Application.Impl.WinAPI:Process;

import std;

import PonyEngine.Application.Impl;
import PonyEngine.FileSystem.WinAPI;
import PonyEngine.Log;
import PonyEngine.Utility;

import :Sleeper;
import :ThreadHelper;

export namespace PonyEngine::Application
{
	/// @brief Windows process.
	class Process : private IProcess
	{
	public:
		Process(const Process&) = delete;
		Process(Process&&) = delete;

		virtual ~Process() noexcept;

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
		virtual Application::ProcessID ProcessID() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual MemoryStatus GetMemoryStatus() const override;

		[[nodiscard("Pure function")]]
		virtual std::string GetThreadRoleLog(std::string_view role) const override;
		[[nodiscard("Pure function")]] 
		virtual std::thread CreateThread(std::move_only_function<void()> func, ThreadParams params) override final;

		[[nodiscard("Pure function")]] 
		virtual std::shared_ptr<ISleeper> CreateSleeper() override;

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

		/// @brief Initializes the application.
		void Initialize();
		/// @brief Finalizes the application.
		void Finalize();
		/// @brief Runs the main loop.
		/// @return Exit code.
		[[nodiscard("Pure function")]]
		int RunMainLoop();

		/// @brief Sets the main thread role.
		void SetMainThreadRole();
		/// @brief Reverts the main thread mmcss if it's set.
		void RevertMainThreadMmcss() noexcept;

		HANDLE mainThreadMmcss; ///< Main thread mmcss.
		std::unique_ptr<App> application; ///< Application.

#ifndef NDEBUG
		std::atomic_size_t sleeperCount; ///< Sleeper count.
#endif
	};
}

namespace PonyEngine::Application
{
	Process::Process(const std::span<const std::string_view> commandLine) :
		mainThreadMmcss{nullptr},
		application(std::make_unique<App>(commandLine, GetThreadRoles(), GetExecutablePath(), GetLocalDataDirectory(), GetUserDataDirectory(), GetTempDataDirectory(), 
			static_cast<IProcess&>(*this)))
	{
	}

	Process::~Process() noexcept
	{
#ifndef NDEBUG
		assert(sleeperCount.load(std::memory_order::relaxed) == 0uz && "Some sleepers weren't destroyed.");
#endif
	}

	int Process::Run()
	{
		assert(std::this_thread::get_id() == application->MainThreadID() && "Wrong thread.");

		Initialize();
		const auto finalizeGuard = Utility::ScopeGuard([&]() noexcept { Finalize(); });
		return RunMainLoop();
	}

	App& Process::Application() const noexcept
	{
		return *application;
	}

	Application::ProcessID Process::ProcessID() const noexcept
	{
		return GetCurrentProcessId();
	}

	MemoryStatus Process::GetMemoryStatus() const
	{
		auto memoryStatus = MEMORYSTATUSEX{.dwLength = sizeof(MEMORYSTATUSEX)};
		if (!GlobalMemoryStatusEx(&memoryStatus)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to get memory status: Error code = '0x{:X}'", GetLastError()));
		}

		return MemoryStatus
		{
			.physicalMemory = MemoryInfo{.total = memoryStatus.ullTotalPhys, .available = memoryStatus.ullAvailPhys},
			.commitMemory = MemoryInfo{.total = memoryStatus.ullTotalPageFile, .available = memoryStatus.ullAvailPageFile},
			.virtualMemory = MemoryInfo{.total = memoryStatus.ullTotalVirtual, .available = memoryStatus.ullAvailVirtual}
		};
	}

	std::string Process::GetThreadRoleLog(const std::string_view role) const
	{
		return Application::GetThreadRoleLog(GetThreadRoleIndex(role));
	}

	std::thread Process::CreateThread(std::move_only_function<void()> func, ThreadParams params)
	{
		if (!params.role.empty())
		{
			return std::thread(std::move(func));
		}

		return std::thread([f = std::move(func), beginError = std::move(params.onBeginException), endError = std::move(params.onEndException), 
			roleIndex = GetThreadRoleIndex(params.role)]() mutable
		{
			HANDLE mmcssHandle = nullptr;
			bool execute = true;

			try
			{
				const HANDLE threadHandle = GetCurrentThread();
				SetThreadPriority(threadHandle, roleIndex);
				mmcssHandle = SetThreadMMCSS(threadHandle, roleIndex);
				if (mmcssHandle)
				{
					SetThreadMMCSSPriority(mmcssHandle, roleIndex);
				}
			}
			catch (...)
			{
				if (beginError)
				{
					execute = beginError(std::current_exception());
				}
			}

			if (execute) [[likely]]
			{
				f();
			}

			try
			{
				if (mmcssHandle)
				{
					RevertThreadMMCSS(mmcssHandle);
				}
			}
			catch (...)
			{
				if (endError)
				{
					endError(std::current_exception());
				}
			}
		});
	}

	std::shared_ptr<ISleeper> Process::CreateSleeper()
	{
#ifndef NDEBUG
		const auto sleeper = new Sleeper();
		sleeperCount.fetch_add(1uz, std::memory_order::relaxed);
		return std::shared_ptr<Sleeper>(sleeper, [this](const Sleeper* const sleeperToDestroy) noexcept
		{
			delete sleeperToDestroy;
			sleeperCount.fetch_sub(1uz, std::memory_order::relaxed);
		});
#else
		return std::make_shared<Sleeper>();
#endif
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

	void Process::Initialize()
	{
		auto scopeGuardFlag = Utility::ScopeGuardFlag();

		application->InitializeEarly();
		const auto initializeEarlyScopeGuard = Utility::ScopeGuard([&]() noexcept { application->FinalizeEarly(); }, scopeGuardFlag);
		CreateConsole();
		const auto consoleScopeGuard = Utility::ScopeGuard([&]() noexcept { DestroyConsole(); }, scopeGuardFlag);
		application->LogBasicInfo();
		SetProcessPriority();
		SetMainThreadRole();
		const auto mainThreadRoleScopeGuard = Utility::ScopeGuard([&]() noexcept { RevertMainThreadMmcss(); }, scopeGuardFlag);
		AddProcessInterfaces();
		const auto processInterfacesScopeGuard = Utility::ScopeGuard([&]() noexcept { RemoveProcessInterfaces(); }, scopeGuardFlag);
		application->InitializeNormal();
		const auto initializeNormalScopeGuard = Utility::ScopeGuard([&]() noexcept { application->FinalizeNormal(); }, scopeGuardFlag);
		application->InitializeLate();

		scopeGuardFlag.Release();
	}

	void Process::Finalize()
	{
		application->FinalizeLate();
		application->FinalizeNormal();
		RemoveProcessInterfaces();
		RevertMainThreadMmcss();
		DestroyConsole();
		application->FinalizeEarly();
	}

	int Process::RunMainLoop()
	{
		application->Begin();
		const auto endScopeGuard = Utility::ScopeGuard([&]() noexcept { application->End(); });

		std::optional<int> exitCode;
		do
		{
			application->BeginFrame();
			TickPlatform();
			application->Tick();
			application->EndFrame();
			exitCode = application->ExitCode();
		} while (!exitCode);

		return *exitCode;
	}

	void Process::SetMainThreadRole()
	{
		constexpr std::string_view mainThreadRole = PONY_STRINGIFY_VALUE(PONY_ENGINE_APPLICATION_MAIN_THREAD_ROLE);
		PONY_LOG(application->LogService(), Log::LogType::Info, "Setting main thread role. Role: '{}'.", mainThreadRole);

		if (mainThreadRole.empty())
		{
			return;
		}

		try
		{
			const HANDLE threadHandle = GetCurrentThread();
			const std::size_t roleIndex = GetThreadRoleIndex(mainThreadRole);
			SetThreadPriority(threadHandle, roleIndex);
			mainThreadMmcss = SetThreadMMCSS(threadHandle, roleIndex);
			if (mainThreadMmcss)
			{
				SetThreadMMCSSPriority(mainThreadMmcss, roleIndex);
			}
		}
		catch (...)
		{
			PONY_LOG(application->LogService(), Log::LogType::Error, std::current_exception(), "On setting main thread role.");
		}
	}

	void Process::RevertMainThreadMmcss() noexcept
	{
		if (mainThreadMmcss)
		{
			PONY_LOG(application->LogService(), Log::LogType::Info, "Reverting main thread mmcss.");
			try
			{
				RevertThreadMMCSS(mainThreadMmcss);
			}
			catch (...)
			{
				PONY_LOG(application->LogService(), Log::LogType::Error, std::current_exception(), "On reverting main thread MMCSS.");
			}
			mainThreadMmcss = nullptr;
		}
	}
}
