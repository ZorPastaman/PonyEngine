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

export module PonyEngine.Render:StencilOperation;

import <algorithm>;
import <array>;
import <cstddef>;
import <cstdint>;
import <ostream>;
import <string_view>;

namespace PonyEngine::Render
{
	/// @brief Stencil operation names.
	constexpr std::array<std::string_view, 8> StencilOperationNames
	{
		"Keep",
		"Zero",
		"Replace",
		"Invert",
		"Increment",
		"Decrement",
		"IncrementSaturated",
		"DecrementSaturated"
		"Unknown"
	};
}

export namespace PonyEngine::Render
{
	/// @brief Stencil operation.
	enum class StencilOperation : std::uint8_t
	{
		Keep,
		Zero,
		Replace,
		Invert,
		Increment,
		Decrement,
		IncrementSaturated,
		DecrementSaturated
	};

	ENUM_VALUE_FEATURES(StencilOperation, StencilOperationNames)
}
