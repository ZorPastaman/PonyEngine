/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#define PONY_SYSTEM_CONSOLE_LOG 1 // TODO: remove it.

#if PONY_SYSTEM_CONSOLE_LOG
#if _WIN32
#include "PonyEngine/Platform/Windows/Framework.h"
#endif
#endif

export module PonyEngine.Log:LogHelper;

import <cstddef>;
import <exception>;
import <iostream>;
import <ostream>;

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

	/// @brief Logs to a standard console and a system console.
	/// @param logType Log type. It must be one log type value.
	/// @param message Log message.
	void LogToConsole(LogType logType, const char* message);
	/// @brief Logs the @p exception to a standard console and a system console.
	/// @param exception Exception to log.
	/// @param message Log message.
	void LogExceptionToConsole(const std::exception& exception, const char* message);

	/// @brief Chooses a console output stream by the @p logType.
	/// @param logType Log type. It must be one log type value.
	/// @return Chosen stream.
	std::ostream& ChooseConsoleStream(LogType logType);
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

	void LogToConsole(const LogType logType, const char* message)
	{
		const char* logTypeString = ToStringSimple(logType);

#if PONY_CONSOLE_LOG
		ChooseConsoleStream(logType) << '[' << logTypeString << "] " << message << std::endl;
#endif
#if PONY_SYSTEM_CONSOLE_LOG
#if _WIN32
		OutputDebugStringA("[");
		OutputDebugStringA(logTypeString);
		OutputDebugStringA("] ");
		OutputDebugStringA(message);
		OutputDebugStringA("\n");
#endif
#endif
	}

	void LogExceptionToConsole(const std::exception& exception, const char* message)
	{
		const char* logTypeString = ToStringSimple(LogType::Exception);

#if PONY_CONSOLE_LOG
		ChooseConsoleStream(LogType::Exception) << '[' << logTypeString << "] " << exception.what() << " - " << message << std::endl;
#endif
#if PONY_SYSTEM_CONSOLE_LOG
#if _WIN32
		OutputDebugStringA("[");
		OutputDebugStringA(logTypeString);
		OutputDebugStringA("] ");
		OutputDebugStringA(exception.what());
		OutputDebugStringA(" - ");
		OutputDebugStringA(message);
		OutputDebugStringA("\n");
#endif
#endif
	}

	std::ostream& ChooseConsoleStream(const LogType logType)
	{
		switch (logType)
		{
		case LogType::Verbose:
		case LogType::Debug:
		case LogType::Info:
			return std::cout;
		case LogType::Warning:
			return std::clog;
		case LogType::Error:
		case LogType::Exception:
			return std::cerr;
		default:
			throw std::invalid_argument("logType has an incorrect value.");
		}
	}
}
