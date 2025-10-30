/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Input:AxisBinding;

import std;

import :Axis;

export namespace PonyEngine::Input
{
	/// @brief Axis binding.
	struct AxisBinding final
	{
		Axis axis; ///< Axis.
		float scale = 1.f; ///< Scale.
		std::uint8_t actionAxisIndex = 0u; ///< Action axis index.
	};
}
