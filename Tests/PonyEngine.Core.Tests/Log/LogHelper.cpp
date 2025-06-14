/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include <catch2/catch_test_macros.hpp>

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

TEST_CASE("LogToLogger: basic", "[Log][LogHelper]")
{
	MockLogger logger;
	PonyEngine::Log::LogData data;
	constexpr auto logType = PonyEngine::Log::LogType::Info;

	PonyEngine::Log::LogToLogger(logger, logType, data);

	REQUIRE(logger.logCalled);
	REQUIRE_FALSE(logger.logExceptionCalled);
	REQUIRE(logger.lastLogType == logType);
	REQUIRE(logger.lastMsg.empty());
	REQUIRE(logger.lastStacktrace.empty());
}

TEST_CASE("LogToLogger: message", "[Log][LogHelper]")
{
	MockLogger logger;
	PonyEngine::Log::LogData data;
	constexpr auto logType = PonyEngine::Log::LogType::Warning;
	constexpr std::string_view message = "Message";

	PonyEngine::Log::LogToLogger(logger, logType, data, message);

	REQUIRE(logger.logCalled);
	REQUIRE_FALSE(logger.logExceptionCalled);
	REQUIRE(logger.lastLogType == logType);
	REQUIRE(logger.lastMsg == message);
	REQUIRE(logger.lastStacktrace.empty());
}

TEST_CASE("LogToLogger: exception", "[Log][LogHelper]")
{
	MockLogger logger;
	const auto exception = std::runtime_error("Test");
	PonyEngine::Log::LogData data;

	PonyEngine::Log::LogToLogger(logger, exception, data);

	REQUIRE_FALSE(logger.logCalled);
	REQUIRE(logger.logExceptionCalled);
	REQUIRE(logger.lastMsg.empty());
	REQUIRE(logger.lastExceptionMsg == exception.what());
	REQUIRE(logger.lastStacktrace.empty());
}

TEST_CASE("LogToLogger: exception, message", "[Log][LogHelper]")
{
	MockLogger logger;
	const auto exception = std::runtime_error("Test");
	PonyEngine::Log::LogData data;
	constexpr std::string_view message = "Message";

	PonyEngine::Log::LogToLogger(logger, exception, data, message);

	REQUIRE_FALSE(logger.logCalled);
	REQUIRE(logger.logExceptionCalled);
	REQUIRE(logger.lastMsg == message);
	REQUIRE(logger.lastExceptionMsg == exception.what());
	REQUIRE(logger.lastStacktrace.empty());
}

TEST_CASE("LogToLogger: stacktrace", "[Log][LogHelper]")
{
	MockLogger logger;
	PonyEngine::Log::LogData data;
	constexpr auto logType = PonyEngine::Log::LogType::Debug;
	data.stacktrace = std::stacktrace::current();

	PonyEngine::Log::LogToLogger(logger, logType, data);

	REQUIRE(logger.logCalled);
	REQUIRE_FALSE(logger.logExceptionCalled);
	REQUIRE(logger.lastLogType == logType);
	REQUIRE(logger.lastStacktrace == data.stacktrace);
}

TEST_CASE("LogToLogger: stacktrace, message", "[Log][LogHelper]")
{
	MockLogger logger;
	PonyEngine::Log::LogData data;
	constexpr auto logType = PonyEngine::Log::LogType::Debug;
	data.stacktrace = std::stacktrace::current();
	constexpr std::string_view message = "Message";

	PonyEngine::Log::LogToLogger(logger, logType, data, message);

	REQUIRE(logger.logCalled);
	REQUIRE_FALSE(logger.logExceptionCalled);
	REQUIRE(logger.lastLogType == logType);
	REQUIRE(logger.lastMsg == message);
	REQUIRE(logger.lastStacktrace == data.stacktrace);
}

TEST_CASE("LogToLogger: stacktrace, exception", "[Log][LogHelper]")
{
	MockLogger logger;
	const auto exception = std::runtime_error("Test");
	PonyEngine::Log::LogData data;
	data.stacktrace = std::stacktrace::current();

	PonyEngine::Log::LogToLogger(logger, exception, data);

	REQUIRE_FALSE(logger.logCalled);
	REQUIRE(logger.logExceptionCalled);
	REQUIRE(logger.lastExceptionMsg == exception.what());
	REQUIRE(logger.lastStacktrace == data.stacktrace);
}

TEST_CASE("LogToLogger: stacktrace, exception, message", "[Log][LogHelper]")
{
	MockLogger logger;
	const auto exception = std::runtime_error("Test");
	PonyEngine::Log::LogData data;
	data.stacktrace = std::stacktrace::current();
	constexpr std::string_view message = "Message";

	PonyEngine::Log::LogToLogger(logger, exception, data, message);

	REQUIRE_FALSE(logger.logCalled);
	REQUIRE(logger.logExceptionCalled);
	REQUIRE(logger.lastMsg == message);
	REQUIRE(logger.lastExceptionMsg == exception.what());
	REQUIRE(logger.lastStacktrace == data.stacktrace);
}

TEST_CASE("LogToLogger with format: message", "[Log][LogHelper]")
{
	MockLogger logger;
	PonyEngine::Log::LogData data;
	constexpr auto logType = PonyEngine::Log::LogType::Warning;
	constexpr std::string_view format = "Message: {}";
	constexpr std::string_view arg = "Arg!";

	PonyEngine::Log::LogToLogger(logger, logType, data, format, arg);

	REQUIRE(logger.logCalled);
	REQUIRE_FALSE(logger.logExceptionCalled);
	REQUIRE(logger.lastLogType == logType);
	REQUIRE(logger.lastMsg == std::format(format, arg));
	REQUIRE(logger.lastStacktrace.empty());
}

TEST_CASE("LogToLogger with format: exception, message", "[Log][LogHelper]")
{
	MockLogger logger;
	const auto exception = std::runtime_error("Test");
	PonyEngine::Log::LogData data;
	constexpr std::string_view format = "Message: {}";
	constexpr std::string_view arg = "Arg!";

	PonyEngine::Log::LogToLogger(logger, exception, data, format, arg);

	REQUIRE_FALSE(logger.logCalled);
	REQUIRE(logger.logExceptionCalled);
	REQUIRE(logger.lastMsg == std::format(format, arg));
	REQUIRE(logger.lastExceptionMsg == exception.what());
	REQUIRE(logger.lastStacktrace.empty());
}

TEST_CASE("LogToLogger with format: stacktrace, message", "[Log][LogHelper]")
{
	MockLogger logger;
	PonyEngine::Log::LogData data;
	constexpr auto logType = PonyEngine::Log::LogType::Debug;
	data.stacktrace = std::stacktrace::current();
	constexpr std::string_view format = "Message: {}";
	constexpr std::string_view arg = "Arg!";

	PonyEngine::Log::LogToLogger(logger, logType, data, format, arg);

	REQUIRE(logger.logCalled);
	REQUIRE_FALSE(logger.logExceptionCalled);
	REQUIRE(logger.lastLogType == logType);
	REQUIRE(logger.lastMsg == std::format(format, arg));
	REQUIRE(logger.lastStacktrace == data.stacktrace);
}

TEST_CASE("LogToLogger with format: stacktrace, exception, message", "[Log][LogHelper]")
{
	MockLogger logger;
	const auto exception = std::runtime_error("Test");
	PonyEngine::Log::LogData data;
	data.stacktrace = std::stacktrace::current();
	constexpr std::string_view format = "Message: {}";
	constexpr std::string_view arg = "Arg!";

	PonyEngine::Log::LogToLogger(logger, exception, data, format, arg);

	REQUIRE_FALSE(logger.logCalled);
	REQUIRE(logger.logExceptionCalled);
	REQUIRE(logger.lastMsg == std::format(format, arg));
	REQUIRE(logger.lastExceptionMsg == exception.what());
	REQUIRE(logger.lastStacktrace == data.stacktrace);
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
