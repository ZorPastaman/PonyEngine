/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include <iostream>

#include "Debug/Log/LogMacro.h"
#include "Platform/Windows/Framework.h"

import PonyEngine.Debug.Log;

import Launcher;
import Launcher.Windows;

using LogType = PonyEngine::Debug::Log::LogType;

int APIENTRY wWinMain(const HINSTANCE hInstance, const HINSTANCE hPrevInstance, const LPWSTR lpCmdLine, const int nCmdShow)
{
	UNREFERENCED_PARAMETER(hInstance);
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	UNREFERENCED_PARAMETER(nCmdShow);

	PONY_CONSOLE(LogType::Info, "Create a logger provider");
	const Launcher::LoggerProvider loggerProvider;
	PONY_CONSOLE(LogType::Info, "Logger provider created");

	PONY_LOG_GENERAL(loggerProvider.GetLogger(), LogType::Info, "Create a Windows quit checker.");
	const Launcher::WindowsQuitChecker windowsQuitChecker(loggerProvider.GetLogger());
	PONY_LOG_GENERAL(loggerProvider.GetLogger(), LogType::Info, "Windows quit checker created.");

	PONY_LOG_GENERAL(loggerProvider.GetLogger(), LogType::Info, "Create a Windows engine params provider.");
	const Launcher::WindowsEngineParamsProvider windowsEngineParamsProvider(loggerProvider.GetLogger());
	PONY_LOG_GENERAL(loggerProvider.GetLogger(), LogType::Info, "Windows engine params provider created.");

	return Launcher::LauncherMain(loggerProvider.GetLogger(), windowsQuitChecker, windowsEngineParamsProvider);
}
