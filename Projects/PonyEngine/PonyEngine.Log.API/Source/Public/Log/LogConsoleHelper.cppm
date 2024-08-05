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

#include "PonyEngine/Log/Log.h"

export module PonyEngine.Log:LogConsoleHelper;

import <exception>;
import <format>;
import <iostream>;
import <ostream>;
import <string>;

import PonyEngine.StringUtility;

import :LogFormat;
import :LogType;

export namespace PonyEngine::Log
{
	/// @brief Passes exceptions to @p PONY_CONSOLE_E_S.
	struct ConsoleExceptionHandler final
	{
		/// @brief Passes exceptions to @p PONY_CONSOLE_E_S.
		/// @param e Exception to pass.
		void operator ()(const std::exception& e) const noexcept;
	};

	/// @brief Logs to a standard console and a system console.
	/// @param logType Log type.
	/// @param message Log message.
	void LogToConsole(LogType logType, const char* message) noexcept;
	/// @brief Logs to a standard console and a system console.
	/// @tparam Args Format argument types.
	/// @param logType Log type.
	/// @param format Format.
	/// @param args Format arguments.
	template<typename... Args>
	void LogToConsole(LogType logType, std::format_string<Args...> format, Args&&... args) noexcept;

	/// @brief Logs the @p exception to a standard console and a system console.
	/// @param exception Exception to log.
	void LogExceptionToConsole(const std::exception& exception) noexcept;
	/// @brief Logs the @p exception to a standard console and a system console.
	/// @param exception Exception to log.
	/// @param message Log message.
	void LogExceptionToConsole(const std::exception& exception, const char* message) noexcept;
	/// @brief Logs the @p exception to a standard console and a system console.
	/// @tparam Args Format argument types.
	/// @param exception Exception to log.
	/// @param format Format.
	/// @param args Format arguments.
	template<typename... Args>
	void LogExceptionToConsole(const std::exception& exception, std::format_string<Args...> format, Args&&... args) noexcept;

	/// @brief Chooses a console output stream by the @p logType.
	/// @param logType Log type.
	/// @return Chosen stream.
	[[nodiscard("Pure function")]]
	std::ostream& ChooseConsoleStream(LogType logType) noexcept;

	/// @brief @p std::format() wrapper that doesn't throw. If @p std::format() throws, the exception is passed to the @p ConsoleExceptionHandler.
	/// @tparam Args Format argument types.
	/// @param format Format.
	/// @param args Format arguments.
	/// @return Format result or empty string if std::format() threw.
	template<typename... Args> [[nodiscard("Pure function")]]
	std::string SafeFormat(std::format_string<Args...> format, Args&&... args) noexcept;
}

namespace PonyEngine::Log
{
	/// @brief Logs to a standard console and a system console.
	/// @param logType Log type.
	/// @param log Formatted log message.
	void LogFormattedToConsole(LogType logType, const char* log) noexcept;

	void ConsoleExceptionHandler::operator ()(const std::exception& e) const noexcept
	{
		PONY_CONSOLE_E_S(e);
	}

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

	template<typename ... Args>
	void LogToConsole(const LogType logType, std::format_string<Args...> format, Args&&... args) noexcept
	{
		return LogToConsole(logType, SafeFormat(format, std::forward<Args>(args)...).c_str());
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

	template<typename ... Args>
	void LogExceptionToConsole(const std::exception& exception, std::format_string<Args...> format, Args&&... args) noexcept
	{
		return LogExceptionToConsole(exception, SafeFormat(format, std::forward<Args>(args)...).c_str());
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

	template<typename... Args>
	std::string SafeFormat(std::format_string<Args...> format, Args&&... args) noexcept
	{
		return Utility::SafeFormat<ConsoleExceptionHandler>(format, std::forward<Args>(args)...);
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
