/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Platform/WinCore/Framework.h"

export module PonyEngine.Log.PlatformConsole.WinCore:PlatformConsoleSubLogger;

import std;

import PonyEngine.Log.Extension;

export namespace PonyEngine::Log::PlatformConsole::WinCore
{
	/// @brief Sub-logger that writes every message to the OutputDebugString.
	class PlatformConsoleSubLogger final : public Extension::ISubLogger
	{
	public:
		[[nodiscard("Pure constructor")]]
		PlatformConsoleSubLogger() noexcept = default;
		PlatformConsoleSubLogger(const PlatformConsoleSubLogger&) = delete;
		PlatformConsoleSubLogger(PlatformConsoleSubLogger&&) = delete;

		~PlatformConsoleSubLogger() noexcept = default;

		virtual void Log(const Extension::LogEntry& logEntry) const noexcept override;

		PlatformConsoleSubLogger& operator =(const PlatformConsoleSubLogger&) = delete;
		PlatformConsoleSubLogger& operator =(PlatformConsoleSubLogger&&) = delete;
	};
}

namespace PonyEngine::Log::PlatformConsole::WinCore
{
	void PlatformConsoleSubLogger::Log(const Extension::LogEntry& logEntry) const noexcept
	{
		OutputDebugStringA(logEntry.ToString().data());
	}
}
