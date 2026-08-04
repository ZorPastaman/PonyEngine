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
#include <stdio.h>

#include "PonyEngine/Log/Log.h"
#include "PonyEngine/Platform/Windows/Framework.h"

export module PonyEngine.Application.Impl.Windows:GUIProcess;

#ifdef PONY_ENGINE_APPLICATION_MODE_GUI

import PonyEngine.Application.Impl;
import PonyEngine.Application.Windows;
import PonyEngine.Log;

import :CommandLine;
import :Path;
import :Process;
import :ThreadControl;
import :Timer;

export namespace PonyEngine::Application
{
	/// @brief GUI process.
	class GUIProcess final : private IProcess, private IMainData, private IMessagePump
	{
	public:
		/// @brief Creates a GUI process.
		/// @param hInstance Instance from WinMain().
		/// @param hPrevInstance Previous instance from WinMain().
		/// @param lpCmdLine Command line from WinMain().
		/// @param nShowCmd Show command from WinMain().
		[[nodiscard("Pure constructor")]]
		GUIProcess(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nShowCmd);
		GUIProcess(const GUIProcess&) = delete;
		GUIProcess(GUIProcess&&) = delete;

		~GUIProcess() noexcept = default;

		/// @brief Runs the process.
		/// @return Exit code.
		[[nodiscard("Must be returned from main")]]
		int Run();

		GUIProcess& operator =(const GUIProcess&) = delete;
		GUIProcess& operator =(GUIProcess&&) = delete;

	private:
		[[nodiscard("Pure function")]] 
		virtual std::shared_ptr<IThreadControl> CreateThreadControl(std::thread& thread) override;
		[[nodiscard("Pure function")]] 
		virtual std::string_view MainThreadRole() const noexcept override;
		virtual void MainThreadRole(std::string_view role) override;

		[[nodiscard("Pure function")]] 
		virtual HINSTANCE Instance() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual HINSTANCE PrevInstance() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual PSTR CommandLine() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual int ShowCommand() const noexcept override;

		[[nodiscard("Pure function")]] 
		virtual UINT LastMessageType() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual DWORD LastMessageNativeTimePoint() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual std::chrono::time_point<std::chrono::steady_clock> LastMessageTimePoint() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual POINT LastMessageCursorPoint() const noexcept override;

		/// @brief Initializes the application.
		void Initialize();
		/// @brief Finalizes the application.
		void Finalize();

		/// @brief Creates a console if needed.
		void CreateConsole() noexcept;
		/// @brief Destroys a console if it was created.
		void DestroyConsole() noexcept;

		/// @brief Adds the process interfaces to the application.
		void AddProcessInterfaces();
		/// @brief Removes the process interfaces from the application.
		void RemoveProcessInterfaces();

		/// @brief Runs the main loop.
		/// @return Exit code.
		[[nodiscard("Pure function")]]
		int RunMainLoop();
		/// @brief Ticks message pump.
		void TickMessagePump();
		/// @brief Update the message time.
		/// @param newMessageTime New message native time.
		void UpdateMessageTime(DWORD newMessageTime) noexcept;

		HINSTANCE instance; ///< Instance.
		HINSTANCE prevInstance; ///< Previous instance.
		PSTR cmdLine; ///< Command line.
		int showCmd; ///< Show command.

		bool hasConsole; ///< Does the process have a console?

		std::vector<std::string> commandLine; ///< Command line.

		std::chrono::time_point<std::chrono::steady_clock> lastMessageTime; ///< Time of a last message.
		DWORD lastMessageNativeTime; ///< Native time of a last message.
		UINT lastMessageType; ///< Type of a last message.
		POINT lastMessageCursorPoint; ///< Cursor point of a last message.

		std::unique_ptr<App> application; ///< Application.

		ThreadControl mainThreadControl; ///< Main thread control.
		HANDLE timer; ///< Timer handle.
	};
}

namespace PonyEngine::Application
{
	GUIProcess::GUIProcess(const HINSTANCE hInstance, const HINSTANCE hPrevInstance, const PSTR lpCmdLine, const int nShowCmd) :
		instance{hInstance},
		prevInstance{hPrevInstance},
		cmdLine{lpCmdLine},
		showCmd{nShowCmd},
		hasConsole{false},
		commandLine(MakeCommandLine()),
		lastMessageTime(std::chrono::steady_clock::now()),
		lastMessageNativeTime(GetTickCount()),
		lastMessageType{0u},
		lastMessageCursorPoint{.x = 0l, .y = 0l},
		mainThreadControl(GetCurrentThread()),
		timer{nullptr}
	{
		application = std::make_unique<App>(MakeCommandLineView(commandLine), GetThreadRoles(), GetExecutablePath(), GetLocalDataDirectory(), GetUserDataDirectory(), 
			GetTempDataDirectory(), static_cast<IProcess&>(*this));
	}

	int GUIProcess::Run()
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

	std::shared_ptr<IThreadControl> GUIProcess::CreateThreadControl(std::thread& thread)
	{
		return std::make_shared<ThreadControl>(thread);
	}

	std::string_view GUIProcess::MainThreadRole() const noexcept
	{
		return mainThreadControl.Role();
	}

	void GUIProcess::MainThreadRole(const std::string_view role)
	{
		mainThreadControl.Role(role);
	}

	HINSTANCE GUIProcess::Instance() const noexcept
	{
		return instance;
	}

	HINSTANCE GUIProcess::PrevInstance() const noexcept
	{
		return prevInstance;
	}

	PSTR GUIProcess::CommandLine() const noexcept
	{
		return cmdLine;
	}

	int GUIProcess::ShowCommand() const noexcept
	{
		return showCmd;
	}

	UINT GUIProcess::LastMessageType() const noexcept
	{
		assert(std::this_thread::get_id() == application->MainThreadID() && "Must be called on main thread");
		return lastMessageType;
	}

	DWORD GUIProcess::LastMessageNativeTimePoint() const noexcept
	{
		assert(std::this_thread::get_id() == application->MainThreadID() && "Must be called on main thread");
		return lastMessageNativeTime;
	}

	std::chrono::time_point<std::chrono::steady_clock> GUIProcess::LastMessageTimePoint() const noexcept
	{
		assert(std::this_thread::get_id() == application->MainThreadID() && "Must be called on main thread");
		return lastMessageTime;
	}

	POINT GUIProcess::LastMessageCursorPoint() const noexcept
	{
		assert(std::this_thread::get_id() == application->MainThreadID() && "Must be called on main thread");
		return lastMessageCursorPoint;
	}

	void GUIProcess::Initialize()
	{
		application->InitializeEarly();
		CreateConsole();
		application->LogBasicInfo();
		LogProcessBasicInfo(*application);
		SetProcessPriority(*application);
		SetMainThreadRole(*application, mainThreadControl);
		timer = CreateTimer(*application);
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
			DestroyTimer(timer, *application);
			DestroyConsole();
			application->FinalizeEarly();
			throw;
		}
	}

	void GUIProcess::Finalize()
	{
		application->FinalizeLate();
		application->FinalizeNormal();
		RemoveProcessInterfaces();
		DestroyTimer(timer, *application);
		DestroyConsole();
		application->FinalizeEarly();

#ifndef NDEBUG
		for (const std::type_index type : std::views::keys(application->Interfaces()))
		{
			MessageBoxA(nullptr, std::format("Interface of type {} wasn't removed from application.", type.name()).c_str(), "Interface not removed", MB_OK | MB_ICONERROR | MB_TOPMOST);
		}

		if (const std::size_t count = application->Tickables().size(); count != 0uz) [[unlikely]]
		{
			MessageBoxA(nullptr, std::format("{} tickables weren't removed from application.", count).c_str(), "Tickables not removed", MB_OK | MB_ICONERROR | MB_TOPMOST);
		}
#endif
	}

	void GUIProcess::CreateConsole() noexcept
	{
#ifdef PONY_ENGINE_APPLICATION_CREATE_CONSOLE
		if (!AllocConsole()) [[unlikely]]
		{
			PONY_LOG(application->LogService(), Log::LogType::Error, "Failed to allocate console. ErrorCode = '0x{:X}'.", GetLastError());
			return;
		}
		hasConsole = true;

		if (!SetConsoleCP(CP_UTF8)) [[unlikely]]
		{
			PONY_LOG(application->LogService(), Log::LogType::Error, "Failed to set console CP. ErrorCode = '0x{:X}'.", GetLastError());
		}
		if (!SetConsoleOutputCP(CP_UTF8)) [[unlikely]]
		{
			PONY_LOG(application->LogService(), Log::LogType::Error, "Failed to set output console CP. ErrorCode = '0x{:X}'.", GetLastError());
		}

		FILE* fp;
		if (const errno_t error = freopen_s(&fp, "CONOUT$", "w", stdout)) [[unlikely]]
		{
			PONY_LOG(application->LogService(), Log::LogType::Error, "Failed to reassign stdout to console. ErrorCode = '0x{:X}'.", error);
		}
		if (const errno_t error = freopen_s(&fp, "CONOUT$", "w", stderr)) [[unlikely]]
		{
			PONY_LOG(application->LogService(), Log::LogType::Error, "Failed to reassign stderr to console. ErrorCode = '0x{:X}'.", error);
		}
		if (const errno_t error = freopen_s(&fp, "CONIN$", "r", stdin)) [[unlikely]]
		{
			PONY_LOG(application->LogService(), Log::LogType::Error, "Failed to reassign stdin to console. ErrorCode = '0x{:X}'.", error);
		}
#endif
	}

	void GUIProcess::DestroyConsole() noexcept
	{
#ifdef PONY_ENGINE_APPLICATION_CREATE_CONSOLE
		if (!hasConsole)
		{
			return;
		}

		FILE* fp;
		if (const errno_t error = freopen_s(&fp, "NUL", "w", stdout)) [[unlikely]]
		{
			PONY_LOG(application->LogService(), Log::LogType::Error, "Failed to reassign stdout back to nul. ErrorCode = '0x{:X}'.", error);
		}
		if (const errno_t error = freopen_s(&fp, "NUL", "w", stderr)) [[unlikely]]
		{
			PONY_LOG(application->LogService(), Log::LogType::Error, "Failed to reassign stderr back to nul. ErrorCode = '0x{:X}'.", error);
		}
		if (const errno_t error = freopen_s(&fp, "NUL", "r", stdin)) [[unlikely]]
		{
			PONY_LOG(application->LogService(), Log::LogType::Error, "Failed to reassign stdin back to nul. ErrorCode = '0x{:X}'.", error);
		}

		if (!FreeConsole()) [[unlikely]]
		{
			PONY_LOG(application->LogService(), Log::LogType::Error, "Failed to free console. ErrorCode = '0x{:X}'.", GetLastError());
		}
		hasConsole = false;
#endif
	}

	void GUIProcess::AddProcessInterfaces()
	{
		application->AddInterface<IMainData>(*this);
		try
		{
			application->AddInterface<IMessagePump>(*this);
		}
		catch (...)
		{
			application->RemoveInterface<IMainData>(*this);
			throw;
		}
	}

	void GUIProcess::RemoveProcessInterfaces()
	{
		application->RemoveInterface<IMessagePump>(*this);
		application->RemoveInterface<IMainData>(*this);
	}

	int GUIProcess::RunMainLoop()
	{
		std::optional<int> exitCode;

		application->Begin();

		try
		{
			do
			{
				WaitForNextFrame(timer, *application);
				application->BeginFrame();
				TickMessagePump();
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

	void GUIProcess::TickMessagePump()
	{
		MSG message;
		while (PeekMessageA(&message, nullptr, 0, 0, PM_REMOVE | PM_NOYIELD))
		{
			lastMessageType = message.message;
			UpdateMessageTime(message.time);
			lastMessageCursorPoint = message.pt;

			if (message.message == WM_QUIT) [[unlikely]]
			{
				const int exitCode = static_cast<int>(message.wParam);
				PONY_LOG(application->LogService(), Log::LogType::Info, "Quit message received. Stopping application with code '{}'.", exitCode);
				application->Stop(exitCode);
			}

			TranslateMessage(&message);
			DispatchMessageA(&message);
		}
	}

	void GUIProcess::UpdateMessageTime(const DWORD newMessageTime) noexcept
	{
		const DWORD prevToNowDiff = newMessageTime - lastMessageNativeTime;
		const DWORD nowToPrevDiff = lastMessageNativeTime - newMessageTime;

		if (newMessageTime < lastMessageNativeTime && prevToNowDiff > nowToPrevDiff) [[unlikely]]
		{
			lastMessageTime -= std::chrono::milliseconds(nowToPrevDiff);
		}
		else [[likely]]
		{
			lastMessageTime += std::chrono::milliseconds(prevToNowDiff);
		}

		lastMessageNativeTime = newMessageTime;
	}
}

#endif
