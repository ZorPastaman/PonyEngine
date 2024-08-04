/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.StringUtility;

import <algorithm>;
import <exception>;
import <format>;
import <string>;
import <type_traits>;


export namespace PonyEngine::Utility
{
	/// @brief The concept is satisfied if @p T has a function that accepts @p const @p std::exception& like this: @p exceptionHandler(e).
	template<typename T>
	concept ExceptionHandler = requires (const T& exceptionHandler, const std::exception& e)
	{
		{ exceptionHandler(e) } noexcept;
	};

	/// @brief Converts std::wstring to std::string. It just casts every wchar to char.
	/// @param source Source.
	/// @return Converted string.
	[[nodiscard("Pure function")]]
	std::string ConvertToString(const std::wstring& source);

	/// @brief @p std::format() wrapper that doesn't throw.
	/// @tparam Args Format argument types.
	/// @param format Format.
	/// @param args Format arguments.
	/// @return Format result or empty string if std::format() threw.
	template<typename... Args> [[nodiscard("Pure function")]]
	std::string SafeFormat(std::format_string<Args...> format, Args&&... args) noexcept;
	/// @brief @p std::format() wrapper that doesn't throw. If @p std::format() throws, the exception is passed to the @p ExceptionHandler.
	/// @tparam ExceptionHandler Exception handler type.
	/// @tparam Args Format argument types.
	/// @param format Format.
	/// @param args Format arguments.
	/// @return Format result or empty string if std::format() threw.
	template<ExceptionHandler ExceptionHandler, typename... Args> [[nodiscard("Pure function")]]
	std::string SafeFormat(std::format_string<Args...> format, Args&&... args) noexcept requires (std::is_default_constructible_v<ExceptionHandler>);
	/// @brief @p std::format() wrapper that doesn't throw. If @p std::format() throws, the exception is passed to the @p exceptionHandler.
	/// @tparam ExceptionHandler Exception handler type.
	/// @tparam Args Format argument types.
	/// @param exceptionHandler Exception handler.
	/// @param format Format.
	/// @param args Format arguments.
	/// @return Format result or empty string if std::format() threw.
	template<ExceptionHandler ExceptionHandler, typename... Args> [[nodiscard("Pure function")]]
	std::string SafeFormat(const ExceptionHandler& exceptionHandler, std::format_string<Args...> format, Args&&... args) noexcept;
}

namespace PonyEngine::Utility
{
	std::string ConvertToString(const std::wstring& source)
	{
		std::string answer(source.length(), 0);
		std::ranges::transform(source, answer.begin(), [](const wchar_t c) { return static_cast<std::string::value_type>(c); });

		return answer;
	}

	template<typename... Args>
	std::string SafeFormat(std::format_string<Args...> format, Args&&... args) noexcept
	{
		try
		{
			return std::format(format, std::forward<Args>(args)...);
		}
		catch (...)
		{
			return std::string();
		}
	}

	template<ExceptionHandler ExceptionHandler, typename... Args>
	std::string SafeFormat(std::format_string<Args...> format, Args&&... args) noexcept requires (std::is_default_constructible_v<ExceptionHandler>)
	{
		try
		{
			return std::format(format, std::forward<Args>(args)...);
		}
		catch (const std::exception& e)
		{
			ExceptionHandler()(e);

			return std::string();
		}
	}

	template<ExceptionHandler ExceptionHandler, typename... Args>
	std::string SafeFormat(const ExceptionHandler& exceptionHandler, std::format_string<Args...> format, Args&&... args) noexcept
	{
		try
		{
			return std::format(format, std::forward<Args>(args)...);
		}
		catch (const std::exception& e)
		{
			exceptionHandler(e);

			return std::string();
		}
	}
}
