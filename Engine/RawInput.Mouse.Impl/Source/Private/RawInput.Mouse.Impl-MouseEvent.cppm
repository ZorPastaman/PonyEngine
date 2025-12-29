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

import :MouseAxis;

export namespace PonyEngine::Input
{
	/// @brief Mouse button event.
	struct MouseButtonEvent final
	{
		MouseButton button; ///< Button axis.
		bool state; ///< Is the button pressed?
		Math::Vector2<std::int32_t> cursorPosition; ///< Cursor position.
	};

	/// @brief Mouse wheel event.
	struct MouseWheelEvent final
	{
		MouseWheel wheel; ///< Wheel axis.
		float delta; ///< Wheel delta.
		Math::Vector2<std::int32_t> cursorPosition; ///< Cursor position.
	};

	/// @brief Mouse pointer event.
	struct MousePointerEvent final
	{
		Math::Vector2<float> delta; ///< Pointer delta.
		Math::Vector2<std::int32_t> cursorPosition; ///< Cursor position.
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
