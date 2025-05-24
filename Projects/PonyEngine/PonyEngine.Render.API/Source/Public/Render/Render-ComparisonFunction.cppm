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

export module PonyEngine.Render:ComparisonFunction;

import <algorithm>;
import <array>;
import <cstddef>;
import <cstdint>;
import <ostream>;
import <string_view>;

namespace PonyEngine::Render
{
	/// @brief Comparison function names.
	constexpr std::array<std::string_view, 9> ComparisonFunctionNames
	{
		"Never",
		"Always",
		"Equal",
		"NotEqual",
		"Less",
		"LessOrEqual",
		"Greater",
		"GreaterOrEqual",
		"Unknown"
	};
}

export namespace PonyEngine::Render
{
	/// @brief Comparison function.
	enum class ComparisonFunction : std::uint8_t
	{
		Never,
		Always,
		Equal,
		NotEqual,
		Less,
		LessOrEqual,
		Greater,
		GreaterOrEqual
	};

	ENUM_VALUE_FEATURES(ComparisonFunction, ComparisonFunctionNames)
}
