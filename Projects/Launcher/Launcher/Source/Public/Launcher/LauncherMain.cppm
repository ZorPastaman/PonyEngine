/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "Log/LogMacro.h"

export module Launcher:LauncherMain;

import <format>;
import <iostream>;

import PonyEngine.Core.Factories;
import PonyEngine.Log;
import PonyEngine.Window.Factories;

import :EngineParamsProvider;
import :EngineRunner;
import :IPlatformEngineParamsProvider;
import :IPlatformQuitChecker;

export namespace Launcher
{
	/// @brief Main function.
	/// @param logger Logger to use.
	/// @param quitChecker Platform quit checker.
	/// @param platformEngineParamsProvider Platform engine params provider.
	/// @return Exit code.
	int LauncherMain(PonyEngine::Log::ILogger& logger, const IPlatformQuitChecker& quitChecker, const IPlatformEngineParamsProvider& platformEngineParamsProvider);
}

namespace Launcher
{
	int LauncherMain(PonyEngine::Log::ILogger& logger, const IPlatformQuitChecker& quitChecker, const IPlatformEngineParamsProvider& platformEngineParamsProvider)
	{
		PONY_LOG_GENERAL(logger, PonyEngine::Log::LogType::Info, "Create an engine params provider.");
		const EngineParamsProvider engineParamsProvider(logger);
		PONY_LOG_GENERAL(logger, PonyEngine::Log::LogType::Info, "Engine params provider created.");
		PONY_LOG_GENERAL(logger, PonyEngine::Log::LogType::Info, "Create an engine runner.");
		const EngineRunner engineRunner(logger, engineParamsProvider, platformEngineParamsProvider);
		PONY_LOG_GENERAL(logger, PonyEngine::Log::LogType::Info, "Engine runner created.");

		PONY_LOG_GENERAL(logger, PonyEngine::Log::LogType::Info, "Start a main loop.");

		int exitCode = 0;
		bool isRunning = true;

		while (isRunning)
		{
			isRunning = engineRunner.Tick(exitCode) && quitChecker.Check(exitCode);
		}

		PONY_LOG_GENERAL(logger, PonyEngine::Log::LogType::Info, std::format("Main loop ended with the exit code '{}'.", exitCode).c_str());

		return exitCode;
	}
}
