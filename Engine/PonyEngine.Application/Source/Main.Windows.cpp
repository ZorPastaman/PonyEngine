/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/Log/Log.h"
#include "PonyEngine/Platform/Windows/Framework.h"

import std;

import PonyEngine.Log;
import PonyEngine.Main.Windows;
import PonyEngine.Utility;

/// @brief Creates an application.
/// @return Application.
[[nodiscard("Pure function")]]
std::unique_ptr<PonyEngine::Main::App> CreateApp();

int APIENTRY WinMain(const HINSTANCE, const HINSTANCE, const PSTR, const int)
{
	int exitCode = PonyEngine::Main::ExitCodes::Success;

	try
	{
		PonyEngine::Main::Windows::SetProcessPriority(ABOVE_NORMAL_PRIORITY_CLASS);
#if PONY_ENGINE_CREATE_CONSOLE
		PonyEngine::Main::Windows::CreateConsole(CP_UTF8);
#endif

		try
		{
			PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Creating application...");
			std::unique_ptr<PonyEngine::Main::App> app = CreateApp();
			PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Creating application done.");

			try
			{
				PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Main loop start.");
				bool shouldExit = false;
				while (!shouldExit)
				{
					PONY_CONSOLE(PonyEngine::Log::LogType::Verbose, "Ticking application.");
					shouldExit = app->Tick(exitCode);

					if (!shouldExit) [[likely]]
					{
						PONY_CONSOLE(PonyEngine::Log::LogType::Verbose, "Checking for quit message.");
						shouldExit = PonyEngine::Main::Windows::CheckForQuit(exitCode);
					}
				}
				PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Main loop finish. Exit code: '{}'.", exitCode);
			}
			catch (const std::exception& e)
			{
				PONY_CONSOLE_E(e, "On application tick.");
				MessageBoxA(nullptr, PonyEngine::Utility::SafeFormat("Exception on application tick: '{}'.", e.what()).c_str(), "PonyEngine exception", MB_OK | MB_ICONERROR);

				exitCode = PonyEngine::Main::ExitCodes::TickException;
			}
			catch (...)
			{
				PONY_CONSOLE(PonyEngine::Log::LogType::Exception, "Unknown exception on application tick.");
				MessageBoxA(nullptr, "Exception on application tick.", "PonyEngine exception", MB_OK | MB_ICONERROR);

				exitCode = PonyEngine::Main::ExitCodes::TickException;
			}

			PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Releasing application.");
			app.reset();
		}
		catch (const std::exception& e)
		{
			PONY_CONSOLE_E(e, "On application.");
			MessageBoxA(nullptr, PonyEngine::Utility::SafeFormat("Exception on application: '{}'.", e.what()).c_str(), "PonyEngine exception", MB_OK | MB_ICONERROR);

			exitCode = PonyEngine::Main::ExitCodes::ApplicationException;
		}
		catch (...)
		{
			PONY_CONSOLE(PonyEngine::Log::LogType::Exception, "Unknown exception on application.");
			MessageBoxA(nullptr, "Exception on application.", "PonyEngine exception", MB_OK | MB_ICONERROR);

			exitCode = PonyEngine::Main::ExitCodes::ApplicationException;
		}

#if PONY_ENGINE_CREATE_CONSOLE
		PonyEngine::Main::Windows::DestroyConsole();
#endif
	}
	catch (const std::exception& e)
	{
		PONY_CONSOLE_E(e, "On main.");
		MessageBoxA(nullptr, PonyEngine::Utility::SafeFormat("Exception on main: '{}'.", e.what()).c_str(), "PonyEngine exception", MB_OK | MB_ICONERROR);

		exitCode = PonyEngine::Main::ExitCodes::MainException;
	}
	catch (...)
	{
		PONY_CONSOLE(PonyEngine::Log::LogType::Exception, "Unknown exception on main.");
		MessageBoxA(nullptr, "Unknown exception on main.", "PonyEngine exception", MB_OK | MB_ICONERROR);

		exitCode = PonyEngine::Main::ExitCodes::MainException;
	}

	return exitCode;
}

std::unique_ptr<PonyEngine::Main::App> CreateApp()
{
	PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Getting platform paths.");
	const PonyEngine::Main::PlatformPaths paths = PonyEngine::Main::Windows::GetPlatformPaths();

	PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Constructing application.");
	return std::make_unique<PonyEngine::Main::App>(paths);
}
