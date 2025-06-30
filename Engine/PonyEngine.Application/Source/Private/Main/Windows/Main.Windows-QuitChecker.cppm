/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Platform/Windows/Framework.h"

export module PonyEngine.Main.Windows:QuitChecker;

export namespace PonyEngine::Main::Windows
{
	/// @brief Checks if the application must exit.
	/// @remark The function peeks and removes all the messages to the application. So, it must be called last.
	/// @param exitCode Exit code.
	/// @return @a True if the application must exit; @a false otherwise.
	[[nodiscard("Return value must be used")]]
	bool CheckForQuit(int& exitCode);
}

namespace PonyEngine::Main::Windows
{
	bool CheckForQuit(int& exitCode)
	{
		MSG message;
		while (PeekMessageA(&message, nullptr, 0, 0, PM_REMOVE | PM_NOYIELD))
		{
			TranslateMessage(&message);
			DispatchMessageA(&message);

			if (message.message == WM_QUIT) [[unlikely]]
			{
				exitCode = static_cast<int>(message.wParam);

				return true;
			}
		}

		return false;
	}
}
