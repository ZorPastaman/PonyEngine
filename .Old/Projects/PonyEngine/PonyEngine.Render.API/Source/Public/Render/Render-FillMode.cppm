/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Utility/Enum.h"

export module PonyEngine.Render:FillMode;

import <algorithm>;
import <array>;
import <cstddef>;
import <cstdint>;
import <ostream>;
import <string_view>;

namespace PonyEngine::Render
{
	/// @brief Fill mode names.
	constexpr std::array<std::string_view, 3> FillModeNames
	{
		"Solid",
		"Wireframe",
		"Unknown"
	};
}

export namespace PonyEngine::Render
{
	/// @brief Fill mode.
	enum class FillMode : std::uint8_t
	{
		Solid,
		Wireframe
	};

	ENUM_VALUE_FEATURES(FillMode, FillModeNames)
}
