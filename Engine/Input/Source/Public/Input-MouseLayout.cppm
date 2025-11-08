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

export module PonyEngine.Input:MouseLayout;

import std;

import :Axis;

namespace PonyEngine::Input
{
	/// @brief Mouse layout names.
	constexpr std::array<std::string_view, 41> MouseLayoutNames
	{
		// Axes
		"Axis X",
		"Axis Y",
		// Main buttons
		"Button Left",
		"Button Right",
		"Button Middle",
		// Scroll
		"Scroll Up",
		"Scroll Down",
		"Scroll Right",
		"Scroll Left",
		// Additional buttons
		"Button 0",
		"Button 1",
		"Button 2",
		"Button 3",
		"Button 4",
		"Button 5",
		"Button 6",
		"Button 7",
		"Button 8",
		"Button 9",
		"Button 10",
		"Button 11",
		"Button 12",
		"Button 13",
		"Button 14",
		"Button 15",
		"Button 16",
		"Button 17",
		"Button 18",
		"Button 19",
		"Button 20",
		"Button 21",
		"Button 22",
		"Button 23",
		"Button 24",
		"Button 25",
		"Button 26",
		"Button 27",
		"Button 28",
		"Button 29",
		"Button 30",
		"Button 31"
	};
}

export namespace PonyEngine::Input
{
	/// @brief Mouse layout.
	enum class MouseLayout : AxisIdType
	{
		// Axes
		AxisX,
		AxisY,
		// Main buttons
		ButtonLeft,
		ButtonRight,
		ButtonMiddle,
		// Scroll
		ScrollUp,
		ScrollDown,
		ScrollRight,
		ScrollLeft,
		// Additional buttons
		Button0,
		Button1,
		Button2,
		Button3,
		Button4,
		Button5,
		Button6,
		Button7,
		Button8,
		Button9,
		Button10,
		Button11,
		Button12,
		Button13,
		Button14,
		Button15,
		Button16,
		Button17,
		Button18,
		Button19,
		Button20,
		Button21,
		Button22,
		Button23,
		Button24,
		Button25,
		Button26,
		Button27,
		Button28,
		Button29,
		Button30,
		Button31
	};

	ENUM_VALUE_FEATURES(MouseLayout, MouseLayoutNames)
}

export
{
	ENUM_VALUE_FORMATTER(PonyEngine::Input, MouseLayout)
}
