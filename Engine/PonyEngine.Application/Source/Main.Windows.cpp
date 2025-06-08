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
	try
	{
		PonyEngine::Application::Windows::SetProcessPriority(ABOVE_NORMAL_PRIORITY_CLASS);
#if PONY_CREATE_CONSOLE
		PonyEngine::Application::Windows::CreateConsole(CP_UTF8);
#endif

		auto app = std::make_unique<PonyEngine::Application::App>();
		app.reset();

#if PONY_CREATE_CONSOLE
		PonyEngine::Application::Windows::DestroyConsole();
#endif
	}
	catch (const std::exception& e)
	{
		PONY_CONSOLE_E(e, "On main.");
		MessageBoxA(nullptr, PonyEngine::Utility::SafeFormat("Exception on main: '{}'.", e.what()).c_str(), "PonyEngine exception", MB_OK | MB_ICONERROR);

		return PonyEngine::Application::ExitCodes::MainException;
	}
	catch (...)
	{
		PONY_CONSOLE(PonyEngine::Log::LogType::Exception, "Unknown exception - on main.");
		MessageBoxA(nullptr, "Unknown exception on main.", "PonyEngine exception", MB_OK | MB_ICONERROR);

		return PonyEngine::Application::ExitCodes::MainException;
	}

	return PonyEngine::Application::ExitCodes::Success;
}
