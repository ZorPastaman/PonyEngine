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

export module PonyEngine.Log.Console:ConsoleSubLogger;

import std;

import PonyEngine.Log.Extension;

export namespace PonyEngine::Log
{
	/// @brief Sub-logger that writes every message to a standard console.
	class ConsoleSubLogger final : public ISubLogger
	{
	public:
		[[nodiscard("Pure constructor")]]
		ConsoleSubLogger() noexcept = default;
		ConsoleSubLogger(const ConsoleSubLogger&) = delete;
		ConsoleSubLogger(ConsoleSubLogger&&) = delete;

		~ConsoleSubLogger() noexcept = default;

		virtual void Begin() override;
		virtual void End() override;

		virtual void Log(const LogEntry& logEntry) noexcept override;

		ConsoleSubLogger& operator =(const ConsoleSubLogger&) = delete;
		ConsoleSubLogger& operator =(ConsoleSubLogger&&) = delete;
	};
}

namespace PonyEngine::Log
{
	void ConsoleSubLogger::Begin()
	{
	}

	void ConsoleSubLogger::End()
	{
	}

	void ConsoleSubLogger::Log(const LogEntry& logEntry) noexcept
	{
		try
		{
			ChooseConsoleStream(logEntry.LogType()) << logEntry;
		}
		catch (const std::exception& e)
		{
			PONY_CONSOLE_E(e, "On writing to console.");
		}
	}
}
