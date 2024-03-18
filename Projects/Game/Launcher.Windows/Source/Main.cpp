/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "Platform/Windows/Framework.h"

import Launcher;
import Launcher.Windows;

int APIENTRY wWinMain(const HINSTANCE hInstance, const HINSTANCE hPrevInstance, const LPWSTR lpCmdLine, const int nCmdShow)
{
	const Launcher::WindowsEngineParamsProvider windowsEngineParamsProvider;
	const Launcher::WindowsQuitChecker windowsQuitChecker;

	return Launcher::LauncherMain(windowsQuitChecker, windowsEngineParamsProvider);
}
