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
#include "PonyEngine/Platform/Windows/Framework.h"

export module PonyEngine.Application.Impl.Windows:ConsoleProcess;

#ifdef PONY_ENGINE_APPLICATION_MODE_CONSOLE

import std;

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
	/// @brief Console process.
	class ConsoleProcess final : private IProcess
	{
	public:
		[[nodiscard("Pure constructor")]]
		ConsoleProcess(int argc, const char* const argv[]);
		ConsoleProcess(const ConsoleProcess&) = delete;
		ConsoleProcess(ConsoleProcess&&) = delete;

		~ConsoleProcess() noexcept = default;

		/// @brief Runs the process.
		/// @return Exit code.
		[[nodiscard("Must be returned from main")]]
		int Run();

		ConsoleProcess& operator =(const ConsoleProcess&) = delete;
		ConsoleProcess& operator =(ConsoleProcess&&) = delete;

	private:
		[[nodiscard("Pure function")]] 
		virtual std::shared_ptr<IThreadControl> CreateThreadControl(std::thread& thread) override;
		[[nodiscard("Pure function")]] 
		virtual std::string_view MainThreadRole() const noexcept override;
		virtual void MainThreadRole(std::string_view role) override;

		/// @brief Initializes the application.
		void Initialize();
		/// @brief Finalizes the application.
		void Finalize();

		/// @brief Runs the main loop.
		/// @return Exit code.
		[[nodiscard("Pure function")]]
		int RunMainLoop();

		std::unique_ptr<App> application; ///< Application.
		ThreadControl mainThreadControl; ///< Main thread control.
		HANDLE timer; ///< Timer handle.
	};
}

namespace PonyEngine::Application
{
	std::atomic_bool CtrlExit = false; ///< Is CTRL+C received?
	BOOL WINAPI CtrlHandler(DWORD ctrlType);

	ConsoleProcess::ConsoleProcess(const int argc, const char* const argv[]) :
		mainThreadControl(GetCurrentThread()),
		timer{nullptr}
	{
		if (!SetConsoleCtrlHandler(&CtrlHandler, TRUE)) [[unlikely]]
		{
			std::println(std::cerr, "Failed to set console ctrl handler.");
		}

		if (!SetConsoleCP(CP_UTF8)) [[unlikely]]
		{
			PONY_LOG(application->LogService(), Log::LogType::Error, "Failed to set console CP. ErrorCode = '0x{:X}'.", GetLastError());
		}
		if (!SetConsoleOutputCP(CP_UTF8)) [[unlikely]]
		{
			PONY_LOG(application->LogService(), Log::LogType::Error, "Failed to set output console CP. ErrorCode = '0x{:X}'.", GetLastError());
		}

		application = std::make_unique<App>(MakeCommandLineView(argc, argv), GetThreadRoles(), GetExecutablePath(), GetLocalDataDirectory(), GetUserDataDirectory(), 
			GetTempDataDirectory(), static_cast<IProcess&>(*this));
	}

	int ConsoleProcess::Run()
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

	std::shared_ptr<IThreadControl> ConsoleProcess::CreateThreadControl(std::thread& thread)
	{
		return std::make_shared<ThreadControl>(thread);
	}

	std::string_view ConsoleProcess::MainThreadRole() const noexcept
	{
		return mainThreadControl.Role();
	}

	void ConsoleProcess::MainThreadRole(const std::string_view role)
	{
		mainThreadControl.Role(role);
	}

	void ConsoleProcess::Initialize()
	{
		application->InitializeEarly();
		application->LogBasicInfo();
		LogProcessBasicInfo(*application);
		SetProcessPriority(*application);
		SetMainThreadRole(*application, mainThreadControl);
		timer = CreateTimer(*application);
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
			DestroyTimer(timer, *application);
			application->FinalizeEarly();
			throw;
		}
	}

	void ConsoleProcess::Finalize()
	{
		application->FinalizeLate();
		application->FinalizeNormal();
		DestroyTimer(timer, *application);
		application->FinalizeEarly();

#ifndef NDEBUG
		for (const std::type_index type : std::views::keys(application->Interfaces()))
		{
			std::println(std::cerr, "Interface of type {} wasn't removed from application.", type.name());
		}

		if (const std::size_t count = application->Tickables().size(); count != 0uz) [[unlikely]]
		{
			std::println(std::cerr, "{} tickables weren't removed from application.", count);
		}
#endif
	}

	int ConsoleProcess::RunMainLoop()
	{
		std::optional<int> exitCode;

		application->Begin();

		try
		{
			do
			{
				WaitForNextFrame(timer, *application);
				application->BeginFrame();
				if (CtrlExit.load(std::memory_order::relaxed)) [[unlikely]]
				{
					PONY_LOG(application->LogService(), Log::LogType::Info, "CTRL+C message received. Stopping application.");
					application->Stop();
				}
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

	BOOL CtrlHandler(const DWORD ctrlType)
	{
		switch (ctrlType)
		{
		case CTRL_C_EVENT:
			CtrlExit.store(true, std::memory_order::relaxed);
			return TRUE;
		default:
			return FALSE;
		}
	}
}

#endif
