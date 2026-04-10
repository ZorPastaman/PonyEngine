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

TEST_CASE("MouseDevice static data", "[RawInput][Mouse]")
{
	STATIC_REQUIRE(PonyEngine::RawInput::MouseDevice::GenericType == "Mouse");
}

TEST_CASE("MouseLayout static data", "[RawInput][Mouse]")
{
	STATIC_REQUIRE(PonyEngine::RawInput::MouseLayout::Layout == "Mouse");

	STATIC_REQUIRE(PonyEngine::RawInput::MouseLayout::Button == "Button");
	STATIC_REQUIRE(PonyEngine::RawInput::MouseLayout::ButtonPath == "Mouse/Button");
	STATIC_REQUIRE(PonyEngine::RawInput::MouseLayout::Button1Path == "Mouse/Button/1");
	STATIC_REQUIRE(PonyEngine::RawInput::MouseLayout::Button2Path == "Mouse/Button/2");
	STATIC_REQUIRE(PonyEngine::RawInput::MouseLayout::Button3Path == "Mouse/Button/3");
	STATIC_REQUIRE(PonyEngine::RawInput::MouseLayout::Button4Path == "Mouse/Button/4");
	STATIC_REQUIRE(PonyEngine::RawInput::MouseLayout::Button5Path == "Mouse/Button/5");
	STATIC_REQUIRE(PonyEngine::RawInput::MouseLayout::ButtonLeftPath == "Mouse/Button/1");
	STATIC_REQUIRE(PonyEngine::RawInput::MouseLayout::ButtonRightPath == "Mouse/Button/2");
	STATIC_REQUIRE(PonyEngine::RawInput::MouseLayout::ButtonMiddlePath == "Mouse/Button/3");
	STATIC_REQUIRE(PonyEngine::RawInput::MouseLayout::ButtonX1Path == "Mouse/Button/4");
	STATIC_REQUIRE(PonyEngine::RawInput::MouseLayout::ButtonX2Path == "Mouse/Button/5");

	STATIC_REQUIRE(PonyEngine::RawInput::MouseLayout::Wheel == "Wheel");
	STATIC_REQUIRE(PonyEngine::RawInput::MouseLayout::WheelPath == "Mouse/Wheel");
	STATIC_REQUIRE(PonyEngine::RawInput::MouseLayout::WheelHorizontalPath == "Mouse/Wheel/Horizontal");
	STATIC_REQUIRE(PonyEngine::RawInput::MouseLayout::WheelVerticalPath == "Mouse/Wheel/Vertical");

	STATIC_REQUIRE(PonyEngine::RawInput::MouseLayout::Axis == "Axis");
	STATIC_REQUIRE(PonyEngine::RawInput::MouseLayout::AxisPath == "Mouse/Axis");
	STATIC_REQUIRE(PonyEngine::RawInput::MouseLayout::AxisXPath == "Mouse/Axis/X");
	STATIC_REQUIRE(PonyEngine::RawInput::MouseLayout::AxisYPath == "Mouse/Axis/Y");
}
