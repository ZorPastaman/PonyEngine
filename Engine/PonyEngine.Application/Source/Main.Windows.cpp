/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: cybercode.smith@pm.me                    *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include <exception>

#include "PonyEngine/Log/Log.h"
#include "PonyEngine/Platform/Windows/Framework.h"

import PonyEngine.Application.Windows;
import PonyEngine.Log;

int APIENTRY WinMain(const HINSTANCE, const HINSTANCE, const PSTR, const int)
{
	try
	{
		PonyEngine::Application::Windows::SetProcessPriority(ABOVE_NORMAL_PRIORITY_CLASS);
#if PONY_CREATE_CONSOLE
		PonyEngine::Application::Windows::CreateConsole(CP_UTF8);
#endif

		PonyEngine::Application::App app;

#if PONY_CREATE_CONSOLE
		PonyEngine::Application::Windows::DestroyConsole();
#endif
	}
	catch (const std::exception& e)
	{
		PONY_CONSOLE_E(e, "On main.");

		return PonyEngine::Application::ExitCodes::MainException;
	}
	catch (...)
	{
		PONY_CONSOLE(PonyEngine::Log::LogType::Exception, "Unknown exception - on main.");

		return PonyEngine::Application::ExitCodes::MainException;
	}

	return PonyEngine::Application::ExitCodes::Success;
}
