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

export module Launcher.Windows:WindowsLoop;

import <format>;
import <iostream>;

import PonyEngine.Log;

import Launcher;

export namespace Launcher
{
	/// @brief Windows loop.
	class WindowsLoop final : public ILoopElement
	{
	public:
		/// @brief Creates a Windows loop.
		/// @param logger Logger to use.
		[[nodiscard("Pure constructor")]]
		explicit WindowsLoop(PonyEngine::Log::ILogger& logger) noexcept;
		WindowsLoop(const WindowsLoop&) = delete;
		WindowsLoop(WindowsLoop&&) = delete;

		~WindowsLoop() noexcept = default;

		virtual bool Tick(int& exitCode) override;

		WindowsLoop& operator =(const WindowsLoop&) = delete;
		WindowsLoop& operator =(WindowsLoop&&) = delete;

	private:
		PonyEngine::Log::ILogger* const logger; ///< Logger.
	};
}

namespace Launcher
{
	WindowsLoop::WindowsLoop(PonyEngine::Log::ILogger& logger) noexcept :
		logger{&logger}
	{
	}

	bool WindowsLoop::Tick(int& exitCode)
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
