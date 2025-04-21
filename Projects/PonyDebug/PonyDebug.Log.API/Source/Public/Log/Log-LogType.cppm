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
		/// @brief Special name for the zero flag state.
		None = 0,
		/// @brief Log everything.
		Verbose = 1 << 0,
		/// @brief Log additional debug information.
		Debug = 1 << 1,
		/// @brief Log a normal program execution.
		Info = 1 << 2,
		/// @brief Log a non-critical error or suspicious program execution.
		Warning = 1 << 3,
		/// @brief Log an error.
		Error = 1 << 4,
		/// @brief Log an exception.
		Exception = 1 << 5,
		/// @brief Special name the all flags state.
		All = Verbose | Debug | Info | Warning | Error | Exception
	};

	/// @brief Gets a string representing the @p logType.
	/// @param logType Log type.
	/// @return Representing string.
	[[nodiscard("Pure function")]]
	constexpr std::string_view ToString(LogType logType) noexcept;

	/// @brief Bitwise complement operator.
	/// @param logType Log type.
	/// @return Complement of the @p logType.
	[[nodiscard("Pure operator")]] 
	constexpr LogType operator ~(LogType logType) noexcept;
	/// @brief Bitwise and operator.
	/// @param left Left log type.
	/// @param right Right log type.
	/// @return And of the log types.
	[[nodiscard("Pure operator")]] 
	constexpr LogType operator &(LogType left, LogType right) noexcept;
	/// @brief Bitwise or operator.
	/// @param left Left log type.
	/// @param right Right log type.
	/// @return Or of the log types.
	[[nodiscard("Pure operator")]] 
	constexpr LogType operator |(LogType left, LogType right) noexcept;
	/// @brief Bitwise xor operator.
	/// @param left Left log type.
	/// @param right Right log type.
	/// @return Xor of the log types.
	[[nodiscard("Pure operator")]] 
	constexpr LogType operator ^(LogType left, LogType right) noexcept;

	/// @brief Puts @p ToString(logType) into the @p stream.
	/// @param stream Target stream.
	/// @param logType Input source.
	/// @return @p stream.
	std::ostream& operator <<(std::ostream& stream, LogType logType);
}

namespace PonyDebug::Log
{
	/// @brief Log type names by index.
	constexpr std::array<std::string_view, 65> LogTypeNames
	{
		"None",
		"Verbose",
		"Debug",
		"Verbose | Debug",
		"Info",
		"Verbose | Info",
		"Debug | Info",
		"Verbose | Debug | Info",
		"Warning",
		"Verbose | Warning",
		"Debug | Warning",
		"Verbose | Debug | Warning",
		"Info | Warning",
		"Verbose | Info | Warning",
		"Debug | Info | Warning",
		"Verbose | Debug | Info | Warning",
		"Error",
		"Verbose | Error",
		"Debug | Error",
		"Verbose | Debug | Error",
		"Info | Error",
		"Verbose | Info | Error",
		"Debug | Info | Error",
		"Verbose | Debug | Info | Error",
		"Warning | Error",
		"Verbose | Warning | Error",
		"Debug | Warning | Error",
		"Verbose | Debug | Warning | Error",
		"Info | Warning | Error",
		"Verbose | Info | Warning | Error",
		"Debug | Info | Warning | Error",
		"Verbose | Debug | Info | Warning | Error",
		"Exception",
		"Verbose | Exception",
		"Debug | Exception",
		"Verbose | Debug | Exception",
		"Info | Exception",
		"Verbose | Info | Exception",
		"Debug | Info | Exception",
		"Verbose | Debug | Info | Exception",
		"Warning | Exception",
		"Verbose | Warning | Exception",
		"Debug | Warning | Exception",
		"Verbose | Debug | Warning | Exception",
		"Info | Warning | Exception",
		"Verbose | Info | Warning | Exception",
		"Debug | Info | Warning | Exception",
		"Verbose | Debug | Info | Warning | Exception",
		"Error | Exception",
		"Verbose | Error | Exception",
		"Debug | Error | Exception",
		"Verbose | Debug | Error | Exception",
		"Info | Error | Exception",
		"Verbose | Info | Error | Exception",
		"Debug | Info | Error | Exception",
		"Verbose | Debug | Info | Error | Exception",
		"Warning | Error | Exception",
		"Verbose | Warning | Error | Exception",
		"Debug | Warning | Error | Exception",
		"Verbose | Debug | Warning | Error | Exception",
		"Info | Warning | Error | Exception",
		"Verbose | Info | Warning | Error | Exception",
		"Debug | Info | Warning | Error | Exception",
		"Verbose | Debug | Info | Warning | Error | Exception", 
		"Unknown"
	};

	constexpr std::string_view ToString(const LogType logType) noexcept
	{
		return LogTypeNames[std::min(static_cast<std::size_t>(logType), LogTypeNames.size() - 1)];
	}

	constexpr LogType operator ~(const LogType logType) noexcept
	{
		return logType ^ LogType::All;
	}

	constexpr LogType operator &(const LogType left, const LogType right) noexcept
	{
		return static_cast<LogType>(static_cast<std::underlying_type_t<LogType>>(left) & static_cast<std::underlying_type_t<LogType>>(right));
	}

	constexpr LogType operator |(const LogType left, const LogType right) noexcept
	{
		return static_cast<LogType>(static_cast<std::underlying_type_t<LogType>>(left) | static_cast<std::underlying_type_t<LogType>>(right));
	}

	constexpr LogType operator ^(const LogType left, const LogType right) noexcept
	{
		return static_cast<LogType>(static_cast<std::underlying_type_t<LogType>>(left) ^ static_cast<std::underlying_type_t<LogType>>(right));
	}

	std::ostream& operator <<(std::ostream& stream, const LogType logType)
	{
		return stream << ToString(logType);
	}
}
