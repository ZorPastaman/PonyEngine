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

import PonyEngine.Utility;

TEST_CASE("Arithmetic concept", "[Utility][Concepts]")
{
	STATIC_REQUIRE(PonyEngine::Utility::Arithmetic<std::int32_t>);
	STATIC_REQUIRE(PonyEngine::Utility::Arithmetic<std::uint64_t>);
	STATIC_REQUIRE(PonyEngine::Utility::Arithmetic<float>);
	STATIC_REQUIRE_FALSE(PonyEngine::Utility::Arithmetic<void*>);
}

TEST_CASE("Signed concept", "[Utility][Concepts]")
{
	STATIC_REQUIRE(PonyEngine::Utility::Signed<std::int16_t>);
	STATIC_REQUIRE(PonyEngine::Utility::Signed<float>);
	STATIC_REQUIRE_FALSE(PonyEngine::Utility::Signed<std::uint32_t>);
	STATIC_REQUIRE_FALSE(PonyEngine::Utility::Signed<std::uint8_t>);
}

TEST_CASE("Unsigned concept", "[Utility][Concepts]")
{
	STATIC_REQUIRE_FALSE(PonyEngine::Utility::Unsigned<std::int16_t>);
	STATIC_REQUIRE_FALSE(PonyEngine::Utility::Unsigned<float>);
	STATIC_REQUIRE(PonyEngine::Utility::Unsigned<std::uint32_t>);
	STATIC_REQUIRE(PonyEngine::Utility::Unsigned<std::uint8_t>);
}
