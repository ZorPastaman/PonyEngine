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

export module PonyEngine.Render:ThreadGroupCountsMode;

import <algorithm>;
import <array>;
import <cstddef>;
import <cstdint>;
import <ostream>;
import <string_view>;

namespace PonyEngine::Render
{
	/// @brief Thread group counts names.
	constexpr std::array<std::string_view, 6> ThreadGroupCountsModeNames
	{
		"SetMesh",
		"SetPipelineState",
		"Multiply",
		"DivideMeshByPipelineState",
		"DividePipelineStateByMesh",
		"Unknown"
	};
}

export namespace PonyEngine::Render
{
	/// @brief Thread group counts calculation mode.
	enum class ThreadGroupCountsMode : std::uint8_t
	{
		/// @brief Take mesh thread group counts. Ignore pipeline state thread group counts.
		SetMesh,
		/// @brief Take pipeline state thread group counts. Ignore mesh thread group counts.
		SetPipelineState,
		/// @brief Multiplies mesh thread group counts by pipeline state thread group counts.
		/// Each axis is multiplied independently.
		Multiply,
		/// @brief Divide mesh thread group counts by pipeline state thread group counts.
		/// Each axis is divided independently. If a pipeline state thread group count is zero, the result is zero.
		/// The result is ceiled.
		DivideMeshByPipelineState,
		/// @brief Divide pipeline state thread group counts by mesh thread group counts.
		/// Each axis is divided independently. If a mesh thread group count is zero, the result is zero.
		/// The result is ceiled.
		DividePipelineStateByMesh
	};

	ENUM_VALUE_FEATURES(ThreadGroupCountsMode, ThreadGroupCountsModeNames)
}
