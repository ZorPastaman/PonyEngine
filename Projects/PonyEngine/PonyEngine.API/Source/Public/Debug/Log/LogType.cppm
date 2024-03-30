/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Debug.Log:LogType;

import <algorithm>;
import <array>;
import <cstdint>;
import <format>;
import <string>;
import <ostream>;
import <type_traits>;

namespace PonyEngine::Debug::Log
{
	/// @brief Severity of a log.
	export enum class LogType : std::uint_fast8_t
	{
		/// @brief Special name for the zero flag state.
		None = 0,
		/// @brief Log only when it's totally required to log everything.
		Verbose = 1 << 0,
		/// @brief Log additional debug information.
		Debug = 1 << 1,
		/// @brief Log a normal program execution.
		Info = 1 << 2,
		/// @brief Log a non-critical error or suspicion program execution.
		Warning = 1 << 3,
		/// @brief Log an error.
		Error = 1 << 4,
		/// @brief Log an exception.
		Exception = 1 << 5,
		/// @brief Special name the all flags state.
		All = Verbose | Debug | Info | Warning | Error | Exception
	};

	/// @brief Creates a string representing the @p logType.
	/// @param logType Log type.
	/// @param addNumber If it's true, the string will contain a number representation.
	/// @return Created string.
	export [[nodiscard("Pure function")]]
	std::string ToString(LogType logType, bool addNumber = false);

	/// @brief Creates a string representing the @p logType.
	/// @param logType Log type.
	/// @return Created string.
	[[nodiscard("Pure function")]]
	static std::string ToStringInternal(LogType logType);

	export [[nodiscard("Pure operator")]] 
	constexpr inline LogType operator ~(LogType logType) noexcept;

	export [[nodiscard("Pure operator")]] 
	constexpr inline LogType operator &(LogType left, LogType right) noexcept;

	export [[nodiscard("Pure operator")]] 
	constexpr inline LogType operator |(LogType left, LogType right) noexcept;

	export [[nodiscard("Pure operator")]] 
	constexpr inline LogType operator ^(LogType left, LogType right) noexcept;

	/// @brief Puts ToString(logType) into the @p stream.
	/// @param stream Target stream.
	/// @param logType Input source.
	/// @return @p stream.
	export inline std::ostream& operator <<(std::ostream& stream, LogType logType);

	/// @brief Log type names by index.
	static const std::array<const char*, 7> s_logTypeNames
	{
		"Verbose",
		"Debug",
		"Info",
		"Warning",
		"Error",
		"Exception",
		"Unknown"
	};

	std::string ToString(const LogType logType, const bool addNumber)
	{
		std::string answer = ToStringInternal(logType);

		if (!addNumber)
		{
			return answer;
		}

		auto number = static_cast<std::underlying_type_t<LogType>>(logType);
		return std::format("{} ({})", answer, number);
	}

	static std::string ToStringInternal(LogType logType)
	{
		std::string answer;

		if (logType == LogType::None)
		{
			answer = "None";
		}
		else
		{
			for (auto number = static_cast<std::underlying_type_t<LogType>>(logType), steps = std::underlying_type_t<LogType>{0};
				number != std::underlying_type_t<LogType>{0};
				number >>= 1, steps = std::min(static_cast<std::underlying_type_t<LogType>>(steps + 1), static_cast<std::underlying_type_t<LogType>>(s_logTypeNames.size() - 1)))
			{
				if (number & std::underlying_type_t<LogType>{1})
				{
					answer += s_logTypeNames[steps];

					if (number >> 1)
					{
						answer += " | ";
					}
				}
			}
		}

		return answer;
	}

	constexpr inline LogType operator ~(const LogType logType) noexcept
	{
		return logType ^ LogType::All;
	}

	constexpr inline LogType operator &(const LogType left, const LogType right) noexcept
	{
		return static_cast<LogType>(static_cast<std::underlying_type_t<LogType>>(left) & static_cast<std::underlying_type_t<LogType>>(right));
	}

	constexpr inline LogType operator |(const LogType left, const LogType right) noexcept
	{
		return static_cast<LogType>(static_cast<std::underlying_type_t<LogType>>(left) | static_cast<std::underlying_type_t<LogType>>(right));
	}

	constexpr inline LogType operator ^(const LogType left, const LogType right) noexcept
	{
		return static_cast<LogType>(static_cast<std::underlying_type_t<LogType>>(left) ^ static_cast<std::underlying_type_t<LogType>>(right));
	}

	inline std::ostream& operator <<(std::ostream& stream, const LogType logType)
	{
		return stream << ToString(logType, true);
	}
}
