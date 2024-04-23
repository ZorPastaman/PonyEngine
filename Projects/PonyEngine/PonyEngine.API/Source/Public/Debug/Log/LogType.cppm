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

export namespace PonyEngine::Debug::Log
{
	/// @brief Severity of a log.
	enum class LogType : std::uint_fast8_t
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
	[[nodiscard("Pure function")]]
	std::string ToString(LogType logType, bool addNumber = false);

	[[nodiscard("Pure operator")]] 
	constexpr LogType operator ~(LogType logType) noexcept;

	[[nodiscard("Pure operator")]] 
	constexpr LogType operator &(LogType left, LogType right) noexcept;

	[[nodiscard("Pure operator")]] 
	constexpr LogType operator |(LogType left, LogType right) noexcept;

	[[nodiscard("Pure operator")]] 
	constexpr LogType operator ^(LogType left, LogType right) noexcept;

	/// @brief Puts ToString(logType) into the @p stream.
	/// @param stream Target stream.
	/// @param logType Input source.
	/// @return @p stream.
	std::ostream& operator <<(std::ostream& stream, LogType logType);
}

namespace PonyEngine::Debug::Log
{
	namespace
	{
		/// @brief Log type names by index.
		constexpr std::array<const char*, 7> LogTypeNames
		{
			"Verbose",
			"Debug",
			"Info",
			"Warning",
			"Error",
			"Exception",
			"Unknown"
		};

		/// @brief Creates a string representing the @p logType.
		/// @param logType Log type.
		/// @return Created string.
		[[nodiscard("Pure function")]]
		std::string ToStringInternal(LogType logType)
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
					number >>= 1, steps = std::min(static_cast<std::underlying_type_t<LogType>>(steps + 1), static_cast<std::underlying_type_t<LogType>>(LogTypeNames.size() - 1)))
				{
					if (number & std::underlying_type_t<LogType>{1})
					{
						answer += LogTypeNames[steps];

						if (number >> 1)
						{
							answer += " | ";
						}
					}
				}
			}

			return answer;
		}
	}

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
		return stream << ToString(logType, true);
	}
}
