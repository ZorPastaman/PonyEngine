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

TEST_CASE("Layout static data", "[RawInput][Layout]")
{
	STATIC_REQUIRE(PonyEngine::RawInput::Layout::PathSeparator == '/');

	STATIC_REQUIRE(PonyEngine::RawInput::Layout::Middle == "Middle");
	STATIC_REQUIRE(PonyEngine::RawInput::Layout::Left == "Left");
	STATIC_REQUIRE(PonyEngine::RawInput::Layout::Right == "Right");
	STATIC_REQUIRE(PonyEngine::RawInput::Layout::Down == "Down");
	STATIC_REQUIRE(PonyEngine::RawInput::Layout::Up == "Up");
	STATIC_REQUIRE(PonyEngine::RawInput::Layout::Horizontal == "Horizontal");
	STATIC_REQUIRE(PonyEngine::RawInput::Layout::Vertical == "Vertical");

	STATIC_REQUIRE(PonyEngine::RawInput::Layout::Axis == "Axis");
	STATIC_REQUIRE(PonyEngine::RawInput::Layout::Arrow == "Arrow");
	STATIC_REQUIRE(PonyEngine::RawInput::Layout::Button == "Button");

	STATIC_REQUIRE(PonyEngine::RawInput::Layout::System == "System");
	STATIC_REQUIRE(PonyEngine::RawInput::Layout::Main == "Main");
	STATIC_REQUIRE(PonyEngine::RawInput::Layout::Menu == "Menu");
	STATIC_REQUIRE(PonyEngine::RawInput::Layout::Select == "Select");
	STATIC_REQUIRE(PonyEngine::RawInput::Layout::Guide == "Guide");
}
