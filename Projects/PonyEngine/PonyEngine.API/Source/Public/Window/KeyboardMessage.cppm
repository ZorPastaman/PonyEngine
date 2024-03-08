/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Window:KeyboardMessage;

import :KeyboardKeyCode;

namespace PonyEngine::Window
{
	/// @brief Keyboard message.
	export struct KeyboardMessage final
	{
	public:
		/// @brief Creates an empty keyboard message.
		constexpr inline KeyboardMessage() noexcept;
		/// @brief Create a keyboard message.
		/// @param keyCode Key code.
		/// @param isDown @a True if the key is pressed; @a false if it's unpressed.
		constexpr inline KeyboardMessage(KeyboardKeyCode keyCode, bool isDown) noexcept;
		/// @brief Copy constructor.
		/// @param other Copy source.
		constexpr inline KeyboardMessage(const KeyboardMessage& other) noexcept;
		
		constexpr inline ~KeyboardMessage() noexcept = default;

		/// @brief Copy assignment.
		/// @param other Copy source.
		/// @return @a This.
		constexpr inline KeyboardMessage& operator =(const KeyboardMessage& other) noexcept;

		KeyboardKeyCode keyCode; /// @brief Key code.
		bool isDown; /// @brief @a True if the key is pressed; @a false if it's unpressed.
	};

	constexpr inline KeyboardMessage::KeyboardMessage() noexcept :
		keyCode{},
		isDown{}
	{
	}

	constexpr inline KeyboardMessage::KeyboardMessage(const KeyboardKeyCode keyCode, const bool isDown) noexcept :
		keyCode{keyCode},
		isDown{isDown}
	{
	}

	constexpr inline KeyboardMessage::KeyboardMessage(const KeyboardMessage& other) noexcept :
		keyCode{other.keyCode},
		isDown{other.isDown}
	{
	}

	constexpr inline KeyboardMessage& KeyboardMessage::operator =(const KeyboardMessage& other) noexcept
	{
		keyCode = other.keyCode;
		isDown = other.isDown;

		return *this;
	}
}
