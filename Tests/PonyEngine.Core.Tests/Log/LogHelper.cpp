/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include <exception>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>

#include <catch2/catch_test_macros.hpp>

import PonyEngine.Log;

class MockLogger final : public PonyEngine::Log::ILogger
{
public:
	mutable PonyEngine::Log::LogType lastLogType;
	mutable std::string lastMsg;
	mutable std::optional<std::uint64_t> lastFrame;
	mutable std::string lastExceptionMsg;
	mutable bool logCalled = false;
	mutable bool logExceptionCalled = false;

	virtual void Log(const PonyEngine::Log::LogType logType, const PonyEngine::Log::LogInput& logInput) const noexcept override
	{
		logCalled = true;
		lastLogType = logType;
		lastMsg = logInput.message;
		lastFrame = logInput.frameCount;
	}

	virtual void LogException(const std::exception& exception, const PonyEngine::Log::LogInput& logInput) const noexcept override
	{
		logExceptionCalled = true;
		lastExceptionMsg = exception.what();
		lastMsg = logInput.message;
		lastFrame = logInput.frameCount;
	}
};

TEST_CASE("LogToLogger logs message to logger", "[Log][LogHelper]")
{
	MockLogger logger;
	LogToLogger(logger, PonyEngine::Log::LogType::Info, "Test message");
	REQUIRE(logger.logCalled);
	REQUIRE(logger.lastLogType == PonyEngine::Log::LogType::Info);
	REQUIRE(logger.lastMsg == "Test message");
}

TEST_CASE("LogToLogger (format) logs formatted message", "[Log][LogHelper]")
{
	MockLogger logger;
	LogToLogger(logger, PonyEngine::Log::LogType::Debug, "Value: {}", 42);
	REQUIRE(logger.logCalled);
	REQUIRE(logger.lastLogType == PonyEngine::Log::LogType::Debug);
	REQUIRE(logger.lastMsg.find("42") != std::string::npos);
}

TEST_CASE("LogExceptionToLogger logs exception", "[Log][LogHelper]")
{
	MockLogger logger;
	const std::runtime_error ex("Exception occurred");
	LogExceptionToLogger(logger, ex);
	REQUIRE(logger.logExceptionCalled);
	REQUIRE(logger.lastExceptionMsg == std::string("Exception occurred"));
}

TEST_CASE("LogExceptionToLogger logs exception with message", "[Log][LogHelper]")
{
	MockLogger logger;
	const std::runtime_error ex("Exception occurred");
	LogExceptionToLogger(logger, ex, "Extra info");
	REQUIRE(logger.logExceptionCalled);
	REQUIRE(logger.lastExceptionMsg == std::string("Exception occurred"));
	REQUIRE(logger.lastMsg == "Extra info");
}

TEST_CASE("LogExceptionToLogger (format) logs exception with formatted message", "[Log][LogHelper]")
{
	MockLogger logger;
	const std::runtime_error ex("Exception occurred");
	LogExceptionToLogger(logger, ex, "Error code: {}", 404);
	REQUIRE(logger.logExceptionCalled);
	REQUIRE(logger.lastExceptionMsg == std::string("Exception occurred"));
	REQUIRE(logger.lastMsg.find("404") != std::string::npos);
}

TEST_CASE("ChooseConsoleStream returns correct stream", "[Log][LogHelper]")
{
	REQUIRE(&PonyEngine::Log::ChooseConsoleStream(PonyEngine::Log::LogType::Info) == &std::cout);
	REQUIRE(&PonyEngine::Log::ChooseConsoleStream(PonyEngine::Log::LogType::Debug) == &std::cout);
	REQUIRE(&PonyEngine::Log::ChooseConsoleStream(PonyEngine::Log::LogType::Verbose) == &std::cout);
	REQUIRE(&PonyEngine::Log::ChooseConsoleStream(PonyEngine::Log::LogType::Warning) == &std::clog);
	REQUIRE(&PonyEngine::Log::ChooseConsoleStream(PonyEngine::Log::LogType::Error) == &std::cerr);
	REQUIRE(&PonyEngine::Log::ChooseConsoleStream(PonyEngine::Log::LogType::Exception) == &std::cerr);
}
