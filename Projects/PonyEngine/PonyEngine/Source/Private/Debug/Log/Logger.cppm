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

#include "PonyEngine/Log/LogMacro.h"

export module PonyEngine.Log.Implementation:Logger;

import <algorithm>;
import <chrono>;
import <format>;
import <exception>;
import <iostream>;
import <string>;
import <vector>;

import PonyEngine.Log;

export namespace PonyEngine::Log
{
	/// @brief Default logger. It just resends logs to its sub-loggers.
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

		virtual void AddSubLogger(ISubLogger* subLogger) override;
		virtual void RemoveSubLogger(ISubLogger* subLogger) override;

		[[nodiscard("Pure function")]]
		virtual const char* GetName() const noexcept override;

		Logger& operator =(const Logger&) = delete;
		Logger& operator =(Logger&&) = delete;

		static constexpr const char* StaticName = "PonyEngine::Log::Logger"; ///< Class name.

	private:
		std::vector<ISubLogger*> subLoggers; ///< Sub-loggers container.
	};
}

namespace PonyEngine::Log
{
	void Logger::Log(const LogType logType, const LogInput& logInput) noexcept
	{
		assert((logType == LogType::Verbose || logType == LogType::Debug || logType == LogType::Info || logType == LogType::Warning || logType == LogType::Error));

		const LogEntry logEntry(logInput.GetMessage(), nullptr, std::chrono::system_clock::now(), logInput.GetFrameCount(), logType);

		for (ISubLogger* const subLogger : subLoggers)
		{
			try
			{
				subLogger->Log(logEntry);
			}
			catch (const std::exception& e)
			{
				PONY_CONSOLE(LogType::Exception, std::format("{} - On writing to the sublogger '{}'.", e.what(), subLogger->GetName()));
			}
		}
	}

	void Logger::LogException(const std::exception& exception, const LogInput& logInput) noexcept
	{
		const LogEntry logEntry(logInput.GetMessage(), &exception, std::chrono::system_clock::now(), logInput.GetFrameCount(), LogType::Exception);

		for (ISubLogger* const subLogger : subLoggers)
		{
			try
			{
				subLogger->Log(logEntry);
			}
			catch (const std::exception& e)
			{
				PONY_CONSOLE(LogType::Exception, std::format("{} - On writing to the log.", e.what()));
			}
		}
	}

	void Logger::AddSubLogger(ISubLogger* const subLogger)
	{
		assert((subLogger && "The sub-logger is nullptr."));
		assert((std::ranges::find(std::as_const(subLoggers), subLogger) == subLoggers.cend() && "The sub-logger is already added."));
		PONY_CONSOLE(LogType::Info, std::format("Add sub-logger '{}'.", subLogger->GetName()));
		subLoggers.push_back(subLogger);
		PONY_CONSOLE(LogType::Info, "Sub-logger added.");
	}

	void Logger::RemoveSubLogger(ISubLogger* const subLogger)
	{
		PONY_CONSOLE_IF(subLogger == nullptr, LogType::Warning, "Tried to remove a nullptr sub-logger.");

		if (const auto position = std::ranges::find(std::as_const(subLoggers), subLogger); position != subLoggers.cend()) [[likely]]
		{
			PONY_CONSOLE(LogType::Info, std::format("Remove a sub-logger '{}'.", subLogger->GetName()));
			subLoggers.erase(position);
			PONY_CONSOLE(LogType::Info, "Sub-logger removed.");
		}
		else [[unlikely]]
		{
			PONY_CONSOLE_IF(subLogger != nullptr, LogType::Warning, std::format("Tried to remove a not added sub-logger '{}'.", subLogger->GetName()));
		}
	}

	const char* Logger::GetName() const noexcept
	{
		return StaticName;
	}
}
