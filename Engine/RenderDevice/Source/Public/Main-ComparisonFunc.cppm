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

export module PonyEngine.RenderDevice:ComparisonFunc;

import std;

export namespace PonyEngine::RenderDevice
{
	/// @brief Comparison function.
	enum class ComparisonFunc : std::uint8_t
	{
		NoComparison,
		Never,
		Always,
		Equal,
		NotEqual,
		Less,
		LessOrEqual,
		Greater,
		GreaterOrEqual
	};
}

namespace PonyEngine::RenderDevice
{
	/// @brief Comparison function names.
	constexpr std::array<std::string_view, 9> ComparisonFuncNames
	{
		"NoComparison",
		"Never",
		"Always",
		"Equal",
		"NotEqual",
		"Less",
		"LessOrEqual",
		"Greater",
		"GreaterOrEqual"
	};
}

export
{
	PONY_ENUM_VALUE_FORMATTER(PonyEngine::RenderDevice::ComparisonFunc, PonyEngine::RenderDevice::ComparisonFuncNames)
}
