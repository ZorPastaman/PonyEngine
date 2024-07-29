/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#if PONY_SYSTEM_CONSOLE_LOG
#if _WIN32
#include "PonyEngine/Platform/Windows/Framework.h"
#endif
#endif

export module PonyEngine.Log:LogConsoleHelper;

import <exception>;
import <iostream>;
import <ostream>;
import <string>;

import :LogFormat;
import :LogType;

export namespace PonyEngine::Log
{
	/// @brief Logs to a standard console and a system console.
	/// @param logType Log type.
	/// @param message Log message.
	void LogToConsole(LogType logType, const char* message) noexcept;
	/// @brief Logs the @p exception to a standard console and a system console.
	/// @param exception Exception to log.
	void LogExceptionToConsole(const std::exception& exception) noexcept;
	/// @brief Logs the @p exception to a standard console and a system console.
	/// @param exception Exception to log.
	/// @param message Log message.
	void LogExceptionToConsole(const std::exception& exception, const char* message) noexcept;

	/// @brief Chooses a console output stream by the @p logType.
	/// @param logType Log type.
	/// @return Chosen stream.
	[[nodiscard("Pure function")]]
	std::ostream& ChooseConsoleStream(LogType logType) noexcept;
}

namespace PonyEngine::Log
{
	/// @brief Logs to a standard console and a system console.
	/// @param logType Log type.
	/// @param log Formatted log message.
	void LogFormattedToConsole(LogType logType, const char* log) noexcept;

	void LogToConsole(const LogType logType, const char* const message) noexcept
	{
		try
		{
			const std::string log = LogFormat(logType, message ? message : "");
			LogFormattedToConsole(logType, log.c_str());
		}
		catch (...)
		{
			// Something totally wrong happened.
		}
	}

	void LogExceptionToConsole(const std::exception& exception) noexcept
	{
		try
		{
			const std::string log = LogFormat(LogType::Exception, exception.what());
			LogFormattedToConsole(LogType::Exception, log.c_str());
		}
		catch (...)
		{
			// Something totally wrong happened.
		}
	}

	void LogExceptionToConsole(const std::exception& exception, const char* const message) noexcept
	{
		try
		{
			const std::string log = LogFormat(LogType::Exception, exception.what(), message ? message : "");
			LogFormattedToConsole(LogType::Exception, log.c_str());
		}
		catch (...)
		{
			// Something totally wrong happened.
		}
	}

	std::ostream& ChooseConsoleStream(const LogType logType) noexcept
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
			return std::cerr; // Fallback
		}
	}

	void LogFormattedToConsole(const LogType logType, const char* const log) noexcept
	{
#if PONY_CONSOLE_LOG
		try
		{
			ChooseConsoleStream(logType) << log;
		}
		catch (...)
		{
			// Something totally wrong happened.
		}
#endif
#if PONY_SYSTEM_CONSOLE_LOG
#if _WIN32
		try
		{
			OutputDebugStringA(log);
		}
		catch (...)
		{
			// Something totally wrong happened.
		}
#endif
#endif
	}
}
