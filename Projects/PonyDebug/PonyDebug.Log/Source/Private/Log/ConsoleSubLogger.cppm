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

export module PonyDebug.Log.Implementation:ConsoleSubLogger;

import <exception>;
import <ostream>;

import PonyDebug.Log;

export namespace PonyDebug::Log
{
	/// @brief Sub-logger that sends logs to std::cout, std::clog and std::cerr.
	class ConsoleSubLogger final : public ISubLogger
	{
	public:
		[[nodiscard("Pure constructor")]]
		ConsoleSubLogger() noexcept = default;
		ConsoleSubLogger(const ConsoleSubLogger&) = delete;
		ConsoleSubLogger(ConsoleSubLogger&&) = delete;

		~ConsoleSubLogger() noexcept = default;

		virtual void Log(const LogEntry& logEntry) noexcept override;

		[[nodiscard("Pure function")]]
		virtual const char* Name() const noexcept override;

		ConsoleSubLogger& operator =(const ConsoleSubLogger&) = delete;
		ConsoleSubLogger& operator =(ConsoleSubLogger&&) = delete;

		static constexpr auto StaticName = "PonyDebug::Log::ConsoleSubLogger"; ///< Class name.
	};
}

namespace PonyDebug::Log
{
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

	const char* ConsoleSubLogger::Name() const noexcept
	{
		return StaticName;
	}
}
