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
import <string>;
import <vector>;

import PonyEngine.Debug.Log;

namespace PonyEngine::Debug::Log
{
	/// @brief Default logger. It just resends logs to its sub-loggers.
	export class Logger final : public ILogger
	{
	public:
		[[nodiscard("Pure constructor")]]
		inline Logger() noexcept = default;
		Logger(const Logger&) = delete;
		[[nodiscard("Pure constructor")]]
		inline Logger(Logger&& other) noexcept = default;

		inline virtual ~Logger() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual const char* GetName() const noexcept override;

		virtual void Log(LogType logType, const LogInput& logInput) noexcept override;
		virtual void LogException(const std::exception& exception, const LogInput& logInput) noexcept override;

		virtual void AddSubLogger(ISubLogger* subLogger) override;
		virtual void RemoveSubLogger(ISubLogger* subLogger) override;

		Logger& operator =(const Logger&) = delete;
		inline Logger& operator =(Logger&& other) noexcept = default;

		static const char* const Name; /// @brief Class name.

	private:
		std::vector<ISubLogger*> m_subLoggers; /// @brief Sub-loggers container.
	};

	const char* Logger::GetName() const noexcept
	{
		return Name;
	}

	void Logger::Log(const LogType logType, const LogInput& logInput) noexcept
	{
		assert((logType == LogType::Verbose || logType == LogType::Debug || logType == LogType::Info || logType == LogType::Warning || logType == LogType::Error));

		try
		{
			const LogEntry logEntry(logInput.message, nullptr, std::chrono::system_clock::now(), logInput.frameCount, logType);

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
			const LogEntry logEntry(logInput.message, &exception, std::chrono::system_clock::now(), logInput.frameCount, LogType::Exception);

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
		PONY_CONSOLE(LogType::Info, std::format("Add a sub-logger '{}'.", subLogger->GetName()));
		m_subLoggers.push_back(subLogger);
	}

	void Logger::RemoveSubLogger(ISubLogger* const subLogger)
	{
		PONY_CONSOLE_IF(subLogger == nullptr, LogType::Warning, "Tried to remove a nullptr sub-logger.");

		const std::vector<ISubLogger*>::const_iterator position = std::find(m_subLoggers.cbegin(), m_subLoggers.cend(), subLogger);

		if (position != m_subLoggers.cend()) [[likely]]
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
