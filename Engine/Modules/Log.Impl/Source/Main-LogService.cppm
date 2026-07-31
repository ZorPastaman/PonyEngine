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

export module PonyEngine.Log.Impl:LogService;

import std;

import PonyEngine.Application;
import PonyEngine.Log.Ext;

import :LogFiller;

export namespace PonyEngine::Log
{
	/// @brief Log hub.
	class LogService final : public ILogService, public ILogHub
	{
	public:
		[[nodiscard("Pure constuctor")]]
		LogService() noexcept = default;
		LogService(const LogService&) = delete;
		LogService(LogService&&) = delete;

		~LogService() noexcept;

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

		virtual void AddLogger(ILogger& logger) override;
		virtual void RemoveLogger(ILogger& logger) override;

		LogService& operator =(const LogService&) = delete;
		LogService& operator =(LogService&&) = delete;

	private:
		/// @brief Logs the entry.
		/// @param formattedMessage Formatted message.
		/// @param logEntry Log entry to log.
		void Log(std::string_view formattedMessage, const LogEntry& logEntry) const noexcept;

		inline static thread_local std::string logString; ///< Log string.

		std::vector<ILogger*> loggers; ////< Loggers.
		mutable std::mutex logMutex; ///< Log mutex.
	};
}

namespace PonyEngine::Log
{
	LogService::~LogService() noexcept
	{
		assert(loggers.size() == 0uz && "Some loggers weren't removed.");
	}

	void LogService::Log(const LogType logType, const std::string_view message) const noexcept
	{
		logString.clear();
		LogEntry logEntry;
		FillData(logEntry, logString, logType, message);
		Log(logString, logEntry);
	}

	void LogService::Log(const LogType logType, const std::string_view format, const std::format_args formatArgs) const noexcept
	{
		logString.clear();
		LogEntry logEntry;
		FillData(logEntry, logString, logType, format, formatArgs);
		Log(logString, logEntry);
	}

	void LogService::Log(const LogType logType, const std::string_view message, const std::stacktrace& stacktrace) const noexcept
	{
		logString.clear();
		LogEntry logEntry;
		FillData(logEntry, logString, logType, message, stacktrace);
		Log(logString, logEntry);
	}

	void LogService::Log(const LogType logType, const std::string_view format, const std::format_args formatArgs, const std::stacktrace& stacktrace) const noexcept
	{
		logString.clear();
		LogEntry logEntry;
		FillData(logEntry, logString, logType, format, formatArgs, stacktrace);
		Log(logString, logEntry);
	}

	void LogService::Log(const LogType logType, const std::exception_ptr& exception) const noexcept
	{
		logString.clear();
		LogEntry logEntry;
		FillData(logEntry, logString, logType, exception);
		Log(logString, logEntry);
	}

	void LogService::Log(const LogType logType, const std::exception_ptr& exception, const std::string_view message) const noexcept
	{
		logString.clear();
		LogEntry logEntry;
		FillData(logEntry, logString, logType, exception, message);
		Log(logString, logEntry);
	}

	void LogService::Log(const LogType logType, const std::exception_ptr& exception, const std::string_view format, const std::format_args formatArgs) const noexcept
	{
		logString.clear();
		LogEntry logEntry;
		FillData(logEntry, logString, logType, exception, format, formatArgs);
		Log(logString, logEntry);
	}

	void LogService::Log(const LogType logType, const std::exception_ptr& exception, const std::stacktrace& stacktrace) const noexcept
	{
		logString.clear();
		LogEntry logEntry;
		FillData(logEntry, logString, logType, exception, stacktrace);
		Log(logString, logEntry);
	}

	void LogService::Log(const LogType logType, const std::exception_ptr& exception, const std::string_view message, const std::stacktrace& stacktrace) const noexcept
	{
		logString.clear();
		LogEntry logEntry;
		FillData(logEntry, logString, logType, exception, message, stacktrace);
		Log(logString, logEntry);
	}

	void LogService::Log(const LogType logType, const std::exception_ptr& exception, const std::string_view format, const std::format_args formatArgs, 
		const std::stacktrace& stacktrace) const noexcept
	{
		logString.clear();
		LogEntry logEntry;
		FillData(logEntry, logString, logType, exception, format, formatArgs, stacktrace);
		Log(logString, logEntry);
	}

	void LogService::AddLogger(ILogger& logger)
	{
		const auto lock = std::lock_guard(logMutex);
		assert(std::ranges::find(loggers, &logger) == loggers.cend() && "Logger is already added");
		loggers.push_back(&logger);
	}

	void LogService::RemoveLogger(ILogger& logger)
	{
		const auto lock = std::lock_guard(logMutex);
		const auto position = std::ranges::find(loggers, &logger);
		assert(position != loggers.cend() && "Logger wasn't added");
		loggers.erase(position);
	}

	void LogService::Log(const std::string_view formattedMessage, const LogEntry& logEntry) const noexcept
	{
		const auto lock = std::lock_guard(logMutex);

		for (ILogger* const logger : loggers)
		{
			logger->Log(formattedMessage, logEntry);
		}
	}
}
