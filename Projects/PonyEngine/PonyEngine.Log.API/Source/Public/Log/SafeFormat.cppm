/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Log:SafeFormat;

import <format>;
import <string>;

import PonyEngine.StringUtility;

import :ConsoleExceptionHandler;

export namespace PonyEngine::Log
{
	/// @brief @p std::format() wrapper that doesn't throw. If @p std::format() throws, the exception is passed to the @p ConsoleExceptionHandler.
	/// @tparam Args Format argument types.
	/// @param format Format.
	/// @param args Format arguments.
	/// @return Format result or empty string if std::format() threw.
	template<typename... Args> [[nodiscard("Pure function")]]
	std::string SafeFormat(std::format_string<Args...> format, Args&&... args) noexcept;
}

namespace PonyEngine::Log
{
	template<typename... Args>
	std::string SafeFormat(std::format_string<Args...> format, Args&&... args) noexcept
	{
		return Utility::SafeFormat<ConsoleExceptionHandler>(format, std::forward<Args>(args)...);
	}
}
