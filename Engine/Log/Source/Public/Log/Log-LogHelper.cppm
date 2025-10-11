/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Log:LogHelper;

import std;

import PonyEngine.Text;

import :LogFormat;
import :LogType;

export namespace PonyEngine::Log
{
	// Functions here are used by PonyEngine/Log/Log.h

	/// @brief Returns the same message.
	/// @param message Message.
	/// @return Message.
	[[nodiscard("Pure function")]]
	std::string_view LogString(std::string_view message) noexcept;
	/// @brief Safe formats the string.
	/// @tparam Args Argument types.
	/// @param format Format.
	/// @param args Arguments.
	/// @return Formatted string.
	template<typename... Args> [[nodiscard("Pure function")]]
	std::string LogString(std::format_string<Args...> format, Args&&... args) noexcept;
}

namespace PonyEngine::Log
{
	std::string_view LogString(const std::string_view message) noexcept
	{
		return message;
	}

	template<typename... Args>
	std::string LogString(const std::format_string<Args...> format, Args&&... args) noexcept
	{
		return Text::FormatSafe(format, std::forward<Args>(args)...);
	}
}
