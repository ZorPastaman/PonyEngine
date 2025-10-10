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

#include "PonyEngine/Log/Log.h"

export module PonyEngine.Log.Main:Logger;

import std;

import PonyEngine.Application.Extension;
import PonyEngine.Log.Extension;
import PonyEngine.Text;

export namespace PonyEngine::Log
{
	/// @brief Logger.
	class Logger final : public ILogger, private ILoggerContext, private ILoggerModuleContext
	{
	public:
		/// @brief Creates a logger.
		/// @param loggerContext Logger context.
		[[nodiscard("Pure constuctor")]]
		explicit Logger(Application::ILoggerContext& loggerContext) noexcept;
		Logger(const Logger&) = delete;
		Logger(Logger&&) = delete;

		~Logger() noexcept;

		virtual void Log(LogType logType, std::string_view message, const LogData& logData = LogData()) const noexcept override;
		virtual void Log(const std::exception& exception, std::string_view message, const LogData& logData = LogData()) const noexcept override;

		[[nodiscard("Pure function")]]
		virtual Application::IApplicationContext& Application() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const Application::IApplicationContext& Application() const noexcept override;

		virtual void LogToConsole(LogType logType, std::string_view message) const noexcept override;

		[[nodiscard("Must be used to remove")]]
		virtual SubLoggerHandle AddSubLogger(const std::function<std::shared_ptr<ISubLogger>(ILoggerContext&)>& factory) override;
		virtual void RemoveSubLogger(SubLoggerHandle handle) override;

		/// @brief Gets the public logger interface.
		/// @return Logger interface.
		[[nodiscard("Pure function")]]
		ILogger& PublicLogger() noexcept;
		/// @brief Gets the public logger interface.
		/// @return Logger interface.
		[[nodiscard("Pure function")]]
		const ILogger& PublicLogger() const noexcept;
		/// @brief Gets the public logger module context.
		/// @return Logger module context.
		[[nodiscard("Pure function")]]
		ILoggerModuleContext& PublicLoggerModule() noexcept;
		/// @brief Gets the public logger module context.
		/// @return Logger module context.
		[[nodiscard("Pure function")]]
		const ILoggerModuleContext& PublicLoggerModule() const noexcept;

		Logger& operator =(const Logger&) = delete;
		Logger& operator =(Logger&&) = delete;

	private:
		/// @brief Logs the entry.
		/// @param logEntry Log entry to log.
		void Log(const LogEntry& logEntry) const noexcept;

		Application::ILoggerContext* loggerContext; ///< Logger context.

		std::vector<std::shared_ptr<ISubLogger>> subLoggers; ///< Sub-loggers.
	};
}

namespace PonyEngine::Log
{
	Logger::Logger(Application::ILoggerContext& loggerContext) noexcept :
		loggerContext{&loggerContext}
	{
	}

	Logger::~Logger() noexcept
	{
		if constexpr (IsInMask(LogType::Error, PONY_LOG_MASK))
		{
			if (subLoggers.size() > 0uz) [[unlikely]]
			{
				loggerContext->LogToConsole(LogType::Error, "Sub-loggers weren't removed:");
				for (const std::shared_ptr<ISubLogger>& subLogger : subLoggers)
				{
					loggerContext->LogToConsole(LogType::Error, Text::FormatSafe("Sub-logger: '{}'.", typeid(*subLogger).name()));
				}
			}
		}
	}

	void Logger::Log(const LogType logType, const std::string_view message, const LogData& logData) const noexcept
	{
		const auto logEntry = LogEntry(message, logData.stacktrace, nullptr, std::chrono::system_clock::now(), loggerContext->Application().FrameCount(), logType);
		Log(logEntry);
	}

	void Logger::Log(const std::exception& exception, const std::string_view message, const LogData& logData) const noexcept
	{
		const auto logEntry = LogEntry(message, logData.stacktrace, &exception, std::chrono::system_clock::now(), loggerContext->Application().FrameCount(), LogType::Exception);
		Log(logEntry);
	}

	Application::IApplicationContext& Logger::Application() noexcept
	{
		return loggerContext->Application();
	}

	const Application::IApplicationContext& Logger::Application() const noexcept
	{
		return loggerContext->Application();
	}

	void Logger::LogToConsole(const LogType logType, const std::string_view message) const noexcept
	{
		loggerContext->LogToConsole(logType, message);
	}

	SubLoggerHandle Logger::AddSubLogger(const std::function<std::shared_ptr<ISubLogger>(ILoggerContext&)>& factory)
	{
		if (loggerContext->Application().FlowState() != Application::FlowState::StartingUp) [[unlikely]]
		{
			throw std::logic_error("Sub-logger can be added only on start-up.");
		}

		const std::shared_ptr<ISubLogger> subLogger = factory(*this);
		if (!subLogger) [[unlikely]]
		{
			throw std::invalid_argument("Sub-logger is nullptr.");
		}

		subLoggers.push_back(subLogger);
		PONY_LOG(*this, LogType::Info, "'{}' sub-logger added.", typeid(*subLogger).name());

		return SubLoggerHandle{.id = subLogger.get()};
	}

	void Logger::RemoveSubLogger(const SubLoggerHandle handle)
	{
		if (loggerContext->Application().FlowState() != Application::FlowState::ShuttingDown) [[unlikely]]
		{
			throw std::logic_error("Sub-logger can be removed only on shut-down.");
		}

		if (!handle.IsValid()) [[unlikely]]
		{
			throw std::invalid_argument("Invalid handle.");
		}

		std::optional<std::size_t> indexOpt = std::nullopt;
		for (std::size_t i = subLoggers.size(); i-- > 0uz; )
		{
			if (subLoggers[i].get() == handle.id)
			{
				indexOpt = i;
				break;
			}
		}
		if (!indexOpt) [[unlikely]]
		{
			throw std::invalid_argument("Sub-logger not found.");
		}
		const std::size_t index = *indexOpt;

		PONY_LOG(*this, LogType::Info, "'{}' sub-logger removed.", typeid(*subLoggers[index]).name());
		subLoggers.erase(subLoggers.cbegin() + index);
	}

	ILogger& Logger::PublicLogger() noexcept
	{
		return *this;
	}

	const ILogger& Logger::PublicLogger() const noexcept
	{
		return *this;
	}

	ILoggerModuleContext& Logger::PublicLoggerModule() noexcept
	{
		return *this;
	}

	const ILoggerModuleContext& Logger::PublicLoggerModule() const noexcept
	{
		return *this;
	}

	void Logger::Log(const LogEntry& logEntry) const noexcept
	{
		LogToConsole(logEntry.LogType(), logEntry.ToString());

		for (const std::shared_ptr<ISubLogger>& subLogger : subLoggers)
		{
			subLogger->Log(logEntry);
		}
	}
}
