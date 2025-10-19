/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/Log/LogApp.h"

#if PONY_WINDOWS
#include "PonyEngine/Platform/Windows/Framework.h"
#endif

import std;

import PonyEngine.Application.Main;
import PonyEngine.Log;
import PonyEngine.Text;

#if PONY_WINDOWS
int APIENTRY WinMain(const HINSTANCE hInstance, const HINSTANCE hPrevInstance, const PSTR lpCmdLine, const int nShowCmd)
{
	int exitCode = PonyEngine::Application::ExitCodes::Success;
	std::optional<std::string> exceptionInfo = std::nullopt;

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
				if (!exceptionInfo)
				{
					exceptionInfo = PonyEngine::Text::FormatSafe("Exception on application tick: '{}'.", e.what());
				}
				exitCode = PonyEngine::Application::ExitCodes::TickException;
			}
			catch (...)
			{
				PONY_APP_CONSOLE(PonyEngine::Log::LogType::Exception, "Unknown exception on application tick.");
				if (!exceptionInfo)
				{
					exceptionInfo = "Unknown exception on application tick.";
				}
				exitCode = PonyEngine::Application::ExitCodes::TickException;
			}

			PONY_APP_CONSOLE(PonyEngine::Log::LogType::Info, "Destructing application...");
			app.reset();
			PONY_APP_CONSOLE(PonyEngine::Log::LogType::Info, "Destructing application done.");
		}
		catch (const std::exception& e)
		{
			PONY_APP_CONSOLE_E(e, "On application.");
			if (!exceptionInfo)
			{
				exceptionInfo = PonyEngine::Text::FormatSafe("Exception on application: '{}'.", e.what());
			}
			exitCode = PonyEngine::Application::ExitCodes::ApplicationException;
		}
		catch (...)
		{
			PONY_APP_CONSOLE(PonyEngine::Log::LogType::Exception, "Unknown exception on application.");
			if (!exceptionInfo)
			{
				exceptionInfo = "Unknown exception on application.";
			}
			exitCode = PonyEngine::Application::ExitCodes::ApplicationException;
		}

#if PONY_ENGINE_CREATE_CONSOLE
		PonyEngine::Application::Windows::DestroyConsole();
#endif
	}
	catch (const std::exception& e)
	{
		PONY_APP_CONSOLE_E(e, "On main.");
		if (!exceptionInfo)
		{
			exceptionInfo = PonyEngine::Text::FormatSafe("Exception on main: '{}'.", e.what());
		}
		exitCode = PonyEngine::Application::ExitCodes::MainException;
	}
	catch (...)
	{
		PONY_APP_CONSOLE(PonyEngine::Log::LogType::Exception, "Unknown exception on main.");
		if (!exceptionInfo)
		{
			exceptionInfo = "Unknown exception on main.";
		}
		exitCode = PonyEngine::Application::ExitCodes::MainException;
	}

	if (exceptionInfo) [[unlikely]]
	{
		MessageBoxA(nullptr, exceptionInfo->c_str(), "PonyEngine exception", MB_OK | MB_ICONERROR | MB_TOPMOST);
	}

	return exitCode;
}
#endif
