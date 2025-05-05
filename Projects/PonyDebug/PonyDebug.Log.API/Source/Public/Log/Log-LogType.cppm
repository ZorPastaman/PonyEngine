/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyDebug.Log:LogType;

import <array>;
import <cmath>;
import <cstddef>;
import <cstdint>;
import <ostream>;
import <string_view>;
import <type_traits>;

export namespace PonyDebug::Log
{
	/// @brief Severity of a log.
	enum class LogType : std::uint8_t
	{
		/// @brief Log everything.
		Verbose,
		/// @brief Log additional debug information.
		Debug,
		/// @brief Log a normal program execution.
		Info,
		/// @brief Log a non-critical error or suspicious program execution.
		Warning,
		/// @brief Log an error.
		Error,
		/// @brief Log an exception.
		Exception
	};

	/// @brief Gets a string representing the @p logType.
	/// @param logType Log type.
	/// @return Representing string.
	[[nodiscard("Pure function")]]
	constexpr std::string_view ToString(LogType logType) noexcept;

	/// @brief Puts @p ToString(logType) into the @p stream.
	/// @param stream Target stream.
	/// @param logType Input source.
	/// @return @p stream.
	std::ostream& operator <<(std::ostream& stream, LogType logType);
}

namespace PonyDebug::Log
{
	/// @brief Log type names by index.
	constexpr std::array<std::string_view, 7> LogTypeNames
	{
		"Verbose",
		"Debug",
		"Info",
		"Warning",
		"Error",
		"Exception",
		"Unknown"
	};

	constexpr std::string_view ToString(const LogType logType) noexcept
	{
		return LogTypeNames[std::min(static_cast<std::size_t>(logType), LogTypeNames.size() - 1)];
	}

	std::ostream& operator <<(std::ostream& stream, const LogType logType)
	{
		return stream << ToString(logType);
	}
}
