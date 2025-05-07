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

export module PonyEngine.Render:BlendFactor;

import <algorithm>;
import <array>;
import <cstddef>;
import <cstdint>;
import <ostream>;
import <string_view>;

namespace PonyEngine::Render
{
	/// @brief Blend factor names.
	constexpr std::array<std::string_view, 12> BlendFactorNames
	{
		"Zero",
		"One",
		"ColorSource",
		"ColorSourceInverse",
		"AlphaSource",
		"AlphaSourceInverse",
		"AlphaSourceSaturate",
		"ColorDestination",
		"ColorDestinationInverse",
		"AlphaDestination",
		"AlphaDestinationInverse",
		"Unknown"
	};
}

export namespace PonyEngine::Render
{
	/// @brief Blend factor.
	enum class BlendFactor : std::uint8_t
	{
		Zero,
		One,
		ColorSource,
		ColorSourceInverse,
		AlphaSource,
		AlphaSourceInverse,
		AlphaSourceSaturate,
		ColorDestination,
		ColorDestinationInverse,
		AlphaDestination,
		AlphaDestinationInverse,
	};

	ENUM_VALUE_FEATURES(BlendFactor, BlendFactorNames)
}
