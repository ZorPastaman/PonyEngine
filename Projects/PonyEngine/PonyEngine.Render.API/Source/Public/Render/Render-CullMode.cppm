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

export module PonyEngine.Render:CullMode;

import <algorithm>;
import <array>;
import <cstddef>;
import <cstdint>;
import <ostream>;
import <string_view>;

namespace PonyEngine::Render
{
	/// @brief Cull mode names.
	constexpr std::array<std::string_view, 4> CullModeNames
	{
		"None",
		"Front",
		"Back",
		"Unknown"
	};
}

export namespace PonyEngine::Render
{
	/// @brief Cull mode.
	enum class CullMode : std::uint8_t
	{
		None,
		Front,
		Back
	};

	ENUM_VALUE_FEATURES(CullMode, CullModeNames)
}
