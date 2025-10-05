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

import PonyEngine.Text;

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

TEST_CASE("SafeFormat returns formatted string on success", "[Text][Format]")
{
	std::string result = PonyEngine::Text::FormatSafe("Hello, {}!", "World");
	REQUIRE(result == "Hello, World!");
}

TEST_CASE("SafeFormat returns exception message on format error", "[Text][Format]")
{
	std::string result = PonyEngine::Text::FormatSafe("Value: {}", ThrowingType{});
	REQUIRE(result.find("Custom formatter error") != std::string::npos);
}

TEST_CASE("SafeFormat with custom ExceptionHandler is called on error", "[Text][Format]")
{
	TestExceptionHandler handler;
	std::string result = PonyEngine::Text::FormatSafe(handler, "Value: {}", ThrowingType{});
	REQUIRE(handler.wasCalled);
	REQUIRE(!handler.message.empty());
	REQUIRE(result == handler.message);
}

TEST_CASE("SafeFormat with default-constructible ExceptionHandler", "[Text][Format]")
{
	std::string result = PonyEngine::Text::FormatSafe<TestExceptionHandler>("Value: {}", ThrowingType{});
	REQUIRE(result.find("Custom formatter error") != std::string::npos);
}
