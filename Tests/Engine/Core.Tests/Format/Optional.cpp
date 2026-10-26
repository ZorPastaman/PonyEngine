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

import PonyEngine.Format;

TEST_CASE("Optional format", "[Format][Optional]")
{
	REQUIRE(std::format("{}", std::optional<int>()) == "std::nullopt");
	REQUIRE(std::format("{}", std::optional<int>(1)) == "1");
}
