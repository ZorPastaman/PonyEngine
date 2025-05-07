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

export module PonyEngine.Render:BlendOperation;

import <algorithm>;
import <array>;
import <cstddef>;
import <cstdint>;
import <ostream>;
import <string_view>;

namespace PonyEngine::Render
{
	/// @brief Blend operation names.
	constexpr std::array<std::string_view, 6> BlendOperationNames
	{
		"Add",
		"Subtract",
		"SubtractReverse",
		"Min",
		"Max",
		"Unknown"
	};
}

export namespace PonyEngine::Render
{
	/// @brief Blend operation.
	enum class BlendOperation : std::uint8_t
	{
		Add,
		Subtract,
		SubtractReverse,
		Min,
		Max
	};

	ENUM_VALUE_FEATURES(BlendOperation, BlendOperationNames)
}
