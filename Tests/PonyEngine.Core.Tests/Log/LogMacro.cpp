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

import PonyEngine.Log;

class MockLogger final : public PonyEngine::Log::ILogger
{
public:
	mutable PonyEngine::Log::LogType lastLogType;
	mutable std::string lastMsg;
	mutable std::optional<std::uint64_t> lastFrame;
	mutable std::string lastExceptionMsg;
	mutable std::stacktrace lastStacktrace;
	mutable bool logCalled = false;
	mutable bool logExceptionCalled = false;

	virtual void Log(const PonyEngine::Log::LogType logType, const PonyEngine::Log::LogInput& logInput) const noexcept override
	{
		logCalled = true;
		lastLogType = logType;
		lastMsg = logInput.message;
		lastFrame = logInput.frameCount;
		lastStacktrace = logInput.stacktrace ? *logInput.stacktrace : std::stacktrace();
	}

	virtual void Log(const std::exception& exception, const PonyEngine::Log::LogInput& logInput) const noexcept override
	{
		logExceptionCalled = true;
		lastExceptionMsg = exception.what();
		lastMsg = logInput.message;
		lastFrame = logInput.frameCount;
		lastStacktrace = logInput.stacktrace ? *logInput.stacktrace : std::stacktrace();
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

/*
TEST_CASE("PONY_CONSOLE compilation", "[Log][LogMacro]")
{
	PONY_CONSOLE(PonyEngine::Log::LogType::Info, "Format: {}", "Arg!");
	PONY_CONSOLE_IF(true, PonyEngine::Log::LogType::Info, "Format: {}", "Arg!");
	PONY_CONSOLE_E_S(std::runtime_error("Test!"));
	PONY_CONSOLE_E_S_IF(true, std::runtime_error("Test!"));
	PONY_CONSOLE_E_IF(true, std::runtime_error("Test!"), "Format: {}", "Arg!");
	PONY_CONSOLE_E(std::runtime_error("Test!"), "Format: {}", "Arg!");
	PONY_CONSOLE_E_IF(true, std::runtime_error("Test!"), "Format: {}", "Arg!");
}
*/
