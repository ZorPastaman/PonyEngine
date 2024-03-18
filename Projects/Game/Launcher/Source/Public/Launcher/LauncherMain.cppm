/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module Launcher:LauncherMain;

import <functional>;

import PonyEngine.Core.Factories;
import PonyEngine.Window.Factories;

import :EngineParamsProvider;
import :EngineRunner;
import :IPlatformEngineParamsProvider;
import :IPlatformQuitChecker;

namespace Launcher
{
	/// @brief Main function.
	/// @param quitChecker Platform quit checker.
	/// @param platformEngineParamsProvider Platform engine params provider.
	/// @return Exit code.
	export int LauncherMain(IPlatformQuitChecker& quitChecker, IPlatformEngineParamsProvider& engineParamsProvider);

	int LauncherMain(IPlatformQuitChecker& quitChecker, IPlatformEngineParamsProvider& platformEngineParamsProvider)
	{
		EngineParamsProvider engineParamsProvider;
		EngineRunner engineRunner(engineParamsProvider, platformEngineParamsProvider);

		int exitCode = 0;
		bool shouldExit = false;

		while (!shouldExit)
		{
			shouldExit = !engineRunner.Tick(exitCode) || !quitChecker.Check(exitCode);
		}

		return exitCode;
	}
}
