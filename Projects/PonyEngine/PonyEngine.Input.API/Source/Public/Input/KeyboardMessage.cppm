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
	struct KeyboardMessage final
	{
		/// @brief Creates a string representing the message.
		/// @return Representing string.
		[[nodiscard("Pure function")]]
		std::string ToString() const;

		[[nodiscard("Pure operator")]]
		bool operator ==(const KeyboardMessage& other) const noexcept = default;

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
	std::string KeyboardMessage::ToString() const
	{
		return std::format("(KeyCode: {}, IsDown: {})", Input::ToString(keyCode), isDown);
	}

	std::ostream& operator <<(std::ostream& stream, const KeyboardMessage& message)
	{
		return stream << message.ToString();
	}
}
