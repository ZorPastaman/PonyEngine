/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Input:KeyboardMessage;

import <format>;
import <ostream>;
import <string>;

import :KeyboardKeyCode;

export namespace PonyEngine::Input
{
	/// @brief Keyboard message.
	class KeyboardMessage final
	{
	public:
		/// @brief Create a keyboard message.
		/// @param keyCode Key code.
		/// @param isDown @a True if the key is pressed; @a false if it's unpressed.
		[[nodiscard("Pure constructor")]]
		KeyboardMessage(KeyboardKeyCode keyCode, bool isDown) noexcept;
		[[nodiscard("Pure constructor")]]
		KeyboardMessage(const KeyboardMessage& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		KeyboardMessage(KeyboardMessage&& other) noexcept = default;

		~KeyboardMessage() noexcept = default;

		/// @brief Gets the key code.
		/// @return Key code.
		[[nodiscard("Pure function")]]
		KeyboardKeyCode GetKeyCode() const noexcept;
		/// @brief Is the key down?
		/// @return @a True if the key is down; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool GetIsDown() const noexcept;

		/// @brief Creates a string representing the message.
		/// @return Representing string.
		[[nodiscard("Pure function")]]
		std::string ToString() const;

		KeyboardMessage& operator =(const KeyboardMessage& other) noexcept = default;
		KeyboardMessage& operator =(KeyboardMessage&& other) noexcept = default;

		[[nodiscard("Pure operator")]]
		bool operator ==(const KeyboardMessage& other) const noexcept = default;

	private:
		KeyboardKeyCode keyCode; ///< Key code.
		bool isDown; ///< @a True if the key is pressed; @a false if it's unpressed.
	};

	/// @brief Puts message.ToString into the @p stream.
	/// @param stream Target.
	/// @param message Source.
	/// @return @p Stream.
	std::ostream& operator <<(std::ostream& stream, const KeyboardMessage& message);
}

namespace PonyEngine::Input
{
	KeyboardMessage::KeyboardMessage(const KeyboardKeyCode keyCode, const bool isDown) noexcept :
		keyCode{keyCode},
		isDown{isDown}
	{
	}

	KeyboardKeyCode KeyboardMessage::GetKeyCode() const noexcept
	{
		return keyCode;
	}

	bool KeyboardMessage::GetIsDown() const noexcept
	{
		return isDown;
	}

	std::string KeyboardMessage::ToString() const
	{
		return std::format("(KeyCode: {}, IsDown: {})", Input::ToString(keyCode), isDown);
	}

	std::ostream& operator <<(std::ostream& stream, const KeyboardMessage& message)
	{
		return stream << message.ToString();
	}
}
