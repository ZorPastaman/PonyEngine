/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RawInput.Mouse.Impl:MouseEvent;

import std;

import PonyEngine.Math;
import PonyEngine.RawInput;

export namespace PonyEngine::Input
{
	/// @brief Mouse button event.
	struct MouseButtonEvent final
	{
		AxisId axis; ///< Button axis.
		bool state; ///< Is the button pressed?
		std::optional<Math::Vector2<std::int32_t>> cursorPosition; ///< Cursor position.
	};

	/// @brief Mouse wheel event.
	struct MouseWheelEvent final
	{
		bool isVertical; ///< If it's @true, it's a vertical wheel; otherwise it's a horizontal wheel.
		float delta; ///< Wheel delta.
		std::optional<Math::Vector2<std::int32_t>> cursorPosition; ///< Cursor position.
	};

	/// @brief Mouse pointer event.
	struct MousePointerEvent final
	{
		bool hasX; ///< Has x component?
		bool hasY; ///< Has y component?
		Math::Vector2<float> delta; ///< Pointer delta.
		std::optional<Math::Vector2<std::int32_t>> cursorPosition; ///< Cursor position.
	};

	/// @brief Mouse connection event.
	struct MouseConnectionEvent final
	{
		bool isConnected; ///< Is a device connected?
	};

	/// @brief Mouse event.
	struct MouseEvent final
	{
		std::variant<MouseButtonEvent, MouseWheelEvent, MousePointerEvent, MouseConnectionEvent> event; ///< Event.
		std::chrono::time_point<std::chrono::steady_clock> timePoint; ///< Event time.
	};
}
