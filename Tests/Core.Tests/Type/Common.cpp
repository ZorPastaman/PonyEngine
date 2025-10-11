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

import PonyEngine.Type;

TEST_CASE("Arithmetic concept", "[Type][Common]")
{
	STATIC_REQUIRE(PonyEngine::Type::Arithmetic<std::int32_t>);
	STATIC_REQUIRE(PonyEngine::Type::Arithmetic<std::uint64_t>);
	STATIC_REQUIRE(PonyEngine::Type::Arithmetic<float>);
	STATIC_REQUIRE_FALSE(PonyEngine::Type::Arithmetic<void*>);
}

TEST_CASE("Signed concept", "[Type][Common]")
{
	STATIC_REQUIRE(PonyEngine::Type::Signed<std::int16_t>);
	STATIC_REQUIRE(PonyEngine::Type::Signed<float>);
	STATIC_REQUIRE_FALSE(PonyEngine::Type::Signed<std::uint32_t>);
	STATIC_REQUIRE_FALSE(PonyEngine::Type::Signed<std::uint8_t>);
}

TEST_CASE("Unsigned concept", "[Type][Common]")
{
	STATIC_REQUIRE_FALSE(PonyEngine::Type::Unsigned<std::int16_t>);
	STATIC_REQUIRE_FALSE(PonyEngine::Type::Unsigned<float>);
	STATIC_REQUIRE(PonyEngine::Type::Unsigned<std::uint32_t>);
	STATIC_REQUIRE(PonyEngine::Type::Unsigned<std::uint8_t>);
}
