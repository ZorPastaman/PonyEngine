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
		[[nodiscard("Pure constructor")]]
		inline KeyboardMessage() noexcept = default;
		/// @brief Create a keyboard message.
		/// @param keyCode Key code.
		/// @param isDown @a True if the key is pressed; @a false if it's unpressed.
		[[nodiscard("Pure constructor")]]
		inline KeyboardMessage(KeyboardKeyCode keyCode, bool isDown) noexcept;
		[[nodiscard("Pure constructor")]]
		inline KeyboardMessage(const KeyboardMessage& other) noexcept = default;
		inline KeyboardMessage(KeyboardMessage&& other) noexcept = default;
		
		inline ~KeyboardMessage() noexcept = default;

		inline KeyboardMessage& operator =(const KeyboardMessage& other) noexcept = default;
		inline KeyboardMessage& operator =(KeyboardMessage&& other) noexcept = default;

		KeyboardKeyCode keyCode; /// @brief Key code.
		bool isDown; /// @brief @a True if the key is pressed; @a false if it's unpressed.
	};

	inline KeyboardMessage::KeyboardMessage(const KeyboardKeyCode keyCode, const bool isDown) noexcept :
		keyCode{keyCode},
		isDown{isDown}
	{
	}
}
