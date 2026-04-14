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

import PonyEngine.Math;
import PonyEngine.Time;

TEST_CASE("ToSeconds", "[Time][Utility]")
{
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Time::ToSeconds(std::chrono::duration<double>(8.4)), 8.4));
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Time::ToSeconds(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::duration<double>(8.4))), 8.4));
}

TEST_CASE("ToDuration", "[Time][Utility]")
{
	STATIC_REQUIRE(PonyEngine::Time::ToDuration<std::chrono::duration<float>>(8.4f) == std::chrono::duration<float>(8.4f));
	STATIC_REQUIRE(PonyEngine::Time::ToDuration<std::chrono::nanoseconds>(8.4f) == std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::duration<float>(8.4f)));
}
