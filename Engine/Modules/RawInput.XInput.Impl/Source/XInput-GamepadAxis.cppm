/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RawInput.XInput.Impl:GamepadAxis;

import std;

export namespace PonyEngine::RawInput::XInput
{
	/// @brief Button.
	enum class Button : std::uint8_t
	{
		DpadUp,
		DpadDown,
		DpadLeft,
		DpadRight,
		Start,
		Back,
		LeftThumb,
		RightThumb,
		LeftShoulder,
		RightShoulder,
		A,
		B,
		X,
		Y
	};

	/// @brief Trigger axis.
	enum class TriggerAxis : std::uint8_t
	{
		Left,
		Right
	};
	/// @brief Stick placement.
	enum class StickPlacement : std::uint8_t
	{
		Left,
		Right
	};
	/// @brief Stick direction.
	enum class StickDirection : std::uint8_t
	{
		Horizontal,
		Vertical
	};

	constexpr std::size_t ButtonCount = 14uz; ///< Button count.
	constexpr std::size_t TriggerAxisCount = 2uz; ///< Trigger axis count.
	constexpr std::size_t StickPlacementCount = 2uz; ///< Stick placement count.
	constexpr std::size_t StickDirectionCount = 2uz; ///< Stick direction count.
}
