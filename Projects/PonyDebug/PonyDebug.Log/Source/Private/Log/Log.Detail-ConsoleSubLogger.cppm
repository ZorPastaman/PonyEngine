/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyDebug/Log/Log.h"

export module PonyDebug.Log.Detail:ConsoleSubLogger;

import <exception>;
import <ostream>;

import PonyDebug.Log;

export namespace PonyDebug::Log
{
	/// @brief Sub-logger that sends logs to std::cout, std::clog and std::cerr.
	class ConsoleSubLogger final : public SubLogger
	{
	public:
		/// @brief Creates a @p ConsoleSubLogger.
		/// @param params Console sub-logger parameters.
		[[nodiscard("Pure constructor")]]
		explicit ConsoleSubLogger(const ConsoleSubLoggerParams& params) noexcept;
		ConsoleSubLogger(const ConsoleSubLogger&) = delete;
		ConsoleSubLogger(ConsoleSubLogger&&) = delete;

		virtual ~ConsoleSubLogger() noexcept override = default;

		virtual void Log(const LogEntry& logEntry) const noexcept override;

		ConsoleSubLogger& operator =(const ConsoleSubLogger&) = delete;
		ConsoleSubLogger& operator =(ConsoleSubLogger&&) = delete;
	};
}

namespace PonyDebug::Log
{
	ConsoleSubLogger::ConsoleSubLogger(const ConsoleSubLoggerParams&) noexcept
	{
	}

	void ConsoleSubLogger::Log(const LogEntry& logEntry) const noexcept
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
