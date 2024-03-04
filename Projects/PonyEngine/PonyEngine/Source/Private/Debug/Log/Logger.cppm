/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "Debug/Log/LogMacro.h"

export module PonyEngine.Debug.Log.Implementation:Logger;

import <algorithm>;
import <cassert>;
import <chrono>;
import <format>;
import <exception>;
import <iostream>;
import <string>;
import <vector>;
import <utility>;

import PonyEngine.Core;
import PonyEngine.Debug.Log;

import :IEngineLogger;

namespace PonyEngine::Debug::Log
{
	/// @brief Default logger. It just resends logs to its sub-loggers.
	export class Logger final : public IEngineLogger
	{
	public:
		/// @brief Creates a @p Logger.
		/// @param engine Engine that owns this logger.
		[[nodiscard("Pure constructor")]]
		inline Logger(const Core::IEngine& engine) noexcept;
		Logger(const Logger&) = delete;
		/// @brief Move constructor.
		/// @param other Move source.
		[[nodiscard("Pure constructor")]]
		inline Logger(Logger&& other) noexcept;

		inline virtual ~Logger() noexcept = default;

		virtual void Log(LogType logType, const std::string& message) noexcept override;
		virtual void LogException(const std::exception& exception, const std::string& message = "") noexcept override;

		virtual void AddSubLogger(ISubLogger* subLogger) override;
		virtual void RemoveSubLogger(ISubLogger* subLogger) override;

	private:
		std::vector<ISubLogger*> m_subLoggers; /// @brief sub-loggers container.

		const Core::IEngine& m_engine; /// @brief Engine that owns this logger.
	};

	inline Logger::Logger(const Core::IEngine& engine) noexcept :
		m_subLoggers{},
		m_engine{engine}
	{
	}

	inline Logger::Logger(Logger&& other) noexcept :
		m_subLoggers(std::move(other.m_subLoggers)),
		m_engine{other.m_engine}
	{
	}

	void Logger::Log(const LogType logType, const std::string& message) noexcept
	{
		assert((logType == LogType::Verbose || logType == LogType::Debug || logType == LogType::Info || logType == LogType::Warning || logType == LogType::Error));

		try
		{
			const LogEntry logEntry(message, nullptr, std::chrono::system_clock::now(), m_engine.GetFrameCount(), logType);

			for (ISubLogger* const subLogger : m_subLoggers)
			{
				subLogger->Log(logEntry);
			}
		}
		catch (const std::exception& e)
		{
			PONY_CEXC(e, "On writing to the log.");
		}
	}

	void Logger::LogException(const std::exception& exception, const std::string& message) noexcept
	{
		try
		{
			const LogEntry logEntry(message, &exception, std::chrono::system_clock::now(), m_engine.GetFrameCount(), LogType::Exception);

			for (ISubLogger* const subLogger : m_subLoggers)
			{
				subLogger->Log(logEntry);
			}
		}
		catch (const std::exception& e)
		{
			PONY_CEXC(e, "On writing to the log.");
		}
	}

	void Logger::AddSubLogger(ISubLogger* const subLogger)
	{
		assert((subLogger != nullptr));
		PONY_COUT(std::format("Add a sub-logger '{}'.", subLogger->GetName()));
		m_subLoggers.push_back(subLogger);
	}

	void Logger::RemoveSubLogger(ISubLogger* const subLogger)
	{
		PONY_CLOG_IF(subLogger == nullptr, "Tried to remove a nullptr sub-logger.");

		const std::vector<ISubLogger*>::const_iterator position = std::find(m_subLoggers.cbegin(), m_subLoggers.cend(), subLogger);

		if (position != m_subLoggers.cend()) [[likely]]
		{
			PONY_COUT(std::format("Remove a sub-logger '{}'.", subLogger->GetName()));
			m_subLoggers.erase(position);
		}
		else [[unlikely]]
		{
			PONY_CLOG_IF(subLogger != nullptr, std::format("Tried to remove a not added sub-logger '{}'.", subLogger->GetName()));
		}
	}
}
