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
import PonyEngine.Platform.Windows;

import :Path;
import :Process;

export namespace PonyEngine::Application::Windows
{
	/// @brief Console process.
	class ConsoleProcess final
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
		/// @brief Initializes the application.
		void Initialize();
		/// @brief Finalizes the application.
		void Finalize();

		/// @brief Logs basic info.
		void LogProcessBasicInfo() const noexcept;

		/// @brief Sets the process priority.
		void SetPriority() const noexcept;

		/// @brief Runs the main loop.
		/// @return Exit code.
		[[nodiscard("Pure function")]]
		int RunMainLoop();

		std::vector<std::string_view> commandLine; ///< Command line.

		std::unique_ptr<App> application; ///< Application.
	};
}

namespace PonyEngine::Application::Windows
{
	ConsoleProcess::ConsoleProcess(const int argc, const char* const argv[])
	{
		commandLine.reserve(argc);
		for (int i = 0; i < argc; ++i)
		{
			commandLine.push_back(argv[i]);
		}

		application = std::make_unique<App>(commandLine, GetExecutablePath(), GetLocalDataDirectory(), GetUserDataDirectory(), GetTempDataDirectory());
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

	void ConsoleProcess::Initialize()
	{
		application->InitializeEarly();
		application->LogBasicInfo();
		LogProcessBasicInfo();
		SetPriority();
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
			application->FinalizeEarly();
			throw;
		}
	}

	void ConsoleProcess::Finalize()
	{
		application->FinalizeLate();
		application->FinalizeNormal();
		application->FinalizeEarly();

#ifndef NDEBUG
		for (const std::type_index type : std::views::keys(application->Interfaces()))
		{
			std::cerr << std::format("Interface of type {} wasn't removed from application.", type.name());
		}

		if (const std::size_t count = application->Tickables().size(); count != 0uz) [[unlikely]]
		{
			std::cerr << std::format("{} tickables weren't removed from application.", count);
		}
#endif
	}

	void ConsoleProcess::LogProcessBasicInfo() const noexcept
	{
		PONY_LOG(application->LogService(), Log::LogType::Info, "PID: '{}'.", GetCurrentProcessId());
	}

	void ConsoleProcess::SetPriority() const noexcept
	{
		constexpr DWORD priority = ABOVE_NORMAL_PRIORITY_CLASS;

		PONY_LOG(application->LogService(), Log::LogType::Info, "Setting process priority. Priority: '{}'.", priority);
		try
		{
			SetProcessPriority(priority);
		}
		catch (...)
		{
			PONY_LOG(application->LogService(), Log::LogType::Error, std::current_exception(), "Failed to set process priority.");
			// The application should keep working.
		}
	}

	int ConsoleProcess::RunMainLoop()
	{
		std::optional<int> exitCode;

		application->Begin();

		try
		{
			for (exitCode = application->ExitCode(); !exitCode; exitCode = application->ExitCode())
			{
				application->BeginFrame();
				application->Tick();
				application->EndFrame();
			}
		}
		catch (...)
		{
			application->End();
			throw;
		}

		application->End();

		return *exitCode;
	}
}

#endif
