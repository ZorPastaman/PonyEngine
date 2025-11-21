/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Log.Ext:LogHelper;

import std;

import PonyEngine.Log;

import :ILoggerContext;

export namespace PonyEngine::Log
{
	// Functions here are used by PonyEngine/Log/Console.h

	/// @brief Logs to a console.
	/// @param logger Logger.
	/// @param logType Log type.
	/// @param message Log message.
	void LogToConsole(const ILoggerContext& logger, LogType logType, std::string_view message) noexcept;
	/// @brief Logs to a console.
	/// @tparam Args Format argument types.
	/// @param logger Logger.
	/// @param logType Log type.
	/// @param format Log message format.
	/// @param args Log message format arguments.
	template<typename... Args>
	void LogToConsole(const ILoggerContext& logger, LogType logType, std::format_string<Args...> format, Args&&... args) noexcept;
	/// @brief Logs to a console.
	/// @param logger Logger.
	/// @param logType Log type.
	/// @param stacktrace Stacktrace.
	/// @param message Log message.
	void LogToConsole(const ILoggerContext& logger, LogType logType, const std::stacktrace& stacktrace, std::string_view message) noexcept;
	/// @brief Logs to a console.
	/// @tparam Args Format argument types.
	/// @param logger Logger.
	/// @param logType Log type.
	/// @param stacktrace 
	/// @param format 
	/// @param args 
	template<typename... Args>
	void LogToConsole(const ILoggerContext& logger, LogType logType, const std::stacktrace& stacktrace, std::format_string<Args...> format, Args&&... args) noexcept;

	/// @brief Logs to a console.
	/// @param logger Logger.
	/// @param exception Exception.
	void LogToConsole(const ILoggerContext& logger, const std::exception_ptr& exception) noexcept;
	/// @brief Logs to a console.
	/// @param logger Logger.
	/// @param exception Exception.
	/// @param message Log message.
	void LogToConsole(const ILoggerContext& logger, const std::exception_ptr& exception, std::string_view message) noexcept;
	/// @brief Logs to a console.
	/// @tparam Args Format argument types.
	/// @param logger Logger.
	/// @param exception Exception.
	/// @param format Log message format.
	/// @param args Log message format arguments.
	template<typename... Args>
	void LogToConsole(const ILoggerContext& logger, const std::exception_ptr& exception, std::format_string<Args...> format, Args&&... args) noexcept;
	/// @brief Logs to a console.
	/// @param logger Logger.
	/// @param exception Exception.
	/// @param stacktrace Stacktrace.
	void LogToConsole(const ILoggerContext& logger, const std::exception_ptr& exception, const std::stacktrace& stacktrace) noexcept;
	/// @brief Logs to a console.
	/// @param logger Logger.
	/// @param exception Exception.
	/// @param stacktrace Stacktrace.
	/// @param message Log message.
	void LogToConsole(const ILoggerContext& logger, const std::exception_ptr& exception, const std::stacktrace& stacktrace, std::string_view message) noexcept;
	/// @brief Logs to a console.
	/// @tparam Args Format argument types.
	/// @param logger Logger.
	/// @param exception Exception.
	/// @param stacktrace Stacktrace.
	/// @param format Log message format.
	/// @param args Log message format arguments.
	template<typename... Args>
	void LogToConsole(const ILoggerContext& logger, const std::exception_ptr& exception, const std::stacktrace& stacktrace, std::format_string<Args...> format, Args&&... args) noexcept;
}

namespace PonyEngine::Log
{
	void LogToConsole(const ILoggerContext& logger, const LogType logType, const std::string_view message) noexcept
	{
		logger.LogToConsole(logType, message);
	}

	template<typename... Args>
	void LogToConsole(const ILoggerContext& logger, const LogType logType, const std::format_string<Args...> format, Args&&... args) noexcept
	{
		logger.LogToConsole(logType, format.get(), std::make_format_args(args...));
	}

	void LogToConsole(const ILoggerContext& logger, const LogType logType, const std::stacktrace& stacktrace, const std::string_view message) noexcept
	{
		logger.LogToConsole(logType, message, stacktrace);
	}

	void LogToConsole(const ILoggerContext& logger, const std::exception_ptr& exception) noexcept
	{
		logger.LogToConsole(exception);
	}

	template<typename... Args>
	void LogToConsole(const ILoggerContext& logger, const LogType logType, const std::stacktrace& stacktrace, const std::format_string<Args...> format, Args&&... args) noexcept
	{
		logger.LogToConsole(logType, format.get(), std::make_format_args(args...), stacktrace);
	}

	void LogToConsole(const ILoggerContext& logger, const std::exception_ptr& exception, const std::string_view message) noexcept
	{
		logger.LogToConsole(exception, message);
	}

	template<typename... Args>
	void LogToConsole(const ILoggerContext& logger, const std::exception_ptr& exception, const std::format_string<Args...> format, Args&&... args) noexcept
	{
		logger.LogToConsole(exception, format.get(), std::make_format_args(args...));
	}

	void LogToConsole(const ILoggerContext& logger, const std::exception_ptr& exception, const std::stacktrace& stacktrace) noexcept
	{
		logger.LogToConsole(exception, stacktrace);
	}

	void LogToConsole(const ILoggerContext& logger, const std::exception_ptr& exception, const std::stacktrace& stacktrace, const std::string_view message) noexcept
	{
		logger.LogToConsole(exception, message, stacktrace);
	}

	template<typename... Args>
	void LogToConsole(const ILoggerContext& logger, const std::exception_ptr& exception, const std::stacktrace& stacktrace, const std::format_string<Args...> format, Args&&... args) noexcept
	{
		logger.LogToConsole(exception, format.get(), std::make_format_args(args...), stacktrace);
	}
}
