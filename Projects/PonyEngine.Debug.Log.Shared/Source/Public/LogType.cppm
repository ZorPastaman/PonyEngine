/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <format>

export module PonyEngine.Debug.Log.LogType;

import <cstdint>;
import <string>;
import <ostream>;
import <type_traits>;

namespace PonyEngine::Debug::Log
{
	/// @brief Severity of a log.
	export enum class LogType : std::uint_fast8_t
	{
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
		Exception = 1 << 5
	};

	export constexpr inline LogType operator ~(const LogType logType) noexcept
	{
		return static_cast<LogType>(~static_cast<std::underlying_type_t<LogType>>(logType));
	}

	export constexpr inline LogType operator &(const LogType left, const LogType right) noexcept
	{
		return static_cast<LogType>(static_cast<std::underlying_type_t<LogType>>(left) & static_cast<std::underlying_type_t<LogType>>(right));
	}

	export constexpr inline LogType operator |(const LogType left, const LogType right) noexcept
	{
		return static_cast<LogType>(static_cast<std::underlying_type_t<LogType>>(left) | static_cast<std::underlying_type_t<LogType>>(right));
	}

	export constexpr inline LogType operator ^(const LogType left, const LogType right) noexcept
	{
		return static_cast<LogType>(static_cast<std::underlying_type_t<LogType>>(left) ^ static_cast<std::underlying_type_t<LogType>>(right));
	}

	/// @brief Creates a string representing the @p logType.
	/// @param logType Log type.
	/// @param addNumber If it's true, the string will contain a number representation.
	/// @return Created string.
	export std::string ToString(const LogType logType, const bool addNumber = false)
	{
		const std::string delimiter = " | ";
		std::string answer;

		if ((logType & LogType::Verbose) == LogType::Verbose)
		{
			answer += "Verbose" + delimiter;
		}
		if ((logType & LogType::Debug) == LogType::Debug)
		{
			answer += "Debug" + delimiter;
		}
		if ((logType & LogType::Info) == LogType::Info)
		{
			answer += "Info" + delimiter;
		}
		if ((logType & LogType::Warning) == LogType::Warning)
		{
			answer += "Warning" + delimiter;
		}
		if ((logType & LogType::Error) == LogType::Error)
		{
			answer += "Error" + delimiter;
		}
		if ((logType & LogType::Exception) == LogType::Exception)
		{
			answer += "Exception" + delimiter;
		}
		
		if (answer.empty()) [[unlikely]]
		{
			answer = "None" + delimiter;
		}

		answer.erase(answer.end() - delimiter.size(), answer.end());

		if (!addNumber)
		{
			return answer;
		}

		auto number = static_cast<std::underlying_type_t<LogType>>(logType);

		return std::format("{} ({})", answer, number);
	}

	export std::ostream& operator <<(std::ostream& stream, const LogType logType)
	{
		return stream << ToString(logType, true);
	}
}
