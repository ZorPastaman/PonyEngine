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
#include "Platform/Windows/Framework.h"

export module Launcher.Windows:WindowsQuitChecker;

import <format>;
import <iostream>;

import PonyEngine.Debug.Log;

import Launcher;

using LogType = PonyEngine::Debug::Log::LogType;

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

		[[nodiscard("Non-ignorable result")]]
		virtual bool Check(int& exitCode) const override;

		WindowsQuitChecker& operator =(const WindowsQuitChecker&) = delete;
		WindowsQuitChecker& operator =(WindowsQuitChecker&&) = delete;
	};

	bool WindowsQuitChecker::Check(int& exitCode) const
	{
		PONY_CONSOLE(LogType::Verbose, "Check for a quit message.");

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
				PONY_CONSOLE(LogType::Info, std::format("Received the exit code '{}' from the platform.", exitCode));

				return false;
			}
		}

		return true;
	}
}
