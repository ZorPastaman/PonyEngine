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

TEST_CASE("IsGreater", "[Type][Common]")
{
	STATIC_REQUIRE(PonyEngine::Type::IsGreater<double, float>);
	STATIC_REQUIRE_FALSE(PonyEngine::Type::IsGreater<float, double>);
	STATIC_REQUIRE_FALSE(PonyEngine::Type::IsGreater<float, std::int64_t>);
	STATIC_REQUIRE(PonyEngine::Type::IsGreater<std::int64_t, float>);
	STATIC_REQUIRE(PonyEngine::Type::IsGreater<std::uint16_t, std::int8_t>);
	STATIC_REQUIRE_FALSE(PonyEngine::Type::IsGreater<std::int8_t, std::uint16_t>);
}
TEST_CASE("IsLess", "[Type][Common]")
{
	STATIC_REQUIRE_FALSE(PonyEngine::Type::IsLess<double, float>);
	STATIC_REQUIRE(PonyEngine::Type::IsLess<float, double>);
	STATIC_REQUIRE(PonyEngine::Type::IsLess<float, std::int64_t>);
	STATIC_REQUIRE_FALSE(PonyEngine::Type::IsLess<std::int64_t, float>);
	STATIC_REQUIRE_FALSE(PonyEngine::Type::IsLess<std::uint16_t, std::int8_t>);
	STATIC_REQUIRE(PonyEngine::Type::IsLess<std::int8_t, std::uint16_t>);
}

TEST_CASE("IsEqual", "[Type][Common]")
{
	STATIC_REQUIRE(PonyEngine::Type::IsEqual<std::int64_t, std::int64_t>);
	STATIC_REQUIRE(PonyEngine::Type::IsEqual<std::int64_t, std::uint64_t>);
	STATIC_REQUIRE(PonyEngine::Type::IsEqual<std::int32_t, float>);
	STATIC_REQUIRE_FALSE(PonyEngine::Type::IsEqual<std::int16_t, double>);
	STATIC_REQUIRE_FALSE(PonyEngine::Type::IsEqual<float, double>);
}

TEST_CASE("FloatingBySize and ComputationalFor", "[Type][Common]")
{
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Type::FloatingBySize<float>, float>);
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Type::FloatingBySize<double>, double>);
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Type::FloatingBySize<std::int16_t>, float>);
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Type::FloatingBySize<std::uint32_t>, float>);
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Type::FloatingBySize<std::int64_t>, double>);
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Type::FloatingBySize<std::uint64_t>, double>);
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Type::FloatingBySize<std::pair<std::int64_t, std::int8_t>>, long double>);
	STATIC_REQUIRE(std::is_same_v<PonyEngine::Type::FloatingBySize<std::pair<std::uint64_t, std::uint8_t>>, long double>);
}
