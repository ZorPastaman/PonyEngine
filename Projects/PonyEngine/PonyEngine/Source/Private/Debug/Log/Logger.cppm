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

#include "Debug/Log/LogMacro.h"

export module PonyEngine.Debug.Log.Implementation:Logger;

import <algorithm>;
import <chrono>;
import <format>;
import <exception>;
import <iostream>;
import <ranges>;
import <string>;
import <vector>;

import PonyEngine.Debug.Log;

export namespace PonyEngine::Debug::Log
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

		[[nodiscard("Pure function")]]
		virtual const char* GetName() const noexcept override;

		virtual void Log(LogType logType, const LogInput& logInput) noexcept override;
		virtual void LogException(const std::exception& exception, const LogInput& logInput) noexcept override;

		virtual void AddSubLogger(ISubLogger* subLogger) override;
		virtual void RemoveSubLogger(ISubLogger* subLogger) override;

		Logger& operator =(const Logger&) = delete;
		Logger& operator =(Logger&&) = delete;

		static const char* const Name; ///< Class name.

	private:
		std::vector<ISubLogger*> m_subLoggers; ///< Sub-loggers container.
	};
}

namespace PonyEngine::Debug::Log
{
	const char* Logger::GetName() const noexcept
	{
		return Name;
	}

	void Logger::Log(const LogType logType, const LogInput& logInput) noexcept
	{
		assert((logType == LogType::Verbose || logType == LogType::Debug || logType == LogType::Info || logType == LogType::Warning || logType == LogType::Error));

		try
		{
			const LogEntry logEntry(logInput.GetMessage(), nullptr, std::chrono::system_clock::now(), logInput.GetFrameCount(), logType);

			for (ISubLogger* const subLogger : m_subLoggers)
			{
				subLogger->Log(logEntry);
			}
		}
		catch (const std::exception& e)
		{
			PONY_CONSOLE(LogType::Exception, std::format("{} - {}.", e.what(), "On writing to the log"));
		}
	}

	void Logger::LogException(const std::exception& exception, const LogInput& logInput) noexcept
	{
		try
		{
			const LogEntry logEntry(logInput.GetMessage(), &exception, std::chrono::system_clock::now(), logInput.GetFrameCount(), LogType::Exception);

			for (ISubLogger* const subLogger : m_subLoggers)
			{
				subLogger->Log(logEntry);
			}
		}
		catch (const std::exception& e)
		{
			PONY_CONSOLE(LogType::Exception, std::format("{} - {}.", e.what(), "On writing to the log"));
		}
	}

	void Logger::AddSubLogger(ISubLogger* const subLogger)
	{
		assert((subLogger != nullptr));
		assert((std::ranges::find(std::as_const(m_subLoggers), subLogger) == m_subLoggers.cend()));
		PONY_CONSOLE(LogType::Info, std::format("Add a sub-logger '{}'.", subLogger->GetName()));
		m_subLoggers.push_back(subLogger);
	}

	void Logger::RemoveSubLogger(ISubLogger* const subLogger)
	{
		PONY_CONSOLE_IF(subLogger == nullptr, LogType::Warning, "Tried to remove a nullptr sub-logger.");

		if (const auto position = std::ranges::find(std::as_const(m_subLoggers), subLogger); position != m_subLoggers.cend()) [[likely]]
		{
			PONY_CONSOLE(LogType::Info, std::format("Remove a sub-logger '{}'.", subLogger->GetName()));
			m_subLoggers.erase(position);
		}
		else [[unlikely]]
		{
			PONY_CONSOLE_IF(subLogger != nullptr, LogType::Warning, std::format("Tried to remove a not added sub-logger '{}'.", subLogger->GetName()));
		}
	}

	const char* const Logger::Name = "PonyEngine::Debug::Logger";
}
