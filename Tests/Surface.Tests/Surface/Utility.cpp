/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include <catch2/catch_test_macros.hpp>

import PonyEngine.Math;
import PonyEngine.Surface;

TEST_CASE("Absolute to relative", "[Surface][Utility]")
{
	constexpr auto point = PonyEngine::Math::Vector2<float>(0.333333f, 0.666667f);
	constexpr auto resolution = PonyEngine::Math::Vector2<std::int32_t>(100, 100);
	constexpr PonyEngine::Math::Vector2<std::int32_t> result = PonyEngine::Surface::RelativeToAbsolute(point, resolution);
	STATIC_REQUIRE(PonyEngine::Math::Vector2<std::int32_t>(33, 67) == result);
}

TEST_CASE("Relative to absolute", "[Surface][Utility]")
{
	constexpr auto point = PonyEngine::Math::Vector2<std::int32_t>(33, 67);
	constexpr auto resolution = PonyEngine::Math::Vector2<std::int32_t>(100, 100);
	constexpr PonyEngine::Math::Vector2<float> result = PonyEngine::Surface::AbsoluteToRelative(point, resolution);
	STATIC_REQUIRE(PonyEngine::Math::AreAlmostEqual(PonyEngine::Math::Vector2<float>(0.33f, 0.67f), result));
}
