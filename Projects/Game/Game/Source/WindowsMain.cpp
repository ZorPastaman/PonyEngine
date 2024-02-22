/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include <windows.h>

import EngineRunner;

bool PeekMessages(WPARAM& wParam);

int WINAPI wWinMain(const HINSTANCE hInstance, const HINSTANCE hPrevInstance, const PWSTR pCmdLine, const int nCmdShow)
{
	Game::EngineRunner engineRunner;

	while (engineRunner.IsRunning())
	{
		engineRunner.Tick();

		WPARAM wParam;
		if (PeekMessages(wParam))
		{
			return static_cast<int>(wParam);
		}
	}

	return engineRunner.GetExitCode();
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
