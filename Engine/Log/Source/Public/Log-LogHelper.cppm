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

import PonyEngine.Text;

import :ILogger;
import :LogType;

export namespace PonyEngine::Log
{
	// Functions here are used by PonyEngine/Log/Log.h

	void LogToLogger(const ILogger& logger, LogType logType, std::string_view message) noexcept;
	template<typename... Args>
	void LogToLogger(const ILogger& logger, LogType logType, std::format_string<Args...> format, Args&&... args) noexcept;
	void LogToLogger(const ILogger& logger, LogType logType, const std::stacktrace& stacktrace, std::string_view message) noexcept;
	template<typename... Args>
	void LogToLogger(const ILogger& logger, LogType logType, const std::stacktrace& stacktrace, std::format_string<Args...> format, Args&&... args) noexcept;

	void LogToLogger(const ILogger& logger, const std::exception_ptr& exception) noexcept;
	void LogToLogger(const ILogger& logger, const std::exception_ptr& exception, std::string_view message) noexcept;
	template<typename... Args>
	void LogToLogger(const ILogger& logger, const std::exception_ptr& exception, std::format_string<Args...> format, Args&&... args) noexcept;
	void LogToLogger(const ILogger& logger, const std::exception_ptr& exception, const std::stacktrace& stacktrace) noexcept;
	void LogToLogger(const ILogger& logger, const std::exception_ptr& exception, const std::stacktrace& stacktrace, std::string_view message) noexcept;
	template<typename... Args>
	void LogToLogger(const ILogger& logger, const std::exception_ptr& exception, const std::stacktrace& stacktrace, std::format_string<Args...> format, Args&&... args) noexcept;
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

	void LogToLogger(const ILogger& logger, const std::exception_ptr& exception) noexcept
	{
		logger.Log(exception);
	}

	template<typename... Args>
	void LogToLogger(const ILogger& logger, const LogType logType, const std::stacktrace& stacktrace, const std::format_string<Args...> format, Args&&... args) noexcept
	{
		logger.Log(logType, format.get(), std::make_format_args(args...), stacktrace);
	}

	void LogToLogger(const ILogger& logger, const std::exception_ptr& exception, const std::string_view message) noexcept
	{
		logger.Log(exception, message);
	}

	template<typename... Args>
	void LogToLogger(const ILogger& logger, const std::exception_ptr& exception, const std::format_string<Args...> format, Args&&... args) noexcept
	{
		logger.Log(exception, format.get(), std::make_format_args(args...));
	}

	void LogToLogger(const ILogger& logger, const std::exception_ptr& exception, const std::stacktrace& stacktrace) noexcept
	{
		logger.Log(exception, stacktrace);
	}

	void LogToLogger(const ILogger& logger, const std::exception_ptr& exception, const std::stacktrace& stacktrace, const std::string_view message) noexcept
	{
		logger.Log(exception, message, stacktrace);
	}

	template<typename... Args>
	void LogToLogger(const ILogger& logger, const std::exception_ptr& exception, const std::stacktrace& stacktrace, const std::format_string<Args...> format, Args&&... args) noexcept
	{
		logger.Log(exception, format.get(), std::make_format_args(args...), stacktrace);
	}
}
