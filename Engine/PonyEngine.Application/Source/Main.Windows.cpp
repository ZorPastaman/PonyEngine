/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include <exception>
#include <memory>

#include "PonyEngine/Log/Log.h"
#include "PonyEngine/Platform/Windows/Framework.h"

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
			PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Creates application.");
			auto app = std::make_unique<PonyEngine::Application::App>();
			PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Begins application.");
			app->Begin();
			PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Application created.");

			// TODO: Here should be tick.

			PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Destroys application.");
			PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Ends application.");
			app->End();
			app.reset();
			PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Application destroyed.");
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

		PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Exits with code '{}'.", exitCode);
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
