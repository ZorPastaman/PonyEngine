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
		/// @brief Creates a @p WindowsQuitChecker.
		/// @param logger Logger to use.
		[[nodiscard("Pure constructor")]]
		WindowsQuitChecker(PonyEngine::Debug::Log::ILogger& logger) noexcept;
		WindowsQuitChecker(const WindowsQuitChecker&) = delete;
		WindowsQuitChecker(WindowsQuitChecker&&) = delete;

		virtual ~WindowsQuitChecker() noexcept = default;

		[[nodiscard("Non-ignorable result")]]
		virtual bool Check(int& exitCode) const override;

		WindowsQuitChecker& operator =(const WindowsQuitChecker&) = delete;
		WindowsQuitChecker& operator =(WindowsQuitChecker&&) = delete;

	private:
		PonyEngine::Debug::Log::ILogger& m_logger; /// @brief Logger.
	};

	WindowsQuitChecker::WindowsQuitChecker(PonyEngine::Debug::Log::ILogger& logger) noexcept :
		m_logger{logger}
	{
	}

	bool WindowsQuitChecker::Check(int& exitCode) const
	{
		PONY_LOG_GENERAL(m_logger, LogType::Verbose, "Check for a quit message.");

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
				PONY_LOG_GENERAL(m_logger, LogType::Info, std::format("Received the exit code '{}' from the platform.", exitCode).c_str());

				return false;
			}
		}

		return true;
	}
}
