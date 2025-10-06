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

	/// @brief Safe formats the string.
	/// @param logType Log type.
	/// @param message Message.
	/// @return Formatted string.
	[[nodiscard("Pure function")]]
	std::string LogString(LogType logType, std::string_view message) noexcept;
	/// @brief Safe formats the string.
	/// @tparam Args Argument types.
	/// @param logType Log type.
	/// @param format Format.
	/// @param args Arguments.
	/// @return Formatted string.
	template<typename... Args> [[nodiscard("Pure function")]]
	std::string LogString(LogType logType, std::format_string<Args...> format, Args&&... args) noexcept;
	/// @brief Safe formats the string.
	/// @param logType Log type.
	/// @param stacktrace Stacktrace.
	/// @param message Message.
	/// @return Formatted string.
	[[nodiscard("Pure function")]]
	std::string LogString(LogType logType, const std::stacktrace& stacktrace, std::string_view message) noexcept;
	/// @brief Safe formats the string.
	/// @tparam Args Argument types.
	/// @param logType Log type.
	/// @param stacktrace Stacktrace.
	/// @param format Format.
	/// @param args Arguments.
	/// @return Formatted string.
	template<typename... Args> [[nodiscard("Pure function")]]
	std::string LogString(LogType logType, const std::stacktrace& stacktrace, std::format_string<Args...> format, Args&&... args) noexcept;

	/// @brief Safe formats the string.
	/// @param exception Exception.
	/// @return Formatted string.
	[[nodiscard("Pure function")]]
	std::string LogString(const std::exception& exception) noexcept;
	/// @brief Safe formats the string.
	/// @param exception Exception.
	/// @param message Message.
	/// @return Formatted string.
	[[nodiscard("Pure function")]]
	std::string LogString(const std::exception& exception, std::string_view message) noexcept;
	/// @brief Safe formats the string.
	/// @param exception Exception.
	/// @param stacktrace Stacktrace.
	/// @return Formatted string.
	[[nodiscard("Pure function")]]
	std::string LogString(const std::exception& exception, const std::stacktrace& stacktrace) noexcept;
	/// @brief Safe formats the string.
	/// @tparam Args Argument types.
	/// @param exception Exception.
	/// @param format Format.
	/// @param args Arguments.
	/// @return Formatted string.
	template<typename... Args> [[nodiscard("Pure function")]]
	std::string LogString(const std::exception& exception, std::format_string<Args...> format, Args&&... args) noexcept;
	/// @brief Safe formats the string.
	/// @param exception Exception.
	/// @param stacktrace Stacktrace.
	/// @param message Message.
	/// @return Formatted string.
	[[nodiscard("Pure function")]]
	std::string LogString(const std::exception& exception, const std::stacktrace& stacktrace, std::string_view message) noexcept;
	/// @brief Safe formats the string.
	/// @tparam Args Argument types.
	/// @param exception Exception.
	/// @param stacktrace Stacktrace.
	/// @param format Format.
	/// @param args Arguments.
	/// @return Formatted string.
	template<typename... Args> [[nodiscard("Pure function")]]
	std::string LogString(const std::exception& exception, const std::stacktrace& stacktrace, std::format_string<Args...> format, Args&&... args) noexcept;
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

	std::string LogString(const LogType logType, const std::string_view message) noexcept
	{
		return LogFormat(logType, message);
	}

	template<typename... Args>
	std::string LogString(const LogType logType, const std::format_string<Args...> format, Args&&... args) noexcept
	{
		return LogFormat(logType, LogString(format, std::forward<Args>(args)...));
	}

	std::string LogString(const LogType logType, const std::stacktrace& stacktrace, const std::string_view message) noexcept
	{
		return LogFormat(logType, message, stacktrace);
	}

	template<typename... Args>
	std::string LogString(const LogType logType, const std::stacktrace& stacktrace, const std::format_string<Args...> format, Args&&... args) noexcept
	{
		return LogFormat(logType, LogString(format, std::forward<Args>(args)...), stacktrace);
	}

	std::string LogString(const std::exception& exception) noexcept
	{
		return LogFormat(LogType::Exception, exception.what());
	}

	std::string LogString(const std::exception& exception, const std::string_view message) noexcept
	{
		return LogFormat(LogType::Exception, exception.what(), message);
	}

	std::string LogString(const std::exception& exception, const std::stacktrace& stacktrace) noexcept
	{
		return LogFormat(LogType::Exception, exception.what(), stacktrace);
	}

	template<typename... Args>
	std::string LogString(const std::exception& exception, std::format_string<Args...> format, Args&&... args) noexcept
	{
		return LogFormat(LogType::Exception, exception.what(), LogString(format, std::forward<Args>(args)...));
	}

	std::string LogString(const std::exception& exception, const std::stacktrace& stacktrace, const std::string_view message) noexcept
	{
		return LogFormat(LogType::Exception, exception.what(), message, stacktrace);
	}

	template<typename... Args>
	std::string LogString(const std::exception& exception, const std::stacktrace& stacktrace, std::format_string<Args...> format, Args&&... args) noexcept
	{
		return LogFormat(LogType::Exception, exception.what(), LogString(format, std::forward<Args>(args)...), stacktrace);
	}
}
