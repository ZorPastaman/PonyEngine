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

import PonyEngine.Application.Windows;
import PonyEngine.Log;
import PonyEngine.Utility;

int APIENTRY WinMain(const HINSTANCE, const HINSTANCE, const PSTR, const int)
{
	int exitCode = PonyEngine::Application::ExitCodes::Success;

	try
	{
		PonyEngine::Application::Windows::SetProcessPriority(ABOVE_NORMAL_PRIORITY_CLASS);
#if PONY_CREATE_CONSOLE
		PonyEngine::Application::Windows::CreateConsole(CP_UTF8);
#endif

		try
		{
			PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Creating application...");
			PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Constructing application.");
			auto app = std::make_unique<PonyEngine::Application::App>(PonyEngine::Application::Windows::GetPlatformPaths());
			PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Beginning application.");
			app->Begin();
			PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Creating application done.");

			PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Main loop start.");
			bool shouldExit = false;
			while (!shouldExit)
			{
				PONY_CONSOLE(PonyEngine::Log::LogType::Verbose, "Ticking application.");
				shouldExit = app->Tick(exitCode);

				if (!shouldExit) [[likely]]
				{
					PONY_CONSOLE(PonyEngine::Log::LogType::Verbose, "Checking for quit message.");
					shouldExit = PonyEngine::Application::Windows::CheckForQuit(exitCode);
				}
			}
			PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Main loop finish. Exit code: '{}'.", exitCode);

			PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Destroying application...");
			PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Ending application.");
			app->End();
			PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Destructing application.")
			app.reset();
			PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Destroying application done.");
		}
		catch (const std::exception& e)
		{
			PONY_CONSOLE_E(e, "On application.");
			MessageBoxA(nullptr, PonyEngine::Utility::SafeFormat("Exception on application: '{}'.", e.what()).c_str(), "PonyEngine exception", MB_OK | MB_ICONERROR);

			exitCode = PonyEngine::Application::ExitCodes::ApplicationException;
		}
		catch (...)
		{
			PONY_CONSOLE(PonyEngine::Log::LogType::Exception, "Unknown exception - on application.");
			MessageBoxA(nullptr, "Exception on application.", "PonyEngine exception", MB_OK | MB_ICONERROR);

			exitCode = PonyEngine::Application::ExitCodes::ApplicationException;
		}

#if PONY_CREATE_CONSOLE
		PonyEngine::Application::Windows::DestroyConsole();
#endif
	}
	catch (const std::exception& e)
	{
		PONY_CONSOLE_E(e, "On main.");
		MessageBoxA(nullptr, PonyEngine::Utility::SafeFormat("Exception on main: '{}'.", e.what()).c_str(), "PonyEngine exception", MB_OK | MB_ICONERROR);

		exitCode = PonyEngine::Application::ExitCodes::MainException;
	}
	catch (...)
	{
		PONY_CONSOLE(PonyEngine::Log::LogType::Exception, "Unknown exception - on main.");
		MessageBoxA(nullptr, "Unknown exception on main.", "PonyEngine exception", MB_OK | MB_ICONERROR);

		exitCode = PonyEngine::Application::ExitCodes::MainException;
	}

	return exitCode;
}
