/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RawInput.Keyboard.Impl:KeyboardEvent;

import std;

import PonyEngine.Math;
import PonyEngine.RawInput;

export namespace PonyEngine::Input
{
	/// @brief Keyboard input event.
	struct KeyboardInputEvent final
	{
		AxisId axis; ///< Key axis.
		bool state; ///< Is the key pressed?
		std::optional<Math::Vector2<std::int32_t>> cursorPosition; ///< Cursor position.
	};

	/// @brief Keyboard connection event.
	struct KeyboardConnectionEvent final
	{
		bool connected; ///< Is the device connected?
	};

	/// @brief Keyboard event.
	struct KeyboardEvent final
	{
		std::variant<KeyboardInputEvent, KeyboardConnectionEvent> event; ///< Event.
		std::chrono::time_point<std::chrono::steady_clock> timePoint; ///< Event time.
	};
}
