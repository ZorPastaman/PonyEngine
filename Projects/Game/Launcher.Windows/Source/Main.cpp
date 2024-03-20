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
	UNREFERENCED_PARAMETER(hInstance);
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	UNREFERENCED_PARAMETER(nCmdShow);

	const Launcher::WindowsEngineParamsProvider windowsEngineParamsProvider;
	const Launcher::WindowsQuitChecker windowsQuitChecker;

	return Launcher::LauncherMain(windowsQuitChecker, windowsEngineParamsProvider);
}
