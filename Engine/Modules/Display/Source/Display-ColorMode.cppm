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

export module PonyEngine.Display:ColorMode;

import std;

export namespace PonyEngine::Display
{
	/// @brief Color modes.
	enum class ColorMode : std::uint8_t
	{
		SDR,
		WCG,
		HDR
	};
}

namespace PonyEngine::Display
{
	/// @brief Color mode names.
	constexpr std::array<std::string_view, 3> ColorModeNames
	{
		"SDR",
		"WCG",
		"HDR"
	};
}

export
{
	PONY_ENUM_VALUE_FORMATTER(PonyEngine::Display::ColorMode, PonyEngine::Display::ColorModeNames)
}
