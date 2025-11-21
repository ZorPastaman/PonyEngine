/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include <catch2/catch_test_macros.hpp>

#ifndef PONY_LOG_VERBOSE
#define PONY_LOG_VERBOSE
#endif
#ifndef PONY_LOG_DEBUG
#define PONY_LOG_DEBUG
#endif
#ifndef PONY_LOG_INFO
#define PONY_LOG_INFO
#endif
#ifndef PONY_LOG_WARNING
#define PONY_LOG_WARNING
#endif
#ifndef PONY_LOG_ERROR
#define PONY_LOG_ERROR
#endif
#ifndef PONY_LOG_EXCEPTION
#define PONY_LOG_EXCEPTION
#endif
#ifdef PONY_LOG_STACKTRACE_VERBOSE
#undef PONY_LOG_STACKTRACE_VERBOSE
#endif
#ifdef PONY_LOG_STACKTRACE_DEBUG
#undef PONY_LOG_STACKTRACE_DEBUG
#endif
#ifdef PONY_LOG_STACKTRACE_INFO
#undef PONY_LOG_STACKTRACE_INFO
#endif
#ifdef PONY_LOG_STACKTRACE_WARNING
#undef PONY_LOG_STACKTRACE_WARNING
#endif
#ifdef PONY_LOG_STACKTRACE_ERROR
#undef PONY_LOG_STACKTRACE_ERROR
#endif
#ifdef PONY_LOG_STACKTRACE_EXCEPTION
#undef PONY_LOG_STACKTRACE_EXCEPTION
#endif
#include "PonyEngine/Log/Console.h"

import std;

import PonyEngine.Log.Ext;

class MockLogger final : public PonyEngine::Log::ILoggerContext
{
public:
	mutable PonyEngine::Log::LogType lastLogType;
	mutable std::string lastMsg;
	mutable std::exception_ptr lastException;
	mutable std::stacktrace lastStacktrace;
	mutable bool logCalled = false;
	mutable bool logExceptionCalled = false;

	[[nodiscard("Pure function")]]
	virtual PonyEngine::Application::IApplicationContext& Application() noexcept override
	{
		std::exit(1);
	}

	[[nodiscard("Pure function")]]
	virtual const PonyEngine::Application::IApplicationContext& Application() const noexcept override
	{
		std::exit(1);
	}

	virtual void LogToConsole(const PonyEngine::Log::LogType logType, const std::string_view message) const noexcept override
	{
		logCalled = true;
		lastLogType = logType;
		lastMsg = message;
	}

	virtual void LogToConsole(const PonyEngine::Log::LogType logType, const std::string_view format, const std::format_args formatArgs) const noexcept override
	{
		logCalled = true;
		lastLogType = logType;
		lastMsg = std::vformat(format, formatArgs);
	}

	virtual void LogToConsole(const PonyEngine::Log::LogType logType, const std::string_view message, const std::stacktrace& stacktrace) const noexcept override
	{
		logCalled = true;
		lastLogType = logType;
		lastMsg = message;
		lastStacktrace = stacktrace;
	}

	virtual void LogToConsole(const PonyEngine::Log::LogType logType, const std::string_view format, const std::format_args formatArgs, const std::stacktrace& stacktrace) const noexcept override
	{
		logCalled = true;
		lastLogType = logType;
		lastMsg = std::vformat(format, formatArgs);
		lastStacktrace = stacktrace;
	}

	virtual void LogToConsole(const std::exception_ptr& exception) const noexcept override
	{
		logExceptionCalled = true;
		lastException = exception;
	}

	virtual void LogToConsole(const std::exception_ptr& exception, const std::string_view message) const noexcept override
	{
		logExceptionCalled = true;
		lastException = exception;
		lastMsg = message;
	}

	virtual void LogToConsole(const std::exception_ptr& exception, const std::string_view format, const std::format_args formatArgs) const noexcept override
	{
		logExceptionCalled = true;
		lastException = exception;
		lastMsg = std::vformat(format, formatArgs);
	}

	virtual void LogToConsole(const std::exception_ptr& exception, const std::stacktrace& stacktrace) const noexcept override
	{
		logExceptionCalled = true;
		lastException = exception;
		lastStacktrace = stacktrace;
	}

	virtual void LogToConsole(const std::exception_ptr& exception, const std::string_view message, const std::stacktrace& stacktrace) const noexcept override
	{
		logExceptionCalled = true;
		lastException = exception;
		lastMsg = message;
		lastStacktrace = stacktrace;
	}

	virtual void LogToConsole(const std::exception_ptr& exception, const std::string_view format, const std::format_args formatArgs, const std::stacktrace& stacktrace) const noexcept override
	{
		logExceptionCalled = true;
		lastException = exception;
		lastMsg = std::vformat(format, formatArgs);
		lastStacktrace = stacktrace;
	}
};

TEST_CASE("PONY_CONSOLE message", "[Log][LogMacro]")
{
	MockLogger logger;
	constexpr std::string_view message = "Test message.";
	PONY_CONSOLE(logger, PonyEngine::Log::LogType::Info, message);

	REQUIRE(logger.logCalled);
	REQUIRE_FALSE(logger.logExceptionCalled);
	REQUIRE(logger.lastLogType == PonyEngine::Log::LogType::Info);
	REQUIRE(logger.lastMsg == message);
	REQUIRE_FALSE(logger.lastException);
	REQUIRE(logger.lastStacktrace.empty());
}

TEST_CASE("PONY_CONSOLE format", "[Log][LogMacro]")
{
	MockLogger logger;
	constexpr std::string_view format = "Test format: '{}'.";
	constexpr std::string_view arg = "argument";
	PONY_CONSOLE(logger, PonyEngine::Log::LogType::Debug, format, arg);

	REQUIRE(logger.logCalled);
	REQUIRE_FALSE(logger.logExceptionCalled);
	REQUIRE(logger.lastLogType == PonyEngine::Log::LogType::Debug);
	REQUIRE(logger.lastMsg == std::vformat(format, std::make_format_args(arg)));
	REQUIRE_FALSE(logger.lastException);
	REQUIRE(logger.lastStacktrace.empty());
}

TEST_CASE("PONY_CONSOLE_IF", "[Log][LogMacro]")
{
	MockLogger logger;
	constexpr std::string_view message = "Test message.";
	PONY_CONSOLE_IF(false, logger, PonyEngine::Log::LogType::Info, message);
	REQUIRE_FALSE(logger.logCalled);

	PONY_CONSOLE_IF(true, logger, PonyEngine::Log::LogType::Info, message);
	REQUIRE(logger.logCalled);
	REQUIRE_FALSE(logger.logExceptionCalled);
	REQUIRE(logger.lastLogType == PonyEngine::Log::LogType::Info);
	REQUIRE(logger.lastMsg == message);
	REQUIRE_FALSE(logger.lastException);
	REQUIRE(logger.lastStacktrace.empty());
}

TEST_CASE("PONY_CONSOLE_X", "[Log][LogMacro]")
{
	MockLogger logger;
	std::exception_ptr exception;
	try
	{
		throw std::runtime_error("Test exception.");
	}
	catch (...)
	{
		exception = std::current_exception();
	}

	PONY_CONSOLE_X(logger, exception);
	REQUIRE_FALSE(logger.logCalled);
	REQUIRE(logger.logExceptionCalled);
	REQUIRE(logger.lastMsg.empty());
	REQUIRE(logger.lastException == exception);
	REQUIRE(logger.lastStacktrace.empty());
}

TEST_CASE("PONY_CONSOLE_X message", "[Log][LogMacro]")
{
	MockLogger logger;
	constexpr std::string_view message = "Test exception message.";
	std::exception_ptr exception;
	try
	{
		throw std::runtime_error("Test exception.");
	}
	catch (...)
	{
		exception = std::current_exception();
	}

	PONY_CONSOLE_X(logger, exception, message);
	REQUIRE_FALSE(logger.logCalled);
	REQUIRE(logger.logExceptionCalled);
	REQUIRE(logger.lastMsg == message);
	REQUIRE(logger.lastException == exception);
	REQUIRE(logger.lastStacktrace.empty());
}

TEST_CASE("PONY_CONSOLE_X format", "[Log][LogMacro]")
{
	MockLogger logger;
	constexpr std::string_view format = "Test exception message: '{}'.";
	constexpr std::string_view arg = "argument";
	std::exception_ptr exception;
	try
	{
		throw std::runtime_error("Test exception.");
	}
	catch (...)
	{
		exception = std::current_exception();
	}

	PONY_CONSOLE_X(logger, exception, format, arg);
	REQUIRE_FALSE(logger.logCalled);
	REQUIRE(logger.logExceptionCalled);
	REQUIRE(logger.lastMsg == std::vformat(format, std::make_format_args(arg)));
	REQUIRE(logger.lastException == exception);
	REQUIRE(logger.lastStacktrace.empty());
}

TEST_CASE("PONY_CONSOLE_X_IF", "[Log][LogMacro]")
{
	MockLogger logger;
	std::exception_ptr exception;
	try
	{
		throw std::runtime_error("Test exception.");
	}
	catch (...)
	{
		exception = std::current_exception();
	}
	PONY_CONSOLE_X_IF(false, logger, exception);
	REQUIRE_FALSE(logger.logExceptionCalled);

	PONY_CONSOLE_X_IF(true, logger, exception);
	REQUIRE_FALSE(logger.logCalled);
	REQUIRE(logger.logExceptionCalled);
	REQUIRE(logger.lastMsg.empty());
	REQUIRE(logger.lastException == exception);
	REQUIRE(logger.lastStacktrace.empty());
}
