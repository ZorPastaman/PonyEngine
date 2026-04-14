/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:Reduction;

import std;

import :ComparisonFunc;

export namespace PonyEngine::RenderDevice
{
	/// @brief Standard reduction.
	struct StandardReduction final
	{
	};

	/// @brief Comparison reduction.
	struct ComparisonReduction final
	{
		ComparisonFunc func; ///< Comparison function.
	};

	/// @brief Minimum reduction.
	struct MinimumReduction final
	{
	};

	/// @brief Maximum reduction.
	struct MaximumReduction final
	{
	};

	using Reduction = std::variant<StandardReduction, ComparisonReduction, MinimumReduction, MaximumReduction>; ///< Reduction.
}
