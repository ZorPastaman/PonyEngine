/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Log.Core:Logger;

import std;

import PonyEngine.Core;
import PonyEngine.Log.Extension;

export namespace PonyEngine::Log::Core
{
	/// @brief Logger.
	class Logger final : public PonyEngine::Core::ILogger, private ILogger
	{
	public:
		[[nodiscard("Pure constuctor")]]
		Logger() noexcept = default;
		Logger(const Logger&) = delete;
		Logger(Logger&&) = delete;

		~Logger() noexcept = default;

		virtual void Log(LogType logType, const LogInput& logInput) const noexcept override;
		virtual void Log(const std::exception& exception, const LogInput& logInput) const noexcept override;

		[[nodiscard("Pure function")]]
		virtual Log::ILogger& PublicLogger() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const Log::ILogger& PublicLogger() const noexcept override;

		/// @brief Reserves a memory for sub-loggers.
		/// @param subLoggerCount Sub-logger count.
		void Reserve(std::size_t subLoggerCount);
		/// @brief Adds a sub-logger.
		/// @param subLogger Sub-logger to add.
		void AddSubLogger(const std::shared_ptr<Extension::ISubLogger>& subLogger);

		Logger& operator =(const Logger&) = delete;
		Logger& operator =(Logger&&) = delete;

	private:
		/// @brief Logs the entry.
		/// @param logEntry Log entry to log.
		void Log(const Extension::LogEntry& logEntry) const noexcept;

		std::vector<std::shared_ptr<Extension::ISubLogger>> subLoggers; ///< Sub-loggers.
	};
}

namespace PonyEngine::Log::Core
{
	void Logger::Log(const LogType logType, const LogInput& logInput) const noexcept
	{
		const auto logEntry = Extension::LogEntry(logInput.message, logInput.stacktrace, nullptr, std::chrono::system_clock::now(), logInput.frameCount, logType);
		Log(logEntry);
	}

	void Logger::Log(const std::exception& exception, const LogInput& logInput) const noexcept
	{
		const auto logEntry = Extension::LogEntry(logInput.message, logInput.stacktrace, &exception, std::chrono::system_clock::now(), logInput.frameCount, LogType::Exception);
		Log(logEntry);
	}

	Log::ILogger& Logger::PublicLogger() noexcept
	{
		return *this;
	}

	const Log::ILogger& Logger::PublicLogger() const noexcept
	{
		return *this;
	}

	void Logger::Reserve(const std::size_t subLoggerCount)
	{
		subLoggers.reserve(subLoggerCount);
	}

	void Logger::AddSubLogger(const std::shared_ptr<Extension::ISubLogger>& subLogger)
	{
		subLoggers.push_back(subLogger);
	}

	void Logger::Log(const Extension::LogEntry& logEntry) const noexcept
	{
		for (const std::shared_ptr<Extension::ISubLogger>& subLogger : subLoggers)
		{
			subLogger->Log(logEntry);
		}
	}
}
