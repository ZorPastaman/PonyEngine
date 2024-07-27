/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Log:LogHelper;

import <cstddef>;
import <exception>;

import :ILogger;
import :LogInput;
import :LogType;

export namespace PonyEngine::Log
{
	/// @brief Logs to the @p logger using other arguments as input.
	/// @note Usually you don't need to use this function directly. Use defines from @p PonyEngine/Log/Log.h.
	/// @param logger Logger.
	/// @param logType Log type.
	/// @param message Log message.
	void LogToLogger(ILogger& logger, LogType logType, const char* message) noexcept;
	/// @brief Logs to the @p logger using other arguments as input.
	/// @note Usually you don't need to use this function directly. Use defines from @p PonyEngine/Log/Log.h.
	/// @param logger Logger.
	/// @param logType Log type.
	/// @param message Log message.
	/// @param frameCount Frame count.
	void LogToLogger(ILogger& logger, LogType logType, const char* message, std::size_t frameCount) noexcept;

	/// @brief Logs the @p exception to the @p logger using other arguments as input.
	/// @note Usually you don't need to use this function directly. Use defines from @p PonyEngine/Log/Log.h.
	/// @param logger Logger.
	/// @param exception Exception to log.
	/// @param message Log message.
	void LogExceptionToLogger(ILogger& logger, const std::exception& exception, const char* message) noexcept;
	/// @brief Logs the @p exception to the @p logger using other arguments as input.
	/// @note Usually you don't need to use this function directly. Use defines from @p PonyEngine/Log/Log.h.
	/// @param logger Logger.
	/// @param exception Exception to log.
	/// @param message Log message.
	/// @param frameCount Frame count.
	void LogExceptionToLogger(ILogger& logger, const std::exception& exception, const char* message, std::size_t frameCount) noexcept;
}

namespace PonyEngine::Log
{
	void LogToLogger(ILogger& logger, const LogType logType, const char* message) noexcept
	{
		const auto logInput = LogInput{.message = message, .frameCount = 0};
		logger.Log(logType, logInput);
	}

	void LogToLogger(ILogger& logger, const LogType logType, const char* message, const std::size_t frameCount) noexcept
	{
		const auto logInput = LogInput{.message = message, .frameCount = frameCount};
		logger.Log(logType, logInput);
	}

	void LogExceptionToLogger(ILogger& logger, const std::exception& exception, const char* message) noexcept
	{
		const auto logInput = LogInput{.message = message, .frameCount = 0};
		logger.LogException(exception, logInput);
	}

	void LogExceptionToLogger(ILogger& logger, const std::exception& exception, const char* message, const std::size_t frameCount) noexcept
	{
		const auto logInput = LogInput{.message = message, .frameCount = frameCount};
		logger.LogException(exception, logInput);
	}
}
