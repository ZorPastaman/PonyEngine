/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Window:KeyboardMessage;

import <format>;
import <ostream>;
import <string>;

import :KeyboardKeyCode;

namespace PonyEngine::Window
{
	/// @brief Keyboard message.
	export class KeyboardMessage final
	{
	public:
		/// @brief Create a keyboard message.
		/// @param keyCode Key code.
		/// @param isDown @a True if the key is pressed; @a false if it's unpressed.
		[[nodiscard("Pure constructor")]]
		inline KeyboardMessage(KeyboardKeyCode keyCode, bool isDown) noexcept;
		[[nodiscard("Pure constructor")]]
		inline KeyboardMessage(const KeyboardMessage& other) noexcept = default;
		
		inline ~KeyboardMessage() noexcept = default;

		/// @brief Gets a key code.
		/// @return Key code.
		[[nodiscard("Pure function")]]
		inline KeyboardKeyCode GetKeyCode() const noexcept;
		/// @brief Gets is key down.
		/// @return Is key down?
		[[nodiscard("Pure function")]]
		inline bool GetIsDown() const noexcept;

		inline KeyboardMessage& operator =(const KeyboardMessage& other) noexcept = default;

		inline bool operator ==(const KeyboardMessage& other) const noexcept = default;

		/// @brief Creates a string representing a @p KeyboardMessage.
		/// @return Representing string.
		[[nodiscard("Pure function")]]
		std::string ToString() const;

	private:
		KeyboardKeyCode m_keyCode; /// @brief Key code.
		bool m_isDown; /// @brief @a True if the key is pressed; @a false if it's unpressed.
	};

	/// @brief Puts message.ToString into the @p stream.
	/// @param stream Target.
	/// @param message Source.
	/// @return @p Stream.
	export inline std::ostream& operator <<(std::ostream& stream, const KeyboardMessage& message);

	inline KeyboardMessage::KeyboardMessage(const KeyboardKeyCode keyCode, const bool isDown) noexcept :
		m_keyCode{keyCode},
		m_isDown{isDown}
	{
	}

	inline KeyboardKeyCode KeyboardMessage::GetKeyCode() const noexcept
	{
		return m_keyCode;
	}

	inline bool KeyboardMessage::GetIsDown() const noexcept
	{
		return m_isDown;
	}

	std::string KeyboardMessage::ToString() const
	{
		return std::format("(KeyCode: {}, IsDown: {})", Window::ToString(m_keyCode), m_isDown);
	}

	std::ostream& operator <<(std::ostream& stream, const KeyboardMessage& message)
	{
		return stream << message.ToString();
	}
}
