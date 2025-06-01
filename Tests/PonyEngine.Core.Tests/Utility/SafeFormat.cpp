/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: cybercode.smith@pm.me                    *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include <format>
#include <stdexcept>
#include <string>

#include <catch2/catch_test_macros.hpp>

import PonyEngine.Utility;

struct TestExceptionHandler
{
	bool wasCalled = false;
	std::string message;

	void operator()(const std::exception& e) noexcept
	{
		wasCalled = true;
		message = e.what();
	}
};

struct ThrowingType {};

template<>
struct std::formatter<ThrowingType, char>
{
	static constexpr auto parse(std::format_parse_context& ctx)
	{
		return ctx.begin();
	}

	static auto format(const ThrowingType&, std::format_context& ctx)
	{
		throw std::runtime_error("Custom formatter error");
		return ctx.out();
	}
};

TEST_CASE("SafeFormat returns formatted string on success", "[Utility][SafeFormat]")
{
	std::string result = PonyEngine::Utility::SafeFormat("Hello, {}!", "World");
	REQUIRE(result == "Hello, World!");
}

TEST_CASE("SafeFormat returns exception message on format error", "[Utility][SafeFormat]")
{
	std::string result = PonyEngine::Utility::SafeFormat("Value: {}", ThrowingType{});
	REQUIRE(result.find("Custom formatter error") != std::string::npos);
}

TEST_CASE("SafeFormat with custom ExceptionHandler is called on error", "[Utility][SafeFormat]")
{
	TestExceptionHandler handler;
	std::string result = PonyEngine::Utility::SafeFormat(handler, "Value: {}", ThrowingType{});
	REQUIRE(handler.wasCalled);
	REQUIRE(!handler.message.empty());
	REQUIRE(result == handler.message);
}

TEST_CASE("SafeFormat with default-constructible ExceptionHandler", "[Utility][SafeFormat]")
{
	std::string result = PonyEngine::Utility::SafeFormat<TestExceptionHandler>("Value: {}", ThrowingType{});
	REQUIRE(result.find("Custom formatter error") != std::string::npos);
}
