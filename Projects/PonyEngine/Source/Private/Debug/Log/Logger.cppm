/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Debug.Log.Implementation:Logger;

import <algorithm>;
import <cassert>;
import <chrono>;
import <exception>;
import <iostream>;
import <functional>;
import <string>;
import <vector>;
import <utility>;

import PonyEngine.Debug.Log;

namespace PonyEngine::Debug::Log
{
	/// @brief Default logger. It just resends logs to its sub-loggers.
	export class Logger final : public ILogger
	{
	public:
		/// @brief Creates a @p Logger.
		/// @param frameCountProvider Current frame provider.
		[[nodiscard("Pure constructor")]]
		Logger(const std::function<std::size_t()>& frameCountProvider);
		Logger(const Logger&) = delete;
		/// @brief Move constructor.
		/// @param other Move source.
		[[nodiscard("Pure constructor")]]
		Logger(Logger&& other) noexcept;

		virtual ~Logger() noexcept = default;

		virtual void Log(LogType logType, const std::string& message) noexcept override;
		virtual void LogException(const std::exception& exception, const std::string& message = "") noexcept override;

		virtual void AddSubLogger(ISubLogger* subLogger) override;
		virtual void RemoveSubLogger(ISubLogger* subLogger) override;

	private:
		const std::function<std::size_t()> m_frameCountProvider; /// @brief Current frame provider.

		std::vector<ISubLogger*> m_subLoggers; /// @brief sub-loggers container.
	};

	Logger::Logger(const std::function<std::size_t()>& frameCountProvider) :
		m_frameCountProvider(frameCountProvider),
		m_subLoggers{}
		
	{
	}

	Logger::Logger(Logger&& other) noexcept :
		m_frameCountProvider(std::move(other.m_frameCountProvider)),
		m_subLoggers(std::move(other.m_subLoggers))
	{
	}

	void Logger::Log(const LogType logType, const std::string& message) noexcept
	{
		assert((logType == LogType::Verbose || logType == LogType::Debug || logType == LogType::Info || logType == LogType::Warning || logType == LogType::Error));

		try
		{
			const LogEntry logEntry(message, nullptr, std::chrono::system_clock::now(), m_frameCountProvider(), logType);

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
			const LogEntry logEntry(message, &exception, std::chrono::system_clock::now(), m_frameCountProvider(), LogType::Exception);

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

		if (position != m_subLoggers.end()) [[likely]]
		{
			m_subLoggers.erase(position);
		}
	}
}
