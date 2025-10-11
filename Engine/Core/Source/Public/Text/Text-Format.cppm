/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Text:Format;

import std;

export namespace PonyEngine::Text
{
	/// @brief The concept is satisfied if @p T has a function that accepts @p const @p std::exception& like this: @p exceptionHandler(e).
	template<typename T>
	concept ExceptionHandler = requires (T& exceptionHandler, const std::exception& e)
	{
		{ exceptionHandler(e) } noexcept;
	};

	/// @brief @p std::format() wrapper that doesn't throw.
	/// @tparam Args Format argument types.
	/// @param format Format.
	/// @param args Format arguments.
	/// @return Format result or exception string.
	template<typename... Args> [[nodiscard("Pure function")]]
	std::string FormatSafe(std::format_string<Args...> format, Args&&... args) noexcept;
	/// @brief @p std::format() wrapper that doesn't throw. If @p std::format() throws, the exception is passed to the @p ExceptionHandler.
	/// @tparam ExceptionHandler Exception handler type.
	/// @tparam Args Format argument types.
	/// @param format Format.
	/// @param args Format arguments.
	/// @return Format result or exception string.
	template<ExceptionHandler ExceptionHandler, typename... Args> [[nodiscard("Pure function")]]
	std::string FormatSafe(std::format_string<Args...> format, Args&&... args) noexcept requires (std::is_default_constructible_v<ExceptionHandler>);
	/// @brief @p std::format() wrapper that doesn't throw. If @p std::format() throws, the exception is passed to the @p exceptionHandler.
	/// @tparam ExceptionHandler Exception handler type.
	/// @tparam Args Format argument types.
	/// @param exceptionHandler Exception handler.
	/// @param format Format.
	/// @param args Format arguments.
	/// @return Format result or exception string.
	template<ExceptionHandler ExceptionHandler, typename... Args> [[nodiscard("Pure function")]]
	std::string FormatSafe(ExceptionHandler& exceptionHandler, std::format_string<Args...> format, Args&&... args) noexcept;
}

namespace PonyEngine::Text
{
	/// @brief Exception handler that does nothing.
	struct EmptyExceptionHandler final
	{
		/// @brief Does nothing.
		void operator ()(const std::exception&) const noexcept
		{
		}
	};

	template<typename... Args>
	std::string FormatSafe(const std::format_string<Args...> format, Args&&... args) noexcept
	{
		return FormatSafe<EmptyExceptionHandler>(format, std::forward<Args>(args)...);
	}

	template<ExceptionHandler ExceptionHandler, typename... Args>
	std::string FormatSafe(const std::format_string<Args...> format, Args&&... args) noexcept requires (std::is_default_constructible_v<ExceptionHandler>)
	{
		auto handler = ExceptionHandler();

		return FormatSafe(handler, format, std::forward<Args>(args)...);
	}

	template<ExceptionHandler ExceptionHandler, typename... Args>
	std::string FormatSafe(ExceptionHandler& exceptionHandler, const std::format_string<Args...> format, Args&&... args) noexcept
	{
		try
		{
			try
			{
				return std::format(format, std::forward<Args>(args)...);
			}
			catch (const std::exception& e)
			{
				exceptionHandler(e);

				return std::string(e.what());
			}
		}
		catch (...)
		{
			return std::string();
		}
	}
}
