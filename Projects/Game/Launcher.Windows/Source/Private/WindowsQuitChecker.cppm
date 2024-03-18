/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

export module Launcher.Windows:WindowsQuitChecker;

import Launcher;

namespace Launcher
{
	/// @brief Windows quit checker.
	export class WindowsQuitChecker : public IPlatformQuitChecker
	{
	public:
		[[nodiscard("Pure constructor")]]
		WindowsQuitChecker() noexcept = default;
		WindowsQuitChecker(const WindowsQuitChecker&) = delete;
		WindowsQuitChecker(WindowsQuitChecker&&) = delete;

		virtual ~WindowsQuitChecker() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual bool Check(int& exitCode) const override;

		WindowsQuitChecker& operator =(const WindowsQuitChecker&) = delete;
		WindowsQuitChecker& operator =(WindowsQuitChecker&&) = delete;
	};

	bool WindowsQuitChecker::Check(int& exitCode) const
	{
		MSG message;
		while (PeekMessage(&message, NULL, 0, 0, PM_REMOVE | PM_NOYIELD))
		{
			DispatchMessage(&message);

			if (TranslateMessage(&message))
			{
				DispatchMessage(&message);
			}

			if (message.message == WM_QUIT)
			{
				exitCode = static_cast<int>(message.wParam);
				return false;
			}
		}

		return true;
	}
}
