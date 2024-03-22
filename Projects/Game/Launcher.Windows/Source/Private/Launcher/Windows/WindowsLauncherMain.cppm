/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "Debug/Log/LogMacro.h"

export module Launcher.Windows:WindowsLauncherMain;

import <format>;
import <iostream>;

import PonyEngine.Debug.Log;

import Launcher;

import :WindowsEngineParamsProvider;
import :WindowsQuitChecker;

using LogType = PonyEngine::Debug::Log::LogType;

namespace Launcher
{
	export int WindowsMain(PonyEngine::Debug::Log::ILogger& logger);

	int WindowsMain(PonyEngine::Debug::Log::ILogger& logger)
	{
		PONY_LOG_GENERAL(logger, LogType::Info, "Create a Windows engine params provider.");
		const WindowsEngineParamsProvider windowsEngineParamsProvider(logger);
		PONY_LOG_GENERAL(logger, LogType::Info, "Windows engine params provider created.");
		PONY_LOG_GENERAL(logger, LogType::Info, "Create a Windows quit checker.");
		const WindowsQuitChecker windowsQuitChecker(logger);
		PONY_LOG_GENERAL(logger, LogType::Info, "Windows quit checker created.");

		return LauncherMain(logger, windowsQuitChecker, windowsEngineParamsProvider);
	}
}
