/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Utility/Enum.h"

export module PonyEngine.Surface:SurfacePositionMode;

import std;

namespace PonyEngine::Surface
{
	/// @brief Surface position mode names.
	constexpr std::array<std::string_view, 5> SurfacePositionModeNames
	{
		"LeftTopCorner",
		"RightTopCorner",
		"LeftBottomCorner",
		"RightBottomCorner",
		"Center"
	};
}

export namespace PonyEngine::Surface
{
	/// @brief Surface position mode. It defines how to treat a client position inside a display.
	enum class SurfacePositionMode : std::uint8_t
	{
		LeftTopCorner, ///< Use left-top corners of both a client and a display.
		RightTopCorner, ///< Use right-top corners of both a client and a display.
		LeftBottomCorner, ///< Use left-bottom corners of both a client and a display.
		RightBottomCorner, ///< Use right-bottom corners of both a client and a display.
		Center ///< Use centers of both a client and a display.
	};

	ENUM_VALUE_FEATURES(SurfacePositionMode, SurfacePositionModeNames)
}

export
{
	ENUM_VALUE_FORMATTER(PonyEngine::Surface, SurfacePositionMode)
}
