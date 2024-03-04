/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include <format>
#include <iostream>
#include <windows.h>

#include "Debug/Log/LogMacro.h"

import PonyEngine.Debug.Log;

import EngineRunner;

bool PeekMessages(WPARAM& wParam);

int WINAPI wWinMain(const HINSTANCE hInstance, const HINSTANCE hPrevInstance, const PWSTR pCmdLine, const int nCmdShow)
{
	PONY_COUT("Create an engine runner");
	Game::EngineRunner engineRunner;
	PONY_COUT("Engine runner created");

	while (engineRunner.IsRunning())
	{
		engineRunner.Tick();

		WPARAM wParam;
		if (PeekMessages(wParam))
		{
			PONY_COUT(std::format("Application is ended with message code '{}'", wParam));

			return static_cast<int>(wParam);
		}
	}

	int exitCode = engineRunner.GetExitCode();
	PONY_COUT(std::format("Application is ended with the engine exit code '{}'", exitCode));

	return exitCode;
}

bool PeekMessages(WPARAM& wParam)
{
	MSG message;
	while (PeekMessage(&message, NULL, 0, 0, PM_REMOVE | PM_NOYIELD))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);

		switch (message.message)
		{
		case WM_QUIT:
			wParam = message.wParam;
			return true;
		}
	}

	return false;
}
