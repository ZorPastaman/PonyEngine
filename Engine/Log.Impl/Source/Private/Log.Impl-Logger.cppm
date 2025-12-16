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

#include "PonyEngine/Log/Console.h"

export module PonyEngine.Log.Impl:Logger;

import std;

import PonyEngine.Application.Ext;
import PonyEngine.Log.Ext;

import :LogFiller;
import :SubLoggerContainer;

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

		virtual void Log(LogType logType, std::string_view message) const noexcept override;
		virtual void Log(LogType logType, std::string_view format, std::format_args formatArgs) const noexcept override;
		virtual void Log(LogType logType, std::string_view message, const std::stacktrace& stacktrace) const noexcept override;
		virtual void Log(LogType logType, std::string_view format, std::format_args formatArgs, const std::stacktrace& stacktrace) const noexcept override;

		virtual void Log(const std::exception_ptr& exception) const noexcept override;
		virtual void Log(const std::exception_ptr& exception, std::string_view message) const noexcept override;
		virtual void Log(const std::exception_ptr& exception, std::string_view format, std::format_args formatArgs) const noexcept override;
		virtual void Log(const std::exception_ptr& exception, const std::stacktrace& stacktrace) const noexcept override;
		virtual void Log(const std::exception_ptr& exception, std::string_view message, const std::stacktrace& stacktrace) const noexcept override;
		virtual void Log(const std::exception_ptr& exception, std::string_view format, std::format_args formatArgs, const std::stacktrace& stacktrace) const noexcept override;

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
		[[nodiscard("Pure function")]]
		virtual Application::IApplicationContext& Application() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const Application::IApplicationContext& Application() const noexcept override;

		virtual void LogToConsole(LogType logType, std::string_view message) const noexcept override;
		virtual void LogToConsole(LogType logType, std::string_view format, std::format_args formatArgs) const noexcept override;
		virtual void LogToConsole(LogType logType, std::string_view message, const std::stacktrace& stacktrace) const noexcept override;
		virtual void LogToConsole(LogType logType, std::string_view format, std::format_args formatArgs, const std::stacktrace& stacktrace) const noexcept override;

		virtual void LogToConsole(const std::exception_ptr& exception) const noexcept override;
		virtual void LogToConsole(const std::exception_ptr& exception, std::string_view message) const noexcept override;
		virtual void LogToConsole(const std::exception_ptr& exception, std::string_view format, std::format_args formatArgs) const noexcept override;
		virtual void LogToConsole(const std::exception_ptr& exception, const std::stacktrace& stacktrace) const noexcept override;
		virtual void LogToConsole(const std::exception_ptr& exception, std::string_view message, const std::stacktrace& stacktrace) const noexcept override;
		virtual void LogToConsole(const std::exception_ptr& exception, std::string_view format, std::format_args formatArgs, const std::stacktrace& stacktrace) const noexcept override;

		[[nodiscard("Must be used to remove")]]
		virtual SubLoggerHandle AddSubLogger(const std::function<std::shared_ptr<ISubLogger>(ILoggerContext&)>& factory) override;
		virtual void RemoveSubLogger(SubLoggerHandle handle) override;

		/// @brief Logs the entry.
		/// @param logEntry Log entry to log.
		void Log(const LogEntry& logEntry) const noexcept;

		Application::ILoggerContext* loggerContext; ///< Logger context.

		SubLoggerContainer subLoggerContainer; ///< Sub-logger container.

		mutable std::string logStringTemp; ///< Temporal log string.
		mutable std::string consoleStringTemp; ///< Temporal log string that is used in @p LogToString().

		SubLoggerHandle nextSubLoggerHandle; ///< Next sub-logger handle.
	};
}

namespace PonyEngine::Log
{
	Logger::Logger(Application::ILoggerContext& loggerContext) noexcept :
		loggerContext{&loggerContext},
		nextSubLoggerHandle{.id = 1u}
	{
	}

	Logger::~Logger() noexcept
	{
		if constexpr (IsInMask(LogType::Error, PONY_LOG_MASK))
		{
			if (subLoggerContainer.Size() > 0uz) [[unlikely]]
			{
				PONY_CONSOLE(*this, LogType::Error, "Sub-loggers weren't removed:");
				for (std::size_t i = 0uz; i < subLoggerContainer.Size(); ++i)
				{
					PONY_CONSOLE(*this, LogType::Error, "Sub-logger: '{}'.", typeid(subLoggerContainer.SubLogger(i)).name());
				}
			}
		}
	}

	void Logger::Log(const LogType logType, const std::string_view message) const noexcept
	{
		logStringTemp.clear();
		LogEntry logEntry;
		FillData(logEntry, logStringTemp, logType, message, *loggerContext);
		Log(logEntry);
	}

	void Logger::Log(const LogType logType, const std::string_view format, const std::format_args formatArgs) const noexcept
	{
		logStringTemp.clear();
		LogEntry logEntry;
		FillData(logEntry, logStringTemp, logType, format, formatArgs, *loggerContext);
		Log(logEntry);
	}

	void Logger::Log(const LogType logType, const std::string_view message, const std::stacktrace& stacktrace) const noexcept
	{
		logStringTemp.clear();
		LogEntry logEntry;
		FillData(logEntry, logStringTemp, logType, message, stacktrace, *loggerContext);
		Log(logEntry);
	}

	void Logger::Log(const LogType logType, const std::string_view format, const std::format_args formatArgs, const std::stacktrace& stacktrace) const noexcept
	{
		logStringTemp.clear();
		LogEntry logEntry;
		FillData(logEntry, logStringTemp, logType, format, formatArgs, stacktrace, *loggerContext);
		Log(logEntry);
	}

	void Logger::Log(const std::exception_ptr& exception) const noexcept
	{
		logStringTemp.clear();
		LogEntry logEntry;
		FillData(logEntry, logStringTemp, exception, *loggerContext);
		Log(logEntry);
	}

	void Logger::Log(const std::exception_ptr& exception, const std::string_view message) const noexcept
	{
		logStringTemp.clear();
		LogEntry logEntry;
		FillData(logEntry, logStringTemp, exception, message, *loggerContext);
		Log(logEntry);
	}

	void Logger::Log(const std::exception_ptr& exception, const std::string_view format, const std::format_args formatArgs) const noexcept
	{
		logStringTemp.clear();
		LogEntry logEntry;
		FillData(logEntry, logStringTemp, exception, format, formatArgs, *loggerContext);
		Log(logEntry);
	}

	void Logger::Log(const std::exception_ptr& exception, const std::stacktrace& stacktrace) const noexcept
	{
		logStringTemp.clear();
		LogEntry logEntry;
		FillData(logEntry, logStringTemp, exception, stacktrace, *loggerContext);
		Log(logEntry);
	}

	void Logger::Log(const std::exception_ptr& exception, const std::string_view message, const std::stacktrace& stacktrace) const noexcept
	{
		logStringTemp.clear();
		LogEntry logEntry;
		FillData(logEntry, logStringTemp, exception, message, stacktrace, *loggerContext);
		Log(logEntry);
	}

	void Logger::Log(const std::exception_ptr& exception, const std::string_view format, const std::format_args formatArgs, const std::stacktrace& stacktrace) const noexcept
	{
		logStringTemp.clear();
		LogEntry logEntry;
		FillData(logEntry, logStringTemp, exception, format, formatArgs, stacktrace, *loggerContext);
		Log(logEntry);
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
		consoleStringTemp.clear();
		const std::string_view log = FillData(consoleStringTemp, logType, message, *loggerContext);
		loggerContext->LogToConsole(logType, log);
	}

	void Logger::LogToConsole(const LogType logType, const std::string_view format, const std::format_args formatArgs) const noexcept
	{
		consoleStringTemp.clear();
		const std::string_view log = FillData(consoleStringTemp, logType, format, formatArgs, *loggerContext);
		loggerContext->LogToConsole(logType, log);
	}

	void Logger::LogToConsole(const LogType logType, const std::string_view message, const std::stacktrace& stacktrace) const noexcept
	{
		consoleStringTemp.clear();
		const std::string_view log = FillData(consoleStringTemp, logType, message, stacktrace, *loggerContext);
		loggerContext->LogToConsole(logType, log);
	}

	void Logger::LogToConsole(const LogType logType, const std::string_view format, const std::format_args formatArgs, const std::stacktrace& stacktrace) const noexcept
	{
		consoleStringTemp.clear();
		const std::string_view log = FillData(consoleStringTemp, logType, format, formatArgs, stacktrace, *loggerContext);
		loggerContext->LogToConsole(logType, log);
	}

	void Logger::LogToConsole(const std::exception_ptr& exception) const noexcept
	{
		consoleStringTemp.clear();
		const std::string_view log = FillData(consoleStringTemp, exception, *loggerContext);
		loggerContext->LogToConsole(LogType::Exception, log);
	}

	void Logger::LogToConsole(const std::exception_ptr& exception, const std::string_view message) const noexcept
	{
		consoleStringTemp.clear();
		const std::string_view log = FillData(consoleStringTemp, exception, message, *loggerContext);
		loggerContext->LogToConsole(LogType::Exception, log);
	}

	void Logger::LogToConsole(const std::exception_ptr& exception, const std::string_view format, const std::format_args formatArgs) const noexcept
	{
		consoleStringTemp.clear();
		const std::string_view log = FillData(consoleStringTemp, exception, format, formatArgs, *loggerContext);
		loggerContext->LogToConsole(LogType::Exception, log);
	}

	void Logger::LogToConsole(const std::exception_ptr& exception, const std::stacktrace& stacktrace) const noexcept
	{
		consoleStringTemp.clear();
		const std::string_view log = FillData(consoleStringTemp, exception, stacktrace, *loggerContext);
		loggerContext->LogToConsole(LogType::Exception, log);
	}

	void Logger::LogToConsole(const std::exception_ptr& exception, const std::string_view message, const std::stacktrace& stacktrace) const noexcept
	{
		consoleStringTemp.clear();
		const std::string_view log = FillData(consoleStringTemp, exception, message, stacktrace, *loggerContext);
		loggerContext->LogToConsole(LogType::Exception, log);
	}

	void Logger::LogToConsole(const std::exception_ptr& exception, const std::string_view format, const std::format_args formatArgs, const std::stacktrace& stacktrace) const noexcept
	{
		consoleStringTemp.clear();
		const std::string_view log = FillData(consoleStringTemp, exception, format, formatArgs, stacktrace, *loggerContext);
		loggerContext->LogToConsole(LogType::Exception, log);
	}

	SubLoggerHandle Logger::AddSubLogger(const std::function<std::shared_ptr<ISubLogger>(ILoggerContext&)>& factory)
	{
		if (!nextSubLoggerHandle.IsValid()) [[unlikely]]
		{
			throw std::overflow_error("No more sub-logger handles available");
		}
		if (loggerContext->Application().FlowState() != Application::FlowState::StartingUp) [[unlikely]]
		{
			throw std::logic_error("Sub-logger can be added only on start-up");
		}

		const std::shared_ptr<ISubLogger> subLogger = factory(*this);
		if (!subLogger) [[unlikely]]
		{
			throw std::invalid_argument("Sub-logger is nullptr");
		}
		if (subLoggerContainer.IndexOf(*subLogger) < subLoggerContainer.Size()) [[unlikely]]
		{
			throw std::invalid_argument("Sub-logger has already been added");
		}

		const SubLoggerHandle currentHandle = nextSubLoggerHandle;
		subLoggerContainer.Add(currentHandle, subLogger);
		++nextSubLoggerHandle.id;

		PONY_LOG(*this, LogType::Info, "'{}' sub-logger added. Handle: '0x{:X}'.", typeid(*subLogger).name(), currentHandle.id);

		return currentHandle;
	}

	void Logger::RemoveSubLogger(const SubLoggerHandle handle)
	{
		if (loggerContext->Application().FlowState() != Application::FlowState::StartingUp && loggerContext->Application().FlowState() != Application::FlowState::ShuttingDown) [[unlikely]]
		{
			throw std::logic_error("Sub-logger can be removed only on start-up or shut-down");
		}

		if (const std::size_t index = subLoggerContainer.IndexOf(handle); index < subLoggerContainer.Size()) [[likely]]
		{
			const char* const subLoggerName = typeid(subLoggerContainer.SubLogger(index)).name();
			subLoggerContainer.Remove(index);
			PONY_LOG(*this, LogType::Info, "'{}' sub-logger removed. Handle: '0x{:X}'.", subLoggerName, handle.id);
		}
		else [[unlikely]]
		{
			throw std::invalid_argument("Sub-logger not found");
		}
	}

	void Logger::Log(const LogEntry& logEntry) const noexcept
	{
		loggerContext->LogToConsole(logEntry.logType, logEntry.formattedMessage);

		for (std::size_t i = 0uz; i < subLoggerContainer.Size(); ++i)
		{
			subLoggerContainer.SubLogger(i).Log(logEntry);
		}
	}
}
