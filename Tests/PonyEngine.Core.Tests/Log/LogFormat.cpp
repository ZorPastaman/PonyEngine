/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include <chrono>
#include <cstdint>
#include <string>
#include <string_view>

#include <catch2/catch_test_macros.hpp>

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
