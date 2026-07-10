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

TEST_CASE("GamepadDevice static data", "[RawInput][Gamepad]")
{
	STATIC_REQUIRE(PonyEngine::RawInput::GamepadDevice::GenericType == "Gamepad");

	STATIC_REQUIRE(PonyEngine::RawInput::GamepadDevice::Xbox == "Xbox");
	STATIC_REQUIRE(PonyEngine::RawInput::GamepadDevice::XboxType == "Gamepad/Xbox");

	STATIC_REQUIRE(PonyEngine::RawInput::GamepadDevice::PlayStation == "PlayStation");
	STATIC_REQUIRE(PonyEngine::RawInput::GamepadDevice::PlayStationType == "Gamepad/PlayStation");
}

TEST_CASE("GamepadLayout static data", "[RawInput][Gamepad]")
{
	STATIC_REQUIRE(PonyEngine::RawInput::GamepadLayout::Layout == "Gamepad");

	STATIC_REQUIRE(PonyEngine::RawInput::GamepadLayout::DPad == "D-Pad");
	STATIC_REQUIRE(PonyEngine::RawInput::GamepadLayout::DPadPath == "Gamepad/D-Pad");
	STATIC_REQUIRE(PonyEngine::RawInput::GamepadLayout::DPadLeftPath == "Gamepad/D-Pad/Left");
	STATIC_REQUIRE(PonyEngine::RawInput::GamepadLayout::DPadRightPath == "Gamepad/D-Pad/Right");
	STATIC_REQUIRE(PonyEngine::RawInput::GamepadLayout::DPadDownPath == "Gamepad/D-Pad/Down");
	STATIC_REQUIRE(PonyEngine::RawInput::GamepadLayout::DPadUpPath == "Gamepad/D-Pad/Up");

	STATIC_REQUIRE(PonyEngine::RawInput::GamepadLayout::FaceButton == "FaceButton");
	STATIC_REQUIRE(PonyEngine::RawInput::GamepadLayout::FaceButtonPath == "Gamepad/FaceButton");
	STATIC_REQUIRE(PonyEngine::RawInput::GamepadLayout::FaceButtonLeftPath == "Gamepad/FaceButton/Left");
	STATIC_REQUIRE(PonyEngine::RawInput::GamepadLayout::FaceButtonRightPath == "Gamepad/FaceButton/Right");
	STATIC_REQUIRE(PonyEngine::RawInput::GamepadLayout::FaceButtonDownPath == "Gamepad/FaceButton/Down");
	STATIC_REQUIRE(PonyEngine::RawInput::GamepadLayout::FaceButtonUpPath == "Gamepad/FaceButton/Up");

	STATIC_REQUIRE(PonyEngine::RawInput::GamepadLayout::BackButton == "BackButton");
	STATIC_REQUIRE(PonyEngine::RawInput::GamepadLayout::BackButtonPath == "Gamepad/BackButton");
	STATIC_REQUIRE(PonyEngine::RawInput::GamepadLayout::BackButtonLeftPath == "Gamepad/BackButton/Left");
	STATIC_REQUIRE(PonyEngine::RawInput::GamepadLayout::BackButtonRightPath == "Gamepad/BackButton/Right");

	STATIC_REQUIRE(PonyEngine::RawInput::GamepadLayout::Trigger == "Trigger");
	STATIC_REQUIRE(PonyEngine::RawInput::GamepadLayout::TriggerPath == "Gamepad/Trigger");
	STATIC_REQUIRE(PonyEngine::RawInput::GamepadLayout::TriggerLeftPath == "Gamepad/Trigger/Left");
	STATIC_REQUIRE(PonyEngine::RawInput::GamepadLayout::TriggerRightPath == "Gamepad/Trigger/Right");

	STATIC_REQUIRE(PonyEngine::RawInput::GamepadLayout::LeftStick == "LeftStick");
	STATIC_REQUIRE(PonyEngine::RawInput::GamepadLayout::LeftStickPath == "Gamepad/LeftStick");
	STATIC_REQUIRE(PonyEngine::RawInput::GamepadLayout::LeftStickHorizontalPath == "Gamepad/LeftStick/Horizontal");
	STATIC_REQUIRE(PonyEngine::RawInput::GamepadLayout::LeftStickVerticalPath == "Gamepad/LeftStick/Vertical");
	STATIC_REQUIRE(PonyEngine::RawInput::GamepadLayout::LeftStickButtonPath == "Gamepad/LeftStick/Button");

	STATIC_REQUIRE(PonyEngine::RawInput::GamepadLayout::RightStick == "RightStick");
	STATIC_REQUIRE(PonyEngine::RawInput::GamepadLayout::RightStickPath == "Gamepad/RightStick");
	STATIC_REQUIRE(PonyEngine::RawInput::GamepadLayout::RightStickHorizontalPath == "Gamepad/RightStick/Horizontal");
	STATIC_REQUIRE(PonyEngine::RawInput::GamepadLayout::RightStickVerticalPath == "Gamepad/RightStick/Vertical");
	STATIC_REQUIRE(PonyEngine::RawInput::GamepadLayout::RightStickButtonPath == "Gamepad/RightStick/Button");

	STATIC_REQUIRE(PonyEngine::RawInput::GamepadLayout::System == "System");
	STATIC_REQUIRE(PonyEngine::RawInput::GamepadLayout::SystemPath == "Gamepad/System");
	STATIC_REQUIRE(PonyEngine::RawInput::GamepadLayout::SystemMenuPath == "Gamepad/System/Menu");
	STATIC_REQUIRE(PonyEngine::RawInput::GamepadLayout::SystemSelectPath == "Gamepad/System/Select");
	STATIC_REQUIRE(PonyEngine::RawInput::GamepadLayout::SystemGuidePath == "Gamepad/System/Guide");
}
