/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

import Launcher;
import Launcher.Windows;

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	Launcher::WindowsEngineParamsProvider windowsEngineParamsProvider;
	Launcher::WindowsQuitChecker windowsQuitChecker;

	return Launcher::LauncherMain(windowsQuitChecker, windowsEngineParamsProvider);
}
