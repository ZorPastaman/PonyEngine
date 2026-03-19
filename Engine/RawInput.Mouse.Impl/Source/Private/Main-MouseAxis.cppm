/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RawInput.Mouse.Impl:MouseAxis;

import std;

export namespace PonyEngine::RawInput::Mouse
{
	/// @brief Mouse button.
	enum class MouseButton : std::uint8_t
	{
		Left,
		Right,
		Middle,
		X1,
		X2
	};

	/// @brief Mouse wheel.
	enum class MouseWheel : std::uint8_t
	{
		Horizontal,
		Vertical
	};

	/// @brief Mouse pointer.
	enum class MousePointer : std::uint8_t
	{
		X,
		Y
	};

	constexpr std::size_t MouseButtonCount = 5uz;
	constexpr std::size_t MouseWheelCount = 2uz;
	constexpr std::size_t MousePointerCount = 2uz;
}
