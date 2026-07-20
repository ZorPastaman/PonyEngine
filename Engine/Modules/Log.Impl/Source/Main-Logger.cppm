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

export module PonyEngine.Log.Impl:Logger;

import std;

import PonyEngine.Application;
import PonyEngine.Log.Ext;

import :LogFiller;
import :SubLoggerContainer;

export namespace PonyEngine::Log
{
	/// @brief Logger.
	class Logger final : public ILogService, public ILoggerModuleContext, private ILoggerContext
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

		virtual void Log(LogType logType, const std::exception_ptr& exception) const noexcept override;
		virtual void Log(LogType logType, const std::exception_ptr& exception, std::string_view message) const noexcept override;
		virtual void Log(LogType logType, const std::exception_ptr& exception, std::string_view format, std::format_args formatArgs) const noexcept override;
		virtual void Log(LogType logType, const std::exception_ptr& exception, const std::stacktrace& stacktrace) const noexcept override;
		virtual void Log(LogType logType, const std::exception_ptr& exception, std::string_view message, const std::stacktrace& stacktrace) const noexcept override;
		virtual void Log(LogType logType, const std::exception_ptr& exception, std::string_view format, std::format_args formatArgs, const std::stacktrace& stacktrace) const noexcept override;

		[[nodiscard("Must be used to remove")]]
		virtual SubLoggerHandle AddSubLogger(const std::function<std::shared_ptr<ISubLogger>(ILoggerContext&)>& factory) override;
		virtual void RemoveSubLogger(SubLoggerHandle handle) override;

		Logger& operator =(const Logger&) = delete;
		Logger& operator =(Logger&&) = delete;

	private:
		[[nodiscard("Pure function")]]
		virtual Application::IApplication& Application() noexcept override;
		[[nodiscard("Pure function")]]
		virtual const Application::IApplication& Application() const noexcept override;

		/// @brief Logs the entry.
		/// @param formattedMessage Formatted message.
		/// @param logEntry Log entry to log.
		void Log(std::string_view formattedMessage, const LogEntry& logEntry) const noexcept;

		Application::ILoggerContext* loggerContext; ///< Logger context.

		SubLoggerContainer subLoggerContainer; ///< Sub-logger container.

		inline static thread_local std::string logString; ///< Log string.

		SubLoggerHandle nextSubLoggerHandle; ///< Next sub-logger handle.

		mutable std::mutex logMutex; ///< Log mutex.
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
#if PONY_LOG_ERROR
		if (subLoggerContainer.Size() > 0uz) [[unlikely]]
		{
			loggerContext->LogToConsole(LogType::Error, "Sub-loggers weren't removed:");
			for (std::size_t i = 0uz; i < subLoggerContainer.Size(); ++i)
			{
				loggerContext->LogToConsole(LogType::Error, typeid(subLoggerContainer.SubLogger(i)).name());
			}
		}
#endif
	}

	void Logger::Log(const LogType logType, const std::string_view message) const noexcept
	{
		logString.clear();
		LogEntry logEntry;
		FillData(logEntry, logString, logType, message);
		Log(logString, logEntry);
	}

	void Logger::Log(const LogType logType, const std::string_view format, const std::format_args formatArgs) const noexcept
	{
		logString.clear();
		LogEntry logEntry;
		FillData(logEntry, logString, logType, format, formatArgs);
		Log(logString, logEntry);
	}

	void Logger::Log(const LogType logType, const std::string_view message, const std::stacktrace& stacktrace) const noexcept
	{
		logString.clear();
		LogEntry logEntry;
		FillData(logEntry, logString, logType, message, stacktrace);
		Log(logString, logEntry);
	}

	void Logger::Log(const LogType logType, const std::string_view format, const std::format_args formatArgs, const std::stacktrace& stacktrace) const noexcept
	{
		logString.clear();
		LogEntry logEntry;
		FillData(logEntry, logString, logType, format, formatArgs, stacktrace);
		Log(logString, logEntry);
	}

	void Logger::Log(const LogType logType, const std::exception_ptr& exception) const noexcept
	{
		logString.clear();
		LogEntry logEntry;
		FillData(logEntry, logString, logType, exception);
		Log(logString, logEntry);
	}

	void Logger::Log(const LogType logType, const std::exception_ptr& exception, const std::string_view message) const noexcept
	{
		logString.clear();
		LogEntry logEntry;
		FillData(logEntry, logString, logType, exception, message);
		Log(logString, logEntry);
	}

	void Logger::Log(const LogType logType, const std::exception_ptr& exception, const std::string_view format, const std::format_args formatArgs) const noexcept
	{
		logString.clear();
		LogEntry logEntry;
		FillData(logEntry, logString, logType, exception, format, formatArgs);
		Log(logString, logEntry);
	}

	void Logger::Log(const LogType logType, const std::exception_ptr& exception, const std::stacktrace& stacktrace) const noexcept
	{
		logString.clear();
		LogEntry logEntry;
		FillData(logEntry, logString, logType, exception, stacktrace);
		Log(logString, logEntry);
	}

	void Logger::Log(const LogType logType, const std::exception_ptr& exception, const std::string_view message, const std::stacktrace& stacktrace) const noexcept
	{
		logString.clear();
		LogEntry logEntry;
		FillData(logEntry, logString, logType, exception, message, stacktrace);
		Log(logString, logEntry);
	}

	void Logger::Log(const LogType logType, const std::exception_ptr& exception, const std::string_view format, const std::format_args formatArgs, 
		const std::stacktrace& stacktrace) const noexcept
	{
		logString.clear();
		LogEntry logEntry;
		FillData(logEntry, logString, logType, exception, format, formatArgs, stacktrace);
		Log(logString, logEntry);
	}

	SubLoggerHandle Logger::AddSubLogger(const std::function<std::shared_ptr<ISubLogger>(ILoggerContext&)>& factory)
	{
#ifndef NDEBUG
		if (std::this_thread::get_id() != loggerContext->Application().MainThreadID()) [[unlikely]]
		{
			throw std::logic_error("Must be called on main thread");
		}

		if (!nextSubLoggerHandle.IsValid()) [[unlikely]]
		{
			throw std::overflow_error("No more sub-logger handles available");
		}
		if (loggerContext->Application().FlowState() != Application::FlowState::StartingUp) [[unlikely]]
		{
			throw std::logic_error("Sub-logger can be added only on start-up");
		}
#endif

		const std::shared_ptr<ISubLogger> subLogger = factory(*this);
#ifndef NDEBUG
		if (!subLogger) [[unlikely]]
		{
			throw std::invalid_argument("Sub-logger is nullptr");
		}
		if (subLoggerContainer.IndexOf(*subLogger) < subLoggerContainer.Size()) [[unlikely]]
		{
			throw std::invalid_argument("Sub-logger has already been added");
		}
#endif

		const SubLoggerHandle currentHandle = nextSubLoggerHandle;
		subLoggerContainer.Add(currentHandle, subLogger);
		++nextSubLoggerHandle.id;

		PONY_LOG(*this, LogType::Info, "'{}' sub-logger added. Handle: '0x{:X}'.", typeid(*subLogger).name(), currentHandle.id);

		return currentHandle;
	}

	void Logger::RemoveSubLogger(const SubLoggerHandle handle)
	{
#ifndef NDEBUG
		if (std::this_thread::get_id() != loggerContext->Application().MainThreadID()) [[unlikely]]
		{
			throw std::logic_error("Must be called on main thread");
		}

		if (loggerContext->Application().FlowState() != Application::FlowState::StartingUp && loggerContext->Application().FlowState() != Application::FlowState::ShuttingDown) [[unlikely]]
		{
			throw std::logic_error("Sub-logger can be removed only on start-up or shut-down");
		}
#endif

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

	Application::IApplication& Logger::Application() noexcept
	{
		return loggerContext->Application();
	}

	const Application::IApplication& Logger::Application() const noexcept
	{
		return loggerContext->Application();
	}

	void Logger::Log(const std::string_view formattedMessage, const LogEntry& logEntry) const noexcept
	{
		const auto lock = std::lock_guard(logMutex);

		loggerContext->LogToConsole(logEntry.logType, formattedMessage);

		for (std::size_t i = 0uz; i < subLoggerContainer.Size(); ++i)
		{
			subLoggerContainer.SubLogger(i).Log(formattedMessage, logEntry);
		}
	}
}
