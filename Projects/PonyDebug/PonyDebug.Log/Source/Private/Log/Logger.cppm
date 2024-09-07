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

#include "PonyDebug/Log/Log.h"

export module PonyDebug.Log.Implementation:Logger;

import <algorithm>;
import <chrono>;
import <format>;
import <exception>;
import <utility>;
import <vector>;

import PonyDebug.Log;

export namespace PonyDebug::Log
{
	/// @brief Logger.
	/// @details It just resends logs to its sub-loggers.
	class Logger final : public ILogger
	{
	public:
		[[nodiscard("Pure constructor")]]
		Logger() noexcept = default;
		Logger(const Logger&) = delete;
		Logger(Logger&&) noexcept = delete;

		~Logger() noexcept = default;

		virtual void Log(LogType logType, const LogInput& logInput) noexcept override;
		virtual void LogException(const std::exception& exception, const LogInput& logInput) noexcept override;

		virtual void AddSubLogger(ISubLogger& subLogger) override;
		virtual void RemoveSubLogger(ISubLogger& subLogger) override;

		[[nodiscard("Pure function")]]
		virtual const char* Name() const noexcept override;

		Logger& operator =(const Logger&) = delete;
		Logger& operator =(Logger&&) = delete;

		static constexpr auto StaticName = "PonyDebug::Log::Logger"; ///< Class name.

	private:
		std::vector<ISubLogger*> subLoggers; ///< Sub-loggers container.
	};
}

namespace PonyDebug::Log
{
	void Logger::Log(const LogType logType, const LogInput& logInput) noexcept
	{
		const auto logEntry = LogEntry(logInput.message, nullptr, std::chrono::system_clock::now(), logInput.frameCount, logType);

		for (ISubLogger* const subLogger : subLoggers)
		{
			subLogger->Log(logEntry);
		}
	}

	void Logger::LogException(const std::exception& exception, const LogInput& logInput) noexcept
	{
		const auto logEntry = LogEntry(logInput.message, &exception, std::chrono::system_clock::now(), logInput.frameCount, LogType::Exception);

		for (ISubLogger* const subLogger : subLoggers)
		{
			subLogger->Log(logEntry);
		}
	}

	void Logger::AddSubLogger(ISubLogger& subLogger)
	{
		assert(std::ranges::find(std::as_const(subLoggers), &subLogger) == subLoggers.cend() && "The sub-logger has already been added.");
		subLoggers.push_back(&subLogger);
		PONY_CONSOLE(LogType::Debug, "'{}' sub-logger added.", subLogger.Name());
	}

	void Logger::RemoveSubLogger(ISubLogger& subLogger)
	{
		if (const auto position = std::ranges::find(std::as_const(subLoggers), &subLogger); position != subLoggers.cend()) [[likely]]
		{
			subLoggers.erase(position);
			PONY_CONSOLE(LogType::Debug, "'{}' sub-logger removed.", subLogger.Name());
		}
		else [[unlikely]]
		{
			PONY_CONSOLE(LogType::Warning, "Tried to remove not added sub-logger '{}'.", subLogger.Name());
		}
	}

	const char* Logger::Name() const noexcept
	{
		return StaticName;
	}
}