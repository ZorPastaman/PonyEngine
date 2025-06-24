/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Log/Log.h"

export module PonyEngine.Log.Core:Logger;

import std;

import PonyEngine.Application;
import PonyEngine.Core;
import PonyEngine.Log.Extension;

export namespace PonyEngine::Log
{
	/// @brief Logger.
	class Logger final : public Core::ILogger, private ILogger
	{
	public:
		/// @brief Creates a logger.
		/// @param application Application context.
		[[nodiscard("Pure constuctor")]]
		explicit Logger(Application::IApplicationContext& application);
		Logger(const Logger&) = delete;
		Logger(Logger&&) = delete;

		~Logger() noexcept;

		virtual void Log(LogType logType, const LogInput& logInput) const noexcept override;
		virtual void Log(const std::exception& exception, const LogInput& logInput) const noexcept override;

		[[nodiscard("Pure function")]]
		virtual Log::ILogger& PublicLogger() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const Log::ILogger& PublicLogger() const noexcept override;

		/// @brief Gets the logger context.
		/// @return Logger context.
		[[nodiscard("Pure function")]]
		ILoggerContext& Context() noexcept;
		/// @brief Gets the logger context.
		/// @return Logger context.
		[[nodiscard("Pure function")]]
		const ILoggerContext& Context() const noexcept;

		/// @brief Gets the sub-loggers.
		/// @return Sub-loggers.
		[[nodiscard("Pure function")]]
		const std::vector<std::shared_ptr<ISubLogger>>& SubLoggers() const noexcept;
		/// @brief Sets the sub-loggers.
		/// @param subLoggers Sub-loggers. Must be created with this logger context.
		void SubLoggers(const std::vector<std::shared_ptr<ISubLogger>>& subLoggers);
		/// @brief Sets the sub-loggers.
		/// @param subLoggers Sub-loggers. Must be created with this logger context.
		void SubLoggers(std::vector<std::shared_ptr<ISubLogger>>&& subLoggers);

		Logger& operator =(const Logger&) = delete;
		Logger& operator =(Logger&&) = delete;

	private:
		/// @brief Logger context.
		class LoggerContext final : public ILoggerContext
		{
		public:
			/// @brief Creates a logger context.
			/// @param logger Logger.
			[[nodiscard("Pure constructor")]]
			explicit LoggerContext(Logger& logger) noexcept;
			LoggerContext(const LoggerContext&) = delete;
			LoggerContext(LoggerContext&&) = delete;

			~LoggerContext() noexcept = default;

			[[nodiscard("Pure function")]]
			virtual Application::IApplicationContext& Application() noexcept override;
			[[nodiscard("Pure function")]]
			virtual const Application::IApplicationContext& Application() const noexcept override;

			LoggerContext& operator =(const LoggerContext&) = delete;
			LoggerContext& operator =(LoggerContext&&) = delete;

		private:
			Logger* logger; ///< Logger.
		};

		void Begin();
		void End(std::size_t count) noexcept;

		/// @brief Logs the entry.
		/// @param logEntry Log entry to log.
		void Log(const LogEntry& logEntry) const noexcept;

		Application::IApplicationContext* application; ///< Application context.

		LoggerContext loggerContext; ///< Logger context.
		std::vector<std::shared_ptr<ISubLogger>> subLoggers; ///< Sub-loggers.
	};
}

namespace PonyEngine::Log
{
	Logger::Logger(Application::IApplicationContext& application) :
		application{&application},
		loggerContext(*this)
	{
	}

	Logger::~Logger() noexcept
	{
		End(subLoggers.size());
	}

	void Logger::Log(const LogType logType, const LogInput& logInput) const noexcept
	{
		const auto logEntry = LogEntry(logInput.message, logInput.stacktrace, nullptr, std::chrono::system_clock::now(), logInput.frameCount, logType);
		Log(logEntry);
	}

	void Logger::Log(const std::exception& exception, const LogInput& logInput) const noexcept
	{
		const auto logEntry = LogEntry(logInput.message, logInput.stacktrace, &exception, std::chrono::system_clock::now(), logInput.frameCount, LogType::Exception);
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

	ILoggerContext& Logger::Context() noexcept
	{
		return loggerContext;
	}

	const ILoggerContext& Logger::Context() const noexcept
	{
		return loggerContext;
	}

	const std::vector<std::shared_ptr<ISubLogger>>& Logger::SubLoggers() const noexcept
	{
		return subLoggers;
	}

	void Logger::SubLoggers(const std::vector<std::shared_ptr<ISubLogger>>& subLoggers)
	{
		this->subLoggers = subLoggers;
		Begin();
	}

	void Logger::SubLoggers(std::vector<std::shared_ptr<ISubLogger>>&& subLoggers)
	{
		this->subLoggers = std::move(subLoggers);
		Begin();
	}

	Logger::LoggerContext::LoggerContext(Logger& logger) noexcept :
		logger{&logger}
	{
	}

	Application::IApplicationContext& Logger::LoggerContext::Application() noexcept
	{
		return *logger->application;
	}

	const Application::IApplicationContext& Logger::LoggerContext::Application() const noexcept
	{
		return *logger->application;
	}

	void Logger::Begin()
	{
		for (std::size_t i = 0Z; i < subLoggers.size(); ++i)
		{
			const std::shared_ptr<ISubLogger>& subLogger = subLoggers[i];
			try
			{
				subLogger->Begin();
			}
			catch (const std::exception& e)
			{
				PONY_LOG_E(application->Logger(), e, "On beginning '{}' sub-logger.", typeid(*subLogger).name());
				End(i);

				throw;
			}
			catch (...)
			{
				PONY_LOG(application->Logger(), LogType::Exception, "Unknown exception on beginning '{}' sub-logger.", typeid(*subLogger).name());
				End(i);

				throw;
			}
		}
	}

	void Logger::End(const std::size_t count) noexcept
	{
		for (std::size_t i = count; i-- > 0Z; )
		{
			subLoggers[i]->End();
		}

		subLoggers.clear();
	}

	void Logger::Log(const LogEntry& logEntry) const noexcept
	{
		for (const std::shared_ptr<ISubLogger>& subLogger : subLoggers)
		{
			subLogger->Log(logEntry);
		}
	}
}
