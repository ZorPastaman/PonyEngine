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

export module Launcher:LauncherMain;

import <format>;
import <iostream>;

import PonyEngine.Core.Factories;
import PonyEngine.Debug.Log;
import PonyEngine.Window.Factories;

import :EngineParamsProvider;
import :EngineRunner;
import :IPlatformEngineParamsProvider;
import :IPlatformQuitChecker;

using LogType = PonyEngine::Debug::Log::LogType;

namespace Launcher
{
	/// @brief Main function.
	/// @param quitChecker Platform quit checker.
	/// @param platformEngineParamsProvider Platform engine params provider.
	/// @return Exit code.
	export int LauncherMain(const IPlatformQuitChecker& quitChecker, const IPlatformEngineParamsProvider& engineParamsProvider);

	int LauncherMain(const IPlatformQuitChecker& quitChecker, const IPlatformEngineParamsProvider& platformEngineParamsProvider)
	{
		PONY_CONSOLE(LogType::Info, "Create an engine params provider.");
		const EngineParamsProvider engineParamsProvider;
		PONY_CONSOLE(LogType::Info, "Engine params provider created.");
		PONY_CONSOLE(LogType::Info, "Create an engine runner.");
		EngineRunner engineRunner(engineParamsProvider, platformEngineParamsProvider);
		PONY_CONSOLE(LogType::Info, "Engine runner created.");

		PONY_CONSOLE(LogType::Info, "Start a main loop.");

		int exitCode = 0;
		bool isRunning = true;

		while (isRunning)
		{
			isRunning = engineRunner.Tick(exitCode) && quitChecker.Check(exitCode);
		}

		PONY_CONSOLE(LogType::Info, std::format("Main loop ended with the exit code '{}'.", exitCode));

		return exitCode;
	}
}
