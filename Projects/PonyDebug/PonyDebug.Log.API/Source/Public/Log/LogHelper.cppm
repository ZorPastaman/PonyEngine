/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyDebug.Log:LogHelper;

import <cstddef>;
import <format>;
import <exception>;
import <string>;

import :LogConsoleHelper;
import :ILogger;
import :LogInput;
import :LogType;

export namespace PonyDebug::Log
{
	/// @brief Logs to the @p logger.
	/// @param logger Logger.
	/// @param logType Log type.
	/// @param message Log message.
	void LogToLogger(ILogger& logger, LogType logType, const char* message) noexcept;
	/// @brief Logs to the @p logger.
	/// @tparam Args Format argument types.
	/// @param logger Logger.
	/// @param logType Log type.
	/// @param format Format.
	/// @param args Format arguments.
	template<typename... Args>
	void LogToLogger(ILogger& logger, LogType logType, std::format_string<Args...> format, Args&&... args) noexcept;

	/// @brief Logs the @p exception to the @p logger.
	/// @param logger Logger.
	/// @param exception Exception to log.
	void LogExceptionToLogger(ILogger& logger, const std::exception& exception) noexcept;
	/// @brief Logs the @p exception to the @p logger.
	/// @param logger Logger.
	/// @param exception Exception to log.
	/// @param message Log message.
	void LogExceptionToLogger(ILogger& logger, const std::exception& exception, const char* message) noexcept;
	/// @brief Logs the @p exception to the @p logger.
	/// @tparam Args Format argument types.
	/// @param logger Logger.
	/// @param exception Exception to log.
	/// @param format Format.
	/// @param args Format arguments.
	template<typename... Args>
	void LogExceptionToLogger(ILogger& logger, const std::exception& exception, std::format_string<Args...> format, Args&&... args) noexcept;
}

namespace PonyDebug::Log
{
	void LogToLogger(ILogger& logger, const LogType logType, const char* const message) noexcept
	{
		const auto logInput = LogInput{.message = message};
		logger.Log(logType, logInput);
	}

	template<typename... Args>
	void LogToLogger(ILogger& logger, const LogType logType, std::format_string<Args...> format, Args&&... args) noexcept
	{
		LogToLogger(logger, logType, SafeFormat(format, std::forward<Args>(args)...).c_str());
	}

	void LogExceptionToLogger(ILogger& logger, const std::exception& exception) noexcept
	{
		logger.LogException(exception, LogInput{});
	}

	void LogExceptionToLogger(ILogger& logger, const std::exception& exception, const char* const message) noexcept
	{
		const auto logInput = LogInput{.message = message};
		logger.LogException(exception, logInput);
	}

	template<typename... Args>
	void LogExceptionToLogger(ILogger& logger, const std::exception& exception, std::format_string<Args...> format, Args&&... args) noexcept
	{
		LogExceptionToLogger(logger, exception, SafeFormat(format, std::forward<Args>(args)...).c_str());
	}
}
