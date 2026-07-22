/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <cassert>

export module PonyEngine.Log.Console.Impl:ConsoleLogger;

import std;

import PonyEngine.Log.Ext;

export namespace PonyEngine::Log::Console
{
	/// @brief Logger that logs to a standard console.
	class ConsoleLogger final : public ILogger
	{
	public:
		[[nodiscard("Pure constructor")]]
		ConsoleLogger() noexcept = default;
		ConsoleLogger(const ConsoleLogger&) = delete;
		ConsoleLogger(ConsoleLogger&&) = delete;

		~ConsoleLogger() noexcept = default;

		virtual void Log(std::string_view formattedMessage, const LogEntry& logEntry) noexcept override;

		ConsoleLogger& operator =(const ConsoleLogger&) = delete;
		ConsoleLogger& operator =(ConsoleLogger&&) = delete;

	private:
		/// @brief Gets a log stream depending on the @p logType.
		/// @param logType Log type.
		/// @return Log stream.
		[[nodiscard("Pure function")]]
		static std::ostream& GetStream(LogType logType) noexcept;
	};
}

namespace PonyEngine::Log::Console
{
	void ConsoleLogger::Log(const std::string_view formattedMessage, const LogEntry& logEntry) noexcept
	{
		try
		{
			GetStream(logEntry.logType) << formattedMessage;
		}
		catch (...)
		{
			// Strange but nothing to do.
		}
	}

	std::ostream& ConsoleLogger::GetStream(const LogType logType) noexcept
	{
		switch (logType)
		{
		case LogType::Verbose:
		case LogType::Debug:
		case LogType::Info:
			return std::cout;
		case LogType::Warning:
			return std::clog;
		case LogType::Error:
		case LogType::Fatal:
			return std::cerr;
		default:
			assert(false && "Unsupported log type.");
			return std::cerr;
		}
	}
}
