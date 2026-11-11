/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RawInput:RawInputEvent;

import std;

import PonyEngine.Math;

import :Axis;
import :InputType;

export namespace PonyEngine::RawInput
{
	/// @brief Raw input event.
	struct RawInputEvent final
	{
		std::span<const Axis> axes; ///< Axes.
		std::span<const float> values; ///< Values. It's synced by index with the @p axes.
		std::span<const InputType> inputTypes; ///< Input types. It's synced by index with the @p axes.
		std::chrono::time_point<std::chrono::steady_clock> timePoint; ///< Time point when the event was created.
	};
}
