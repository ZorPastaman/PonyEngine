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

export namespace PonyEngine::Log::WinCore
{
	/// @brief Sub-logger that writes every message to the OutputDebugString.
	class PlatformConsoleSubLogger final : public ISubLogger
	{
	public:
		[[nodiscard("Pure constructor")]]
		PlatformConsoleSubLogger() noexcept = default;
		PlatformConsoleSubLogger(const PlatformConsoleSubLogger&) = delete;
		PlatformConsoleSubLogger(PlatformConsoleSubLogger&&) = delete;

		~PlatformConsoleSubLogger() noexcept = default;

		virtual void Begin() override;
		virtual void End() noexcept override;

		virtual void Log(const LogEntry& logEntry) noexcept override;

		PlatformConsoleSubLogger& operator =(const PlatformConsoleSubLogger&) = delete;
		PlatformConsoleSubLogger& operator =(PlatformConsoleSubLogger&&) = delete;
	};
}

namespace PonyEngine::Log::WinCore
{
	void PlatformConsoleSubLogger::Begin()
	{
	}

	void PlatformConsoleSubLogger::End() noexcept
	{
	}

	void PlatformConsoleSubLogger::Log(const LogEntry& logEntry) noexcept
	{
		OutputDebugStringA(logEntry.ToString().data());
	}
}
