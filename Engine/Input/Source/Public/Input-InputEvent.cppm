/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Input:InputEvent;

import std;

import PonyEngine.Math;

import :ActionId;
import :DeviceHandle;
import :InputEventType;

export namespace PonyEngine::Input
{
	/// @brief Input event.
	struct InputEvent final
	{
		ActionId actionId; ///< Action ID.
		std::span<const float> values; ///< Values.
		InputEventType eventType = InputEventType::State; ///< Event type.

		/// @brief Time point when the event was created.
		/// @remark Input devices may use different clocks. So, don't rely on this time point for time measurements between different devices or the engine time.
		std::chrono::time_point<std::chrono::steady_clock> timePoint;
		std::optional<Math::Vector2<std::int32_t>> cursorPosition; ///< Cursor position in screen coordinates; std::nullopt if not applicable.
	};
}
