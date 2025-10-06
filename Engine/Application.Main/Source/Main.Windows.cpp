/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/Log/LogApp.h"
#include "PonyEngine/Platform/Windows/Framework.h"

import std;

import PonyEngine.Application.Main;
import PonyEngine.Log;
import PonyEngine.Text;

int APIENTRY WinMain(const HINSTANCE hInstance, const HINSTANCE hPrevInstance, const PSTR lpCmdLine, const int nShowCmd)
{
	int exitCode = PonyEngine::Application::ExitCodes::Success;

	try
	{
		PonyEngine::Application::Windows::SetProcessPriority(ABOVE_NORMAL_PRIORITY_CLASS);
#if PONY_ENGINE_CREATE_CONSOLE
		PonyEngine::Application::Windows::CreateConsole();
#endif

		try
		{
			PONY_APP_CONSOLE(PonyEngine::Log::LogType::Info, "Constructing application...");
			auto app = std::make_unique<PonyEngine::Application::Windows::App>(hInstance, hPrevInstance, lpCmdLine, nShowCmd);
			PONY_APP_CONSOLE(PonyEngine::Log::LogType::Info, "Constructing application done.");

			try
			{
				PONY_APP_CONSOLE(PonyEngine::Log::LogType::Info, "Running application...");
				exitCode = app->Run();
				PONY_APP_CONSOLE(PonyEngine::Log::LogType::Info, "Running application done. Exit code: '{}'.", exitCode);
			}
			catch (const std::exception& e)
			{
				PONY_APP_CONSOLE_E(e, "On application tick.");
				MessageBoxA(nullptr, PonyEngine::Text::FormatSafe("Exception on application tick: '{}'.", e.what()).c_str(), "PonyEngine exception", MB_OK | MB_ICONERROR);

				exitCode = PonyEngine::Application::ExitCodes::TickException;
			}
			catch (...)
			{
				PONY_APP_CONSOLE(PonyEngine::Log::LogType::Exception, "Unknown exception on application tick.");
				MessageBoxA(nullptr, "Exception on application tick.", "PonyEngine exception", MB_OK | MB_ICONERROR);

				exitCode = PonyEngine::Application::ExitCodes::TickException;
			}

			PONY_APP_CONSOLE(PonyEngine::Log::LogType::Info, "Destructing application...");
			app.reset();
			PONY_APP_CONSOLE(PonyEngine::Log::LogType::Info, "Destructing application done.");
		}
		catch (const std::exception& e)
		{
			PONY_APP_CONSOLE_E(e, "On application.");
			MessageBoxA(nullptr, PonyEngine::Text::FormatSafe("Exception on application: '{}'.", e.what()).c_str(), "PonyEngine exception", MB_OK | MB_ICONERROR);

			exitCode = PonyEngine::Application::ExitCodes::ApplicationException;
		}
		catch (...)
		{
			PONY_APP_CONSOLE(PonyEngine::Log::LogType::Exception, "Unknown exception on application.");
			MessageBoxA(nullptr, "Exception on application.", "PonyEngine exception", MB_OK | MB_ICONERROR);

			exitCode = PonyEngine::Application::ExitCodes::ApplicationException;
		}

#if PONY_ENGINE_CREATE_CONSOLE
		PonyEngine::Application::Windows::DestroyConsole();
#endif
	}
	catch (const std::exception& e)
	{
		PONY_APP_CONSOLE_E(e, "On main.");
		MessageBoxA(nullptr, PonyEngine::Text::FormatSafe("Exception on main: '{}'.", e.what()).c_str(), "PonyEngine exception", MB_OK | MB_ICONERROR);

		exitCode = PonyEngine::Application::ExitCodes::MainException;
	}
	catch (...)
	{
		PONY_APP_CONSOLE(PonyEngine::Log::LogType::Exception, "Unknown exception on main.");
		MessageBoxA(nullptr, "Unknown exception on main.", "PonyEngine exception", MB_OK | MB_ICONERROR);

		exitCode = PonyEngine::Application::ExitCodes::MainException;
	}

	return exitCode;
}
