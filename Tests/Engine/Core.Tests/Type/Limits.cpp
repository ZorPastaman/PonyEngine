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

TEST_CASE("Digits10", "[Type][Limits]")
{
	STATIC_REQUIRE(PonyEngine::Type::Digits10(std::uint8_t{23}) == 2);
	STATIC_REQUIRE(PonyEngine::Type::Digits10(std::int16_t{-4892}) == 4);
	STATIC_REQUIRE(PonyEngine::Type::Digits10(0) == 1);
	STATIC_REQUIRE(PonyEngine::Type::Digits10(1649165132106549) == 16);
	STATIC_REQUIRE(PonyEngine::Type::Digits10(false) == 1);
}
