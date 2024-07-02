/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Log/LogMacro.h"
#include "PonyEngine/Platform/Windows/Framework.h"

export module Launcher.Windows:WindowsQuitChecker;

import <format>;
import <iostream>;

import PonyEngine.Log;

import Launcher;

export namespace Launcher
{
	/// @brief Windows quit checker.
	class WindowsQuitChecker final : public IPlatformQuitChecker
	{
	public:
		/// @brief Creates a @p WindowsQuitChecker.
		/// @param logger Logger to use.
		[[nodiscard("Pure constructor")]]
		explicit WindowsQuitChecker(PonyEngine::Log::ILogger& logger) noexcept;
		WindowsQuitChecker(const WindowsQuitChecker&) = delete;
		WindowsQuitChecker(WindowsQuitChecker&&) = delete;

		~WindowsQuitChecker() noexcept = default;

		[[nodiscard("Non-ignorable result")]]
		virtual bool Check(int& exitCode) const override;

		WindowsQuitChecker& operator =(const WindowsQuitChecker&) = delete;
		WindowsQuitChecker& operator =(WindowsQuitChecker&&) = delete;

	private:
		PonyEngine::Log::ILogger& logger; ///< Logger.
	};
}

namespace Launcher
{
	WindowsQuitChecker::WindowsQuitChecker(PonyEngine::Log::ILogger& logger) noexcept :
		logger{logger}
	{
	}

	bool WindowsQuitChecker::Check(int& exitCode) const
	{
		PONY_LOG_GENERAL(logger, PonyEngine::Log::LogType::Verbose, "Check for a quit message.");

		MSG message;
		while (PeekMessage(&message, NULL, 0, 0, PM_REMOVE | PM_NOYIELD))
		{
			TranslateMessage(&message);
			DispatchMessage(&message);

			if (message.message == WM_QUIT)
			{
				exitCode = static_cast<int>(message.wParam);
				PONY_LOG_GENERAL(logger, PonyEngine::Log::LogType::Info, std::format("Received the exit code '{}' from the platform.", exitCode).c_str());

				return false;
			}
		}

		return true;
	}
}
