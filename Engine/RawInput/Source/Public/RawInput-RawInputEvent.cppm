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

import :AxisId;
import :InputEventType;

export namespace PonyEngine::Input
{
	/// @brief Raw input event.
	struct RawInputEvent final
	{
		std::span<const AxisId> axes; ///< Axes.
		std::span<const float> values; ///< Values.
		InputEventType eventType = InputEventType::State; ///< Event type.

		/// @brief Time point when the event was created.
		/// @remark Different devices use different clocks. So, it can be used only to approximately compare what input was earlier or something like that.
		std::chrono::time_point<std::chrono::steady_clock> timePoint;
		std::optional<Math::Vector2<std::int32_t>> cursorPosition; ///< Cursor position in screen coordinates; std::nullopt if not applicable.
	};
}
