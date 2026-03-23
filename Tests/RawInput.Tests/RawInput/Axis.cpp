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

import PonyEngine.RawInput;

TEST_CASE("Axis static data", "[RawInput][Axis]")
{
	STATIC_REQUIRE(PonyEngine::RawInput::Axis::PathSeparator == '/');
}

TEST_CASE("Axis constructor", "[RawInput][Axis]")
{
	const auto defaultAxis = PonyEngine::RawInput::Axis();
	REQUIRE(defaultAxis.Path() == "");
	REQUIRE(defaultAxis.Layout() == "");

	constexpr std::string_view gamepad = "Gamepad";
	const auto simpleAxis = PonyEngine::RawInput::Axis(gamepad);
	REQUIRE(simpleAxis.Path() == gamepad);
	REQUIRE(simpleAxis.Layout() == gamepad);

	const std::string bestGamepad = std::format("{}/Best", gamepad);
	const auto axis = PonyEngine::RawInput::Axis(bestGamepad);
	REQUIRE(axis.Path() == bestGamepad);
	REQUIRE(axis.Layout() == gamepad);

	const std::string complexGamepad = std::format("{}//Best////Very", gamepad);
	const auto complexAxis = PonyEngine::RawInput::Axis(complexGamepad);
	REQUIRE(complexAxis.Path() == std::format("{}/Best/Very", gamepad));
	REQUIRE(complexAxis.Layout() == gamepad);

	const PonyEngine::RawInput::Axis copy = axis;
	REQUIRE(copy == axis);

	const PonyEngine::RawInput::Axis moved = std::move(axis);
	REQUIRE(copy == moved);
}

TEST_CASE("Axis append", "[RawInput][Axis]")
{
	constexpr std::string_view gamepad = "Gamepad";
	constexpr std::string_view best = "Best";
	constexpr std::string_view very = "Very";
	constexpr std::string_view mine = "Mine";

	auto axis = PonyEngine::RawInput::Axis();
	axis /= gamepad;
	axis /= PonyEngine::RawInput::Axis(best);
	const auto finalAxis = axis / PonyEngine::RawInput::Axis(very) / mine;
	REQUIRE(finalAxis.Path() == std::format("{}/{}/{}/{}", gamepad, best, very, mine));
	REQUIRE(finalAxis.Layout() == gamepad);
}

TEST_CASE("Axis equals", "[RawInput][Axis]")
{
	constexpr std::string_view gamepad = "Gamepad";
	constexpr std::string_view best = "Best";
	const auto axis = PonyEngine::RawInput::Axis(std::format("{}/{}", gamepad, best));
	REQUIRE(axis == PonyEngine::RawInput::Axis(std::format("{}/{}", gamepad, best)));
	REQUIRE(axis == std::format("{}/{}", gamepad, best));
}
