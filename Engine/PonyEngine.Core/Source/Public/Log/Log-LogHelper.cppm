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

#ifdef PONY_PLATFORM_CONSOLE_LOG
#ifdef PONY_WINCORE
#include "PonyEngine/Platform/WinCore/Framework.h"
#endif
#endif

export module PonyEngine.Log:LogHelper;

import std;

import PonyEngine.Utility;

import :ILogger;
import :LogFormat;
import :LogInput;
import :LogType;

export namespace PonyEngine::Log
{
	/// @brief Logs to the @p logger.
	/// @param logger Logger.
	/// @param logType Log type.
	/// @param message Log message.
	void LogToLogger(const ILogger& logger, LogType logType, std::string_view message) noexcept;
	/// @brief Logs to the @p logger.
	/// @tparam Args Format argument types.
	/// @param logger Logger.
	/// @param logType Log type.
	/// @param format Format.
	/// @param args Format arguments.
	template<typename... Args>
	void LogToLogger(const ILogger& logger, LogType logType, std::format_string<Args...> format, Args&&... args) noexcept;

	/// @brief Logs the @p exception to the @p logger.
	/// @param logger Logger.
	/// @param exception Exception to log.
	void LogExceptionToLogger(const ILogger& logger, const std::exception& exception) noexcept;
	/// @brief Logs the @p exception to the @p logger.
	/// @param logger Logger.
	/// @param exception Exception to log.
	/// @param message Log message.
	void LogExceptionToLogger(const ILogger& logger, const std::exception& exception, std::string_view message) noexcept;
	/// @brief Logs the @p exception to the @p logger.
	/// @tparam Args Format argument types.
	/// @param logger Logger.
	/// @param exception Exception to log.
	/// @param format Format.
	/// @param args Format arguments.
	template<typename... Args>
	void LogExceptionToLogger(const ILogger& logger, const std::exception& exception, std::format_string<Args...> format, Args&&... args) noexcept;

	/// @brief Logs to a standard console and a platform console.
	/// @param logType Log type.
	/// @param message Log message.
	void LogToConsole(LogType logType, std::string_view message) noexcept;
	/// @brief Logs to a standard console and a platform console.
	/// @tparam Args Format argument types.
	/// @param logType Log type.
	/// @param format Format.
	/// @param args Format arguments.
	template<typename... Args>
	void LogToConsole(LogType logType, std::format_string<Args...> format, Args&&... args) noexcept;

	/// @brief Logs the @p exception to a standard console and a platform console.
	/// @param exception Exception to log.
	void LogExceptionToConsole(const std::exception& exception) noexcept;
	/// @brief Logs the @p exception to a standard console and a platform console.
	/// @param exception Exception to log.
	/// @param message Log message.
	void LogExceptionToConsole(const std::exception& exception, std::string_view message) noexcept;
	/// @brief Logs the @p exception to a standard console and a platform console.
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
}

namespace PonyEngine::Log
{
	/// @brief Passes exceptions to a console.
	struct ConsoleExceptionHandler final
	{
		/// @brief Passes exceptions to a console.
		/// @param e Exception to pass.
		void operator ()(const std::exception& e) const noexcept;
	};

	/// @brief @p std::format() wrapper that doesn't throw. If @p std::format() throws, the exception is passed to the @p ConsoleExceptionHandler.
	/// @tparam Args Format argument types.
	/// @param format Format.
	/// @param args Format arguments.
	/// @return Format result or empty string if std::format() threw.
	template<typename... Args> [[nodiscard("Pure function")]]
	std::string SafeFormat(std::format_string<Args...> format, Args&&... args) noexcept;

	/// @brief Logs to a standard console and a platform console.
	/// @param logType Log type.
	/// @param log Formatted log message.
	void LogFormattedToConsole(LogType logType, std::string_view log) noexcept;

	void LogToLogger(const ILogger& logger, const LogType logType, const std::string_view message) noexcept
	{
		const auto logInput = LogInput{.message = message};
		logger.Log(logType, logInput);
	}

	template<typename... Args>
	void LogToLogger(const ILogger& logger, const LogType logType, std::format_string<Args...> format, Args&&... args) noexcept
	{
		LogToLogger(logger, logType, SafeFormat(format, std::forward<Args>(args)...));
	}

	void LogExceptionToLogger(const ILogger& logger, const std::exception& exception) noexcept
	{
		logger.LogException(exception, LogInput{});
	}

	void LogExceptionToLogger(const ILogger& logger, const std::exception& exception, const std::string_view message) noexcept
	{
		const auto logInput = LogInput{.message = message};
		logger.LogException(exception, logInput);
	}

	template<typename... Args>
	void LogExceptionToLogger(const ILogger& logger, const std::exception& exception, std::format_string<Args...> format, Args&&... args) noexcept
	{
		LogExceptionToLogger(logger, exception, SafeFormat(format, std::forward<Args>(args)...));
	}

	void LogToConsole(const LogType logType, const std::string_view message) noexcept
	{
		try
		{
			const std::string log = message.empty() ? LogFormat(logType, std::chrono::system_clock::now()) : LogFormat(logType, message, std::chrono::system_clock::now());
			LogFormattedToConsole(logType, log);
		}
		catch (...)
		{
			// Something totally wrong happened.
		}
	}

	template<typename... Args>
	void LogToConsole(const LogType logType, std::format_string<Args...> format, Args&&... args) noexcept
	{
		LogToConsole(logType, SafeFormat(format, std::forward<Args>(args)...));
	}

	void LogExceptionToConsole(const std::exception& exception) noexcept
	{
		try
		{
			const std::string log = LogFormat(LogType::Exception, exception.what(), std::chrono::system_clock::now());
			LogFormattedToConsole(LogType::Exception, log);
		}
		catch (...)
		{
			// Something totally wrong happened.
		}
	}

	void LogExceptionToConsole(const std::exception& exception, const std::string_view message) noexcept
	{
		try
		{
			const std::string log = message.empty() ? LogFormat(LogType::Exception, exception.what(), std::chrono::system_clock::now()) : LogFormat(LogType::Exception, exception.what(), message, std::chrono::system_clock::now());
			LogFormattedToConsole(LogType::Exception, log);
		}
		catch (...)
		{
			// Something totally wrong happened.
		}
	}

	template<typename... Args>
	void LogExceptionToConsole(const std::exception& exception, std::format_string<Args...> format, Args&&... args) noexcept
	{
		LogExceptionToConsole(exception, SafeFormat(format, std::forward<Args>(args)...));
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
		default: [[unlikely]]
			assert(false && "Invalid log type.");
			return std::cerr;
		}
	}

	template<typename... Args>
	std::string SafeFormat(std::format_string<Args...> format, Args&&... args) noexcept
	{
		return Utility::SafeFormat<ConsoleExceptionHandler>(format, std::forward<Args>(args)...);
	}

	void LogFormattedToConsole(const LogType logType, const std::string_view log) noexcept
	{
#ifdef PONY_CONSOLE_LOG
		try
		{
			ChooseConsoleStream(logType) << log;
		}
		catch (...)
		{
			// Something totally wrong happened.
		}
#endif
#ifdef PONY_PLATFORM_CONSOLE_LOG
#ifdef PONY_WINCORE
		OutputDebugStringA(log.data());
#endif
#endif
	}

	void ConsoleExceptionHandler::operator ()(const std::exception& e) const noexcept
	{
		LogExceptionToConsole(e);
	}
}
