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
#ifndef PONY_LOG_STACKTRACE_VERBOSE
#define PONY_LOG_STACKTRACE_VERBOSE
#endif
#ifndef PONY_LOG_STACKTRACE_DEBUG
#define PONY_LOG_STACKTRACE_DEBUG
#endif
#ifndef PONY_LOG_STACKTRACE_INFO
#define PONY_LOG_STACKTRACE_INFO
#endif
#ifndef PONY_LOG_STACKTRACE_WARNING
#define PONY_LOG_STACKTRACE_WARNING
#endif
#ifndef PONY_LOG_STACKTRACE_ERROR
#define PONY_LOG_STACKTRACE_ERROR
#endif
#ifndef PONY_LOG_STACKTRACE_EXCEPTION
#define PONY_LOG_STACKTRACE_EXCEPTION
#endif
#include "PonyEngine/Log/Log.h"

import std;

import PonyEngine.Application;
import PonyEngine.Log;

class MockLogger final : public PonyEngine::Log::ILogger
{
public:
	mutable PonyEngine::Log::LogType lastLogType;
	mutable std::string lastMsg;
	mutable std::string lastExceptionMsg;
	mutable std::stacktrace lastStacktrace;
	mutable bool logCalled = false;
	mutable bool logExceptionCalled = false;

	virtual void Log(const PonyEngine::Log::LogType logType, const std::string_view message, const PonyEngine::Log::LogData& logData = PonyEngine::Log::LogData()) const noexcept override
	{
		logCalled = true;
		lastLogType = logType;
		lastMsg = message;
		lastStacktrace = logData.stacktrace ? *logData.stacktrace : std::stacktrace();
	}

	virtual void Log(const std::exception& exception, const std::string_view message, const PonyEngine::Log::LogData& logData = PonyEngine::Log::LogData()) const noexcept override
	{
		logExceptionCalled = true;
		lastExceptionMsg = exception.what();
		lastMsg = message;
		lastStacktrace = logData.stacktrace ? *logData.stacktrace : std::stacktrace();
	}
};

class MockApplication final : public PonyEngine::Application::IApplicationContext
{
public:
	MockLogger logger;

	mutable bool logCalled = false;
	mutable PonyEngine::Log::LogType lastType;
	mutable std::string lastMsg;

	[[nodiscard("Pure function")]]
	virtual std::string_view CompanyName() const noexcept override
	{
		return std::string_view();
	}

	[[nodiscard("Pure function")]]
	virtual std::string_view ProjectName() const noexcept override
	{
		return std::string_view();
	}

	[[nodiscard("Pure function")]]
	virtual std::string_view ProjectVersion() const noexcept override
	{
		return std::string_view();
	}

	[[nodiscard("Pure function")]]
	virtual std::string_view CompanyTitle() const noexcept override
	{
		return std::string_view();
	}

	[[nodiscard("Pure function")]]
	virtual std::string_view ProjectTitle() const noexcept override
	{
		return std::string_view();
	}

	[[nodiscard("Pure function")]]
	virtual PonyEngine::Log::ILogger& Logger() noexcept override
	{
		return logger;
	}

	[[nodiscard("Pure function")]]
	virtual const PonyEngine::Log::ILogger& Logger() const noexcept override
	{
		return logger;
	}

	virtual void LogToConsole(const PonyEngine::Log::LogType logType, const std::string_view message) const noexcept override
	{
		logCalled = true;
		lastType = logType;
		lastMsg = message;
	}

	[[nodiscard("Pure function")]]
	virtual void* FindService(const std::type_info& type) noexcept override
	{
		return nullptr;
	}

	[[nodiscard("Pure function")]]
	virtual const void* FindService(const std::type_info& type) const noexcept override
	{
		return nullptr;
	}

	[[nodiscard("Pure function")]]
	virtual bool IsRunning() const noexcept override
	{
		return false;
	}

	[[nodiscard("Pure function")]]
	virtual int ExitCode() const noexcept override
	{
		return 0;
	}

	virtual void Stop(const int exitCode) noexcept override
	{
	}

	[[nodiscard("Pure function")]]
	virtual std::uint64_t FrameCount() const noexcept override
	{
		return 0ull;
	}
};

TEST_CASE("PONY_LOG", "[Log][LogMacro]")
{
	MockLogger logger;
	PONY_LOG(logger, PonyEngine::Log::LogType::Warning, "Format: {}.", "Arg");

	REQUIRE(logger.logCalled);
	REQUIRE_FALSE(logger.logExceptionCalled);
	REQUIRE(logger.lastLogType == PonyEngine::Log::LogType::Warning);
	REQUIRE(logger.lastMsg == std::format("Format: {}.", "Arg"));
	REQUIRE_FALSE(logger.lastStacktrace.empty());
}

TEST_CASE("PONY_LOG_IF", "[Log][LogMacro]")
{
	MockLogger logger;
	PONY_LOG_IF(false, logger, PonyEngine::Log::LogType::Warning, "Format: {}.", "Arg");

	REQUIRE_FALSE(logger.logCalled);
	REQUIRE_FALSE(logger.logExceptionCalled);

	PONY_LOG_IF(true, logger, PonyEngine::Log::LogType::Warning, "Format: {}.", "Arg");

	REQUIRE(logger.logCalled);
	REQUIRE_FALSE(logger.logExceptionCalled);
	REQUIRE(logger.lastLogType == PonyEngine::Log::LogType::Warning);
	REQUIRE(logger.lastMsg == std::format("Format: {}.", "Arg"));
	REQUIRE_FALSE(logger.lastStacktrace.empty());
}

TEST_CASE("PONY_LOG_E_S", "[Log][LogMacro]")
{
	MockLogger logger;
	const auto exception = std::logic_error("Test!");
	PONY_LOG_E_S(logger, exception);

	REQUIRE_FALSE(logger.logCalled);
	REQUIRE(logger.logExceptionCalled);
	REQUIRE(logger.lastExceptionMsg == exception.what());
	REQUIRE_FALSE(logger.lastStacktrace.empty());
}

TEST_CASE("PONY_LOG_E_S_IF", "[Log][LogMacro]")
{
	MockLogger logger;
	const auto exception = std::logic_error("Test!");
	PONY_LOG_E_S_IF(false, logger, exception);

	REQUIRE_FALSE(logger.logCalled);
	REQUIRE_FALSE(logger.logExceptionCalled);

	PONY_LOG_E_S_IF(true, logger, exception);

	REQUIRE_FALSE(logger.logCalled);
	REQUIRE(logger.logExceptionCalled);
	REQUIRE(logger.lastExceptionMsg == exception.what());
	REQUIRE_FALSE(logger.lastStacktrace.empty());
}

TEST_CASE("PONY_LOG_E", "[Log][LogMacro]")
{
	MockLogger logger;
	const auto exception = std::logic_error("Test!");
	PONY_LOG_E(logger, exception, "Format: {}.", "Arg");

	REQUIRE_FALSE(logger.logCalled);
	REQUIRE(logger.logExceptionCalled);
	REQUIRE(logger.lastExceptionMsg == exception.what());
	REQUIRE(logger.lastMsg == std::format("Format: {}.", "Arg"));
	REQUIRE_FALSE(logger.lastStacktrace.empty());
}

TEST_CASE("PONY_LOG_E_IF", "[Log][LogMacro]")
{
	MockLogger logger;
	const auto exception = std::logic_error("Test!");
	PONY_LOG_E_IF(false, logger, exception, "Format: {}.", "Arg");

	REQUIRE_FALSE(logger.logCalled);
	REQUIRE_FALSE(logger.logExceptionCalled);

	PONY_LOG_E_IF(true, logger, exception, "Format: {}.", "Arg");

	REQUIRE_FALSE(logger.logCalled);
	REQUIRE(logger.logExceptionCalled);
	REQUIRE(logger.lastExceptionMsg == exception.what());
	REQUIRE(logger.lastMsg == std::format("Format: {}.", "Arg"));
	REQUIRE_FALSE(logger.lastStacktrace.empty());
}

TEST_CASE("PONY_CONSOLE", "[Log][LogMacro]")
{
	MockApplication application;

	PONY_CONSOLE(application, PonyEngine::Log::LogType::Warning, "Format: {}.", "Arg");
	REQUIRE(application.logCalled);
	REQUIRE(application.lastType == PonyEngine::Log::LogType::Warning);
	REQUIRE(application.lastMsg.contains(std::format("Format: {}.", "Arg")));
}

TEST_CASE("PONY_CONSOLE_IF", "[Log][LogMacro]")
{
	MockApplication application;

	PONY_CONSOLE_IF(false, application, PonyEngine::Log::LogType::Warning, "Format: {}.", "Arg");
	REQUIRE_FALSE(application.logCalled);

	PONY_CONSOLE_IF(true, application, PonyEngine::Log::LogType::Warning, "Format: {}.", "Arg");
	REQUIRE(application.logCalled);
	REQUIRE(application.lastType == PonyEngine::Log::LogType::Warning);
	REQUIRE(application.lastMsg.contains(std::format("Format: {}.", "Arg")));
}

TEST_CASE("PONY_CONSOLE_E_S", "[Log][LogMacro]")
{
	MockApplication application;
	const auto exception = std::logic_error("Test!");

	PONY_CONSOLE_E_S(application, exception);
	REQUIRE(application.logCalled);
	REQUIRE(application.lastType == PonyEngine::Log::LogType::Exception);
}

TEST_CASE("PONY_CONSOLE_E_S_IF", "[Log][LogMacro]")
{
	MockApplication application;
	const auto exception = std::logic_error("Test!");

	PONY_CONSOLE_E_S_IF(false, application, exception);
	REQUIRE_FALSE(application.logCalled);

	PONY_CONSOLE_E_S_IF(true, application, exception);
	REQUIRE(application.logCalled);
	REQUIRE(application.lastType == PonyEngine::Log::LogType::Exception);
}

TEST_CASE("PONY_CONSOLE_E", "[Log][LogMacro]")
{
	MockApplication application;
	const auto exception = std::logic_error("Test!");

	PONY_CONSOLE_E(application, exception, "Format: {}.", "Arg");
	REQUIRE(application.logCalled);
	REQUIRE(application.lastType == PonyEngine::Log::LogType::Exception);
	REQUIRE(application.lastMsg.contains(std::format("Format: {}.", "Arg")));
}

TEST_CASE("PONY_CONSOLE_E_IF", "[Log][LogMacro]")
{
	MockApplication application;
	const auto exception = std::logic_error("Test!");

	PONY_CONSOLE_E_IF(false, application, exception, "Format: {}.", "Arg");
	REQUIRE_FALSE(application.logCalled);

	PONY_CONSOLE_E_IF(true, application, exception, "Format: {}.", "Arg");
	REQUIRE(application.logCalled);
	REQUIRE(application.lastType == PonyEngine::Log::LogType::Exception);
	REQUIRE(application.lastMsg.contains(std::format("Format: {}.", "Arg")));
}
