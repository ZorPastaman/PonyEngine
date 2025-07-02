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

#include "PonyEngine/Log/Log.h"
#ifdef PONY_PLATFORM_CONSOLE_LOG
#ifdef PONY_WINCORE
#include "PonyEngine/Platform/WinCore/Framework.h"
#endif
#endif

export module PonyEngine.Log:LogHelper;

import std;

import PonyEngine.Utility;

import :ILogger;
import :LogData;
import :LogFormat;
import :LogInput;
import :LogType;

export namespace PonyEngine::Log
{
	/// @brief Logs to the @p logger.
	/// @param logger Logger.
	/// @param logType Log type.
	/// @param logData Log data.
	/// @param message Log message.
	void LogToLogger(const ILogger& logger, LogType logType, const LogData& logData, std::string_view message = std::string_view()) noexcept;
	/// @brief Logs to the @p logger.
	/// @tparam Args Format argument types.
	/// @param logger Logger.
	/// @param logType Log type.
	/// @param logData Log data.
	/// @param format Format.
	/// @param args Format arguments.
	template<typename... Args>
	void LogToLogger(const ILogger& logger, LogType logType, const LogData& logData, std::format_string<Args...> format, Args&&... args) noexcept;
	/// @brief Logs to the @p logger.
	/// @param logger Logger.
	/// @param exception Exception.
	/// @param logData Log data.
	/// @param message Log message.
	void LogToLogger(const ILogger& logger, const std::exception& exception, const LogData& logData, std::string_view message = std::string_view()) noexcept;
	/// @brief Logs to the @p logger.
	/// @tparam Args Format argument types.
	/// @param logger Logger.
	/// @param exception Exception.
	/// @param logData Log data.
	/// @param format Format.
	/// @param args Format arguments.
	template<typename... Args>
	void LogToLogger(const ILogger& logger, const std::exception& exception, const LogData& logData, std::format_string<Args...> format, Args&&... args) noexcept;

	/// @brief Logs to a standard console and a platform console.
	/// @param logType Log type.
	/// @param logData Log data.
	/// @param message Log message.
	void LogToConsole(LogType logType, const LogData& logData, std::string_view message = std::string_view()) noexcept;
	/// @brief Logs to a standard console and a platform console.
	/// @tparam Args Format argument types.
	/// @param logType Log type.
	/// @param logData Log data.
	/// @param format Format.
	/// @param args Format arguments.
	template<typename... Args>
	void LogToConsole(LogType logType, const LogData& logData, std::format_string<Args...> format, Args&&... args) noexcept;
	/// @brief Logs to a standard console and a platform console.
	/// @param exception Exception.
	/// @param logData Log data.
	/// @param message Log message.
	void LogToConsole(const std::exception& exception, const LogData& logData, std::string_view message = std::string_view()) noexcept;
	/// @brief Logs to a standard console and a platform console.
	/// @tparam Args Format argument types.
	/// @param exception Exception.
	/// @param logData Log data.
	/// @param format Format.
	/// @param args Format arguments.
	template<typename... Args>
	void LogToConsole(const std::exception& exception, const LogData& logData, std::format_string<Args...> format, Args&&... args) noexcept;

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

	/// @brief Formats the log.
	/// @param logType Log type.
	/// @param logData Log data.
	/// @param timePoint Time point.
	/// @param message Log massage.
	/// @return Formatted log.
	[[nodiscard("Pure function")]]
	std::string Format(LogType logType, const LogData& logData, std::chrono::time_point<std::chrono::system_clock> timePoint, std::string_view message);
	/// @brief Formats the log.
	/// @param exception Exception.
	/// @param logData Log data.
	/// @param timePoint Time point.
	/// @param message Log massage.
	/// @return Formatted log.
	[[nodiscard("Pure function")]]
	std::string Format(const std::exception& exception, const LogData& logData, std::chrono::time_point<std::chrono::system_clock> timePoint, std::string_view message);
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

	void LogToLogger(const ILogger& logger, const LogType logType, const LogData& logData, const std::string_view message) noexcept
	{
		const auto logInput = LogInput{.message = message, .stacktrace = logData.stacktrace.has_value() ? &logData.stacktrace.value() : nullptr};
		logger.Log(logType, logInput);
	}

	template<typename... Args>
	void LogToLogger(const ILogger& logger, const LogType logType, const LogData& logData, const std::format_string<Args...> format, Args&&... args) noexcept
	{
		LogToLogger(logger, logType, logData, SafeFormat(format, std::forward<Args>(args)...));
	}

	void LogToLogger(const ILogger& logger, const std::exception& exception, const LogData& logData, const std::string_view message) noexcept
	{
		const auto logInput = LogInput{.message = message, .stacktrace = logData.stacktrace.has_value() ? &logData.stacktrace.value() : nullptr};
		logger.Log(exception, logInput);
	}

	template<typename... Args>
	void LogToLogger(const ILogger& logger, const std::exception& exception, const LogData& logData, const std::format_string<Args...> format, Args&&... args) noexcept
	{
		LogToLogger(logger, exception, logData, SafeFormat(format, std::forward<Args>(args)...));
	}

	void LogToConsole(const LogType logType, const LogData& logData, const std::string_view message) noexcept
	{
		try
		{
			const std::string log = Format(logType, logData, std::chrono::system_clock::now(), message);
			LogFormattedToConsole(logType, log);
		}
		catch (...)
		{
			// Something totally wrong happened.
		}
	}

	template<typename... Args>
	void LogToConsole(const LogType logType, const LogData& logData, const std::format_string<Args...> format, Args&&... args) noexcept
	{
		LogToConsole(logType, logData, SafeFormat(format, std::forward<Args>(args)...));
	}

	void LogToConsole(const std::exception& exception, const LogData& logData, const std::string_view message) noexcept
	{
		try
		{
			const std::string log = Format(exception, logData, std::chrono::system_clock::now(), message);
			LogFormattedToConsole(LogType::Exception, log);
		}
		catch (...)
		{
			// Something totally wrong happened.
		}
	}

	template<typename... Args>
	void LogToConsole(const std::exception& exception, const LogData& logData, const std::format_string<Args...> format, Args&&... args) noexcept
	{
		LogToConsole(exception, logData, SafeFormat(format, std::forward<Args>(args)...));
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

	std::string Format(const LogType logType, const LogData& logData, const std::chrono::time_point<std::chrono::system_clock> timePoint, const std::string_view message)
	{
		switch ((logData.stacktrace.has_value() << 1) | (!message.empty()))
		{
		case 0:
			return LogFormat(logType, timePoint);
		case 1:
			return LogFormat(logType, message, timePoint);
		case 2:
			return LogFormat(logType, timePoint, logData.stacktrace.value());
		case 3:
			return LogFormat(logType, message, timePoint, logData.stacktrace.value());
		default: [[unlikely]]
			return LogFormat(logType, message.empty() ? "Unknown message" : message, timePoint, logData.stacktrace.has_value() ? logData.stacktrace.value() : std::stacktrace::current());
		}
	}

	std::string Format(const std::exception& exception, const LogData& logData, const std::chrono::time_point<std::chrono::system_clock> timePoint, const std::string_view message)
	{
		switch ((logData.stacktrace.has_value() << 1) | (!message.empty()))
		{
		case 0:
			return LogFormat(LogType::Exception, exception.what(), timePoint);
		case 1:
			return LogFormat(LogType::Exception, exception.what(), message, timePoint);
		case 2:
			return LogFormat(LogType::Exception, exception.what(), timePoint, logData.stacktrace.value());
		case 3:
			return LogFormat(LogType::Exception, exception.what(), message, timePoint, logData.stacktrace.value());
		default: [[unlikely]]
			return LogFormat(LogType::Exception, exception.what(), message.empty() ? "Unknown message" : message, timePoint, logData.stacktrace.has_value() ? logData.stacktrace.value() : std::stacktrace::current());
		}
	}

	template<typename... Args>
	std::string SafeFormat(const std::format_string<Args...> format, Args&&... args) noexcept
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
		PONY_CONSOLE_E_S(e);
	}
}
