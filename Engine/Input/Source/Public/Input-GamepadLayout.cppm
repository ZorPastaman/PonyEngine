/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Type/Enum.h"

export module PonyEngine.Input:GamepadLayout;

import std;

import :Axis;

namespace PonyEngine::Input
{
	/// @brief Gamepad layout names.
	constexpr std::array<std::string_view, 25> GamepadLayoutNames
	{
		// Sticks
		"Left Stick X",
		"Left Stick Y",
		"Left Stick Button",
		"Right Stick X",
		"Right Stick Y",
		"Right Stick Button",
		// D-Pad
		"D-Pad Up",
		"D-Pad Down",
		"D-Pad Right",
		"D-Pad Left",
		// Front buttons
		"Button North",
		"Button South",
		"Button East",
		"Button West",
		// Back buttons
		"Left Bumper",
		"Right Bumper",
		"Left Trigger",
		"Right Trigger",
		// System buttons
		"Button Start",
		"Button Select",
		"Button Home",
		// Paddles
		"Paddle0",
		"Paddle1",
		"Paddle2",
		"Paddle3"
	};
}

export namespace PonyEngine::Input
{
	/// @brief Gamepad layout.
	enum class GamepadLayout : AxisIdType
	{
		// Sticks
		LeftStickX,
		LeftStickY,
		LeftStickButton,
		RightStickX,
		RightStickY,
		RightStickButton,
		// D-Pad
		DPadUp,
		DPadDown,
		DPadRight,
		DPadLeft,
		// Front buttons
		ButtonNorth,
		ButtonSouth,
		ButtonEast,
		ButtonWest,
		// Back buttons
		LeftBumper,
		RightBumper,
		LeftTrigger,
		RightTrigger,
		// System buttons
		ButtonStart,
		ButtonSelect,
		ButtonHome,
		// Paddles
		Paddle0,
		Paddle1,
		Paddle2,
		Paddle3
	};

	ENUM_VALUE_FEATURES(GamepadLayout, GamepadLayoutNames)
}

export
{
	ENUM_VALUE_FORMATTER(PonyEngine::Input, GamepadLayout)
}
