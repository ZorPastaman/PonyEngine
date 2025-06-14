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

TEST_CASE("LogFormat: logType and timePoint", "[Log][LogFormat]") 
{
	constexpr auto lt = PonyEngine::Log::LogType::Verbose;
	const auto tp = std::chrono::system_clock::from_time_t(1717430400);
	std::string expected = std::format("[{}] [{:%F %R:%OS UTC}]\n", lt, tp);
	REQUIRE(PonyEngine::Log::LogFormat(lt, tp) == expected);
}

TEST_CASE("LogFormat: logType, timePoint, frameCount", "[Log][LogFormat]") 
{
	constexpr auto lt = PonyEngine::Log::LogType::Warning;
	const auto tp = std::chrono::system_clock::from_time_t(1717430400);
	constexpr std::uint64_t frame = 42;
	std::string expected = std::format("[{}] [{:%F %R:%OS UTC} ({})]\n", lt, tp, frame);
	REQUIRE(PonyEngine::Log::LogFormat(lt, tp, frame) == expected);
}

TEST_CASE("LogFormat: logType, message, timePoint", "[Log][LogFormat]") 
{
	constexpr auto lt = PonyEngine::Log::LogType::Error;
	const auto tp = std::chrono::system_clock::from_time_t(1717430400);
	constexpr std::string_view message = "Hello";
	std::string expected = std::format("[{}] [{:%F %R:%OS UTC}] {}\n", lt, tp, message);
	REQUIRE(PonyEngine::Log::LogFormat(lt, message, tp) == expected);
}

TEST_CASE("LogFormat: logType, message, timePoint, frameCount", "[Log][LogFormat]") 
{
	constexpr auto lt = PonyEngine::Log::LogType::Debug;
	const auto tp = std::chrono::system_clock::from_time_t(1717430400);
	constexpr std::string_view message = "World";
	constexpr std::uint64_t frame = 42;
	std::string expected = std::format("[{}] [{:%F %R:%OS UTC} ({})] {}\n", lt, tp, frame, message);
	REQUIRE(PonyEngine::Log::LogFormat(lt, message, tp, frame) == expected);
}

TEST_CASE("LogFormat: logType, firstMessage, secondMessage, timePoint", "[Log][LogFormat]") 
{
	constexpr auto lt = PonyEngine::Log::LogType::Exception;
	const auto tp = std::chrono::system_clock::from_time_t(1717430400);
	constexpr std::string_view firstMessage = "Foo";
	constexpr std::string_view secondMessage = "Bar";
	std::string expected = std::format("[{}] [{:%F %R:%OS UTC}] {} - {}\n", lt, tp, firstMessage, secondMessage);
	REQUIRE(PonyEngine::Log::LogFormat(lt, firstMessage, secondMessage, tp) == expected);
}

TEST_CASE("LogFormat: logType, firstMessage, secondMessage, timePoint, frameCount", "[Log][LogFormat]") 
{
	constexpr auto lt = PonyEngine::Log::LogType::Info;
	auto tp = std::chrono::system_clock::from_time_t(1717430400);
	constexpr std::string_view firstMessage = "Foo";
	constexpr std::string_view secondMessage = "Bar";
	constexpr std::uint64_t frame = 42;
	std::string expected = std::format("[{}] [{:%F %R:%OS UTC} ({})] {} - {}\n", lt, tp, frame, firstMessage, secondMessage, frame);
	REQUIRE(PonyEngine::Log::LogFormat(lt, firstMessage, secondMessage, tp, frame) == expected);
}

TEST_CASE("LogFormat: logType, timePoint, stacktrace", "[Log][LogFormat]")
{
	constexpr auto lt = PonyEngine::Log::LogType::Error;
	const auto tp = std::chrono::system_clock::from_time_t(1717430400);
	const std::stacktrace stacktrace = std::stacktrace::current();
	std::string expected = std::format("[{}] [{:%F %R:%OS UTC}]\n{}\n", lt, tp, stacktrace);
	REQUIRE(PonyEngine::Log::LogFormat(lt, tp, stacktrace) == expected);
}

TEST_CASE("LogFormat: logType, timePoint, frameCount, stacktrace", "[Log][LogFormat]")
{
	constexpr auto lt = PonyEngine::Log::LogType::Error;
	const auto tp = std::chrono::system_clock::from_time_t(1717430400);
	constexpr std::uint64_t frame = 42;
	const std::stacktrace stacktrace = std::stacktrace::current();
	std::string expected = std::format("[{}] [{:%F %R:%OS UTC} ({})]\n{}\n", lt, tp, frame, stacktrace);
	REQUIRE(PonyEngine::Log::LogFormat(lt, tp, frame, stacktrace) == expected);
}

TEST_CASE("LogFormat: logType, message, timePoint, stacktrace", "[Log][LogFormat]")
{
	constexpr auto lt = PonyEngine::Log::LogType::Error;
	const auto tp = std::chrono::system_clock::from_time_t(1717430400);
	constexpr std::string_view message = "Stacktrace test";
	const std::stacktrace stacktrace = std::stacktrace::current();
	std::string expected = std::format("[{}] [{:%F %R:%OS UTC}] {}\n{}\n", lt, tp, message, stacktrace);
	REQUIRE(PonyEngine::Log::LogFormat(lt, message, tp, stacktrace) == expected);
}

TEST_CASE("LogFormat: logType, message, timePoint, frameCount, stacktrace", "[Log][LogFormat]")
{
	constexpr auto lt = PonyEngine::Log::LogType::Warning;
	const auto tp = std::chrono::system_clock::from_time_t(1717430400);
	constexpr std::string_view message = "Stacktrace with frame";
	constexpr std::uint64_t frame = 123;
	const std::stacktrace stacktrace = std::stacktrace::current();
	std::string expected = std::format("[{}] [{:%F %R:%OS UTC} ({})] {}\n{}\n", lt, tp, frame, message, stacktrace);
	REQUIRE(PonyEngine::Log::LogFormat(lt, message, tp, frame, stacktrace) == expected);
}

TEST_CASE("LogFormat: logType, firstMessage, secondMessage, timePoint, stacktrace", "[Log][LogFormat]")
{
	constexpr auto lt = PonyEngine::Log::LogType::Exception;
	const auto tp = std::chrono::system_clock::from_time_t(1717430400);
	constexpr std::string_view firstMessage = "First";
	constexpr std::string_view secondMessage = "Second";
	const std::stacktrace stacktrace = std::stacktrace::current();
	std::string expected = std::format("[{}] [{:%F %R:%OS UTC}] {} - {}\n{}\n", lt, tp, firstMessage, secondMessage, stacktrace);
	REQUIRE(PonyEngine::Log::LogFormat(lt, firstMessage, secondMessage, tp, stacktrace) == expected);
}

TEST_CASE("LogFormat: logType, firstMessage, secondMessage, timePoint, frameCount, stacktrace", "[Log][LogFormat]")
{
	constexpr auto lt = PonyEngine::Log::LogType::Debug;
	const auto tp = std::chrono::system_clock::from_time_t(1717430400);
	constexpr std::string_view firstMessage = "Alpha";
	constexpr std::string_view secondMessage = "Beta";
	constexpr std::uint64_t frame = 456;
	const std::stacktrace stacktrace = std::stacktrace::current();
	std::string expected = std::format("[{}] [{:%F %R:%OS UTC} ({})] {} - {}\n{}\n", lt, tp, frame, firstMessage, secondMessage, stacktrace);
	REQUIRE(PonyEngine::Log::LogFormat(lt, firstMessage, secondMessage, tp, frame, stacktrace) == expected);
}
