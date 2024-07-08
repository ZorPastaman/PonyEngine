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
		PonyEngine::Log::ILogger* logger; ///< Logger.
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
		PONY_LOG_GENERAL_PTR(logger, PonyEngine::Log::LogType::Verbose, "Pick messages.");

		MSG message;
		while (PeekMessage(&message, NULL, 0, 0, PM_REMOVE | PM_NOYIELD))
		{
			TranslateMessage(&message);
			DispatchMessage(&message);

			if (message.message == WM_QUIT)
			{
				exitCode = static_cast<int>(message.wParam);
				PONY_LOG_GENERAL_PTR(logger, PonyEngine::Log::LogType::Info, std::format("Received the exit code '{}' from Windows.", exitCode).c_str());

				return true;
			}
		}

		return false;
	}
}
