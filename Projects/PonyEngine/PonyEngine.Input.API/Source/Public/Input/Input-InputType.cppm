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

export module PonyEngine.Input:InputType;

import <algorithm>;
import <array>;
import <cstddef>;
import <cstdint>;
import <ostream>;
import <string_view>;

namespace PonyEngine::Input
{
	/// @brief Input type names.
	constexpr std::array<std::string_view, 3> InputTypeNames
	{
		"State",
		"Delta",
		"Unknown"
	};
}

export namespace PonyEngine::Input 
{
	/// @brief Input type.
	enum class InputType : std::uint8_t
	{
		State, ///< Input state change. It's kept across ticks and can be only changed.
		Delta ///< Input delta. It's zeroed every tick and can only be added.
	};

	ENUM_VALUE_FEATURES(InputType, InputTypeNames)
}
