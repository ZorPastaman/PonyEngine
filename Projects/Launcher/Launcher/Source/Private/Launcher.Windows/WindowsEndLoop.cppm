/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Log/Log.h"
#include "PonyEngine/Platform/Windows/Framework.h"

export module Launcher.Windows:WindowsEndLoop;

import <format>;
import <iostream>;

import PonyEngine.Log;

import Launcher;

export namespace Launcher
{
	/// @brief Windows end loop. It checks for WM_QUIT.
	class WindowsEndLoop final : public ILoopElement
	{
	public:
		/// @brief Creates a Windows loop.
		/// @param logger Logger to use.
		[[nodiscard("Pure constructor")]]
		explicit WindowsEndLoop(PonyEngine::Log::ILogger& logger) noexcept;
		WindowsEndLoop(const WindowsEndLoop&) = delete;
		WindowsEndLoop(WindowsEndLoop&&) = delete;

		~WindowsEndLoop() noexcept = default;

		virtual bool Tick(int& exitCode) override;

		WindowsEndLoop& operator =(const WindowsEndLoop&) = delete;
		WindowsEndLoop& operator =(WindowsEndLoop&&) = delete;

	private:
		PonyEngine::Log::ILogger* const logger; ///< Logger.
	};
}

namespace Launcher
{
	WindowsEndLoop::WindowsEndLoop(PonyEngine::Log::ILogger& logger) noexcept :
		logger{&logger}
	{
	}

	bool WindowsEndLoop::Tick(int& exitCode)
	{
		PONY_LOG_GENERAL(logger, PonyEngine::Log::LogType::Verbose, "Peek messages.");

		MSG message;
		while (PeekMessageW(&message, NULL, 0, 0, PM_REMOVE | PM_NOYIELD))
		{
			TranslateMessage(&message);
			DispatchMessageW(&message);

			if (message.message == WM_QUIT)
			{
				exitCode = static_cast<int>(message.wParam);
				PONY_LOG_GENERAL(logger, PonyEngine::Log::LogType::Info, "Received the exit code '{}' from Windows.", exitCode);

				return true;
			}
		}

		return false;
	}
}
