/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Log:LogHelper;

import std;

import :ILogger;
import :LogType;

export namespace PonyEngine::Log
{
	/// @brief Logs to the logger.
	/// @param logger Logger.
	/// @param logType Log type.
	/// @param message Log message.
	/// @note The function is thread-safe.
	void LogToLogger(const ILogger& logger, LogType logType, std::string_view message) noexcept;
	/// @brief Logs to the logger.
	/// @tparam Args Format argument types.
	/// @param logger Logger.
	/// @param logType Log type.
	/// @param format Log message format.
	/// @param args Log message format arguments.
	/// @note The function is thread-safe.
	template<typename... Args>
	void LogToLogger(const ILogger& logger, LogType logType, std::format_string<Args...> format, Args&&... args) noexcept;
	/// @brief Logs to the logger.
	/// @param logger Logger.
	/// @param logType Log type.
	/// @param stacktrace Stacktrace.
	/// @param message Log message.
	/// @note The function is thread-safe.
	void LogToLogger(const ILogger& logger, LogType logType, const std::stacktrace& stacktrace, std::string_view message) noexcept;
	/// @brief Logs to the logger.
	/// @tparam Args Format argument types.
	/// @param logger Logger.
	/// @param logType Log type.
	/// @param stacktrace Stacktrace.
	/// @param format Log message format.
	/// @param args Log message format arguments.
	/// @note The function is thread-safe.
	template<typename... Args>
	void LogToLogger(const ILogger& logger, LogType logType, const std::stacktrace& stacktrace, std::format_string<Args...> format, Args&&... args) noexcept;

	/// @brief Logs to the logger.
	/// @param logger Logger.
	/// @param logType Log type.
	/// @param exception Exception.
	/// @note The function is thread-safe.
	void LogToLogger(const ILogger& logger, LogType logType, const std::exception_ptr& exception) noexcept;
	/// @brief Logs to the logger.
	/// @param logger Logger.
	/// @param logType Log type.
	/// @param exception Exception.
	/// @param message Log message.
	/// @note The function is thread-safe.
	void LogToLogger(const ILogger& logger, LogType logType, const std::exception_ptr& exception, std::string_view message) noexcept;
	/// @brief Logs to the logger.
	/// @tparam Args Format argument types.
	/// @param logger Logger.
	/// @param logType Log type.
	/// @param exception Exception.
	/// @param format Log message format.
	/// @param args Log message format arguments.
	/// @note The function is thread-safe.
	template<typename... Args>
	void LogToLogger(const ILogger& logger, LogType logType, const std::exception_ptr& exception, std::format_string<Args...> format, Args&&... args) noexcept;
	/// @brief Logs to the logger.
	/// @param logger Logger.
	/// @param logType Log type.
	/// @param exception Exception.
	/// @param stacktrace Stacktrace.
	/// @note The function is thread-safe.
	void LogToLogger(const ILogger& logger, LogType logType, const std::stacktrace& stacktrace, const std::exception_ptr& exception) noexcept;
	/// @brief Logs to the logger.
	/// @param logger Logger.
	/// @param logType Log type.
	/// @param exception Exception.
	/// @param stacktrace Stacktrace.
	/// @param message Log message.
	/// @note The function is thread-safe.
	void LogToLogger(const ILogger& logger, LogType logType, const std::stacktrace& stacktrace, const std::exception_ptr& exception, std::string_view message) noexcept;
	/// @brief Logs to the logger.
	/// @tparam Args Format argument types.
	/// @param logger Logger.
	/// @param logType Log type.
	/// @param exception Exception.
	/// @param stacktrace Stacktrace.
	/// @param format Log message format.
	/// @param args Log message format arguments.
	/// @note The function is thread-safe.
	template<typename... Args>
	void LogToLogger(const ILogger& logger, LogType logType, const std::stacktrace& stacktrace, const std::exception_ptr& exception, std::format_string<Args...> format, Args&&... args) noexcept;
}

namespace PonyEngine::Log
{
	void LogToLogger(const ILogger& logger, const LogType logType, const std::string_view message) noexcept
	{
		logger.Log(logType, message);
	}

	template<typename... Args>
	void LogToLogger(const ILogger& logger, const LogType logType, const std::format_string<Args...> format, Args&&... args) noexcept
	{
		logger.Log(logType, format.get(), std::make_format_args(args...));
	}

	void LogToLogger(const ILogger& logger, const LogType logType, const std::stacktrace& stacktrace, const std::string_view message) noexcept
	{
		logger.Log(logType, message, stacktrace);
	}

	template<typename... Args>
	void LogToLogger(const ILogger& logger, const LogType logType, const std::stacktrace& stacktrace, const std::format_string<Args...> format, Args&&... args) noexcept
	{
		logger.Log(logType, format.get(), std::make_format_args(args...), stacktrace);
	}

	void LogToLogger(const ILogger& logger, const LogType logType, const std::exception_ptr& exception) noexcept
	{
		logger.Log(logType, exception);
	}

	void LogToLogger(const ILogger& logger, const LogType logType, const std::exception_ptr& exception, const std::string_view message) noexcept
	{
		logger.Log(logType, exception, message);
	}

	template<typename... Args>
	void LogToLogger(const ILogger& logger, const LogType logType, const std::exception_ptr& exception, const std::format_string<Args...> format, Args&&... args) noexcept
	{
		logger.Log(logType, exception, format.get(), std::make_format_args(args...));
	}

	void LogToLogger(const ILogger& logger, const LogType logType, const std::stacktrace& stacktrace, const std::exception_ptr& exception) noexcept
	{
		logger.Log(logType, exception, stacktrace);
	}

	void LogToLogger(const ILogger& logger, const LogType logType, const std::stacktrace& stacktrace, const std::exception_ptr& exception, const std::string_view message) noexcept
	{
		logger.Log(logType, exception, message, stacktrace);
	}

	template<typename... Args>
	void LogToLogger(const ILogger& logger, const LogType logType, const std::stacktrace& stacktrace, const std::exception_ptr& exception, const std::format_string<Args...> format, Args&&... args) noexcept
	{
		logger.Log(logType, exception, format.get(), std::make_format_args(args...), stacktrace);
	}
}
