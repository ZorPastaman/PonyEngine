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
#include <chrono>

export module PonyEngine.Debug.Log.Logger;

import <algorithm>;
import <exception>;
import <iostream>;
import <string>;
import <vector>;
import <utility>;

import PonyEngine.IEngine;
import PonyEngine.Debug.Log.ILogger;
import PonyEngine.Debug.Log.ISubLogger;
import PonyEngine.Debug.Log.LogEntry;
import PonyEngine.Debug.Log.LogType;

namespace PonyEngine::Debug::Log
{
	/// @brief Default logger. It just resends logs to its sub-loggers.
	export class Logger final : public ILogger
	{
	public:
		/// @brief Creates a @p Logger.
		/// @param engine Engine that the logger is owned by.
		Logger(const IEngine* engine) noexcept;
		Logger(const Logger&) = delete;
		/// @brief Move constructor.
		/// @param other Move source.
		Logger(Logger&& other) noexcept;

		virtual ~Logger() noexcept = default;

		virtual void Log(LogType logType, const std::string& message) noexcept override;
		virtual void LogException(const std::exception& exception, const std::string& message = "") noexcept override;

		virtual void AddSubLogger(ISubLogger* subLogger) override;
		virtual void RemoveSubLogger(ISubLogger* subLogger) override;

	private:
		std::vector<ISubLogger*> m_subLoggers; /// @brief sub-loggers container.

		const IEngine* const m_engine; /// @brief Engine the owner of the @p Logger.
	};

	Logger::Logger(const IEngine* const engine) noexcept :
		m_subLoggers{},
		m_engine{engine}
	{
		assert((engine != nullptr));
	}

	Logger::Logger(Logger&& other) noexcept :
		m_subLoggers(std::move(other.m_subLoggers)),
		m_engine{other.m_engine}
	{
	}

	void Logger::Log(const LogType logType, const std::string& message) noexcept
	{
		assert((logType == LogType::Verbose || logType == LogType::Debug || logType == LogType::Info || logType == LogType::Warning || logType == LogType::Error));

		try
		{
			const LogEntry logEntry(message, nullptr, std::chrono::system_clock::now(), m_engine->GetFrameCount(), logType);

			for (ISubLogger* const subLogger : m_subLoggers)
			{
				subLogger->Log(logEntry);
			}
		}
		catch (const std::exception& e)
		{
			std::cerr << e.what() << " on writing to log.";
		}
	}

	void Logger::LogException(const std::exception& exception, const std::string& message) noexcept
	{
		try
		{
			const LogEntry logEntry(message, &exception, std::chrono::system_clock::now(), m_engine->GetFrameCount(), LogType::Exception);

			for (ISubLogger* const subLogger : m_subLoggers)
			{
				subLogger->Log(logEntry);
			}
		}
		catch (const std::exception& e)
		{
			std::cerr << e.what() << " on writing to log.";
		}
	}

	void Logger::AddSubLogger(ISubLogger* const subLogger)
	{
		assert((subLogger != nullptr));
		m_subLoggers.push_back(subLogger);
	}

	void Logger::RemoveSubLogger(ISubLogger* const subLogger)
	{
		const std::vector<ISubLogger*>::iterator position = std::find(m_subLoggers.begin(), m_subLoggers.end(), subLogger);

		if (position != m_subLoggers.end())
		{
			m_subLoggers.erase(position);
		}
	}
}
