/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Log:LogType;

import <array>;
import <bit>;
import <cstddef>;
import <cstdint>;
import <ostream>;
import <type_traits>;

export namespace PonyEngine::Log
{
	/// @brief Severity of a log.
	enum class LogType : std::uint_fast8_t
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
	constexpr const char* ToString(LogType logType) noexcept;

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

namespace PonyEngine::Log
{
	/// @brief Log type names by index.
	constexpr std::array<const char*, 8> LogTypeNames
	{
		"None",
		"Verbose",
		"Debug",
		"Info",
		"Warning",
		"Error",
		"Exception",
		"Unknown"
	};

	constexpr const char* ToString(const LogType logType) noexcept
	{
		constexpr auto exceptionUnderlyingLogType = static_cast<std::underlying_type_t<LogType>>(LogType::Exception);

		const auto underlyingLogType = static_cast<std::underlying_type_t<LogType>>(logType);
		const std::size_t index = underlyingLogType
			? std::has_single_bit(underlyingLogType) && underlyingLogType <= exceptionUnderlyingLogType
				? std::countr_zero(underlyingLogType) + 1
				: LogTypeNames.size() - 1
			: 0;

		return LogTypeNames[index];
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
