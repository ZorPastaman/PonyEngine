/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Window:Messages.KeyboardMessage;

import :Messages.KeyboardKeyCode;

namespace PonyEngine::Window::Messages
{
	export struct KeyboardMessage final
	{
	public:
		constexpr inline KeyboardMessage() noexcept;
		constexpr inline KeyboardMessage(KeyboardKeyCode keyCode, bool isDown) noexcept;
		constexpr inline KeyboardMessage(const KeyboardMessage& other) noexcept;
		
		constexpr inline ~KeyboardMessage() noexcept = default;

		KeyboardKeyCode keyCode;
		bool isDown;
	};

	constexpr inline KeyboardMessage::KeyboardMessage() noexcept :
		keyCode{},
		isDown{}
	{
	}

	constexpr inline KeyboardMessage::KeyboardMessage(KeyboardKeyCode keyCode, bool isDown) noexcept :
		keyCode{keyCode},
		isDown{isDown}
	{
	}

	constexpr inline KeyboardMessage::KeyboardMessage(const KeyboardMessage& other) noexcept :
		keyCode{other.keyCode},
		isDown{other.isDown}
	{
	}
}
