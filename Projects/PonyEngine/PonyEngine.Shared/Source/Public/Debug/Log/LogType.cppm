/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Debug.Log:LogType;

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
	std::string ToString(const LogType logType, const bool addNumber = false);

	export [[nodiscard("Pure function")]] 
	constexpr inline LogType operator ~(const LogType logType) noexcept;

	export [[nodiscard("Pure function")]] 
	constexpr inline LogType operator &(const LogType left, const LogType right) noexcept;

	export [[nodiscard("Pure function")]] 
	constexpr inline LogType operator |(const LogType left, const LogType right) noexcept;

	export [[nodiscard("Pure function")]] 
	constexpr inline LogType operator ^(const LogType left, const LogType right) noexcept;

	/// @brief Puts ToString(logType) into the @p stream.
	/// @param stream Target stream.
	/// @param logType Input source.
	/// @return @p stream.
	export inline std::ostream& operator <<(std::ostream& stream, const LogType logType);

	constexpr inline LogType operator ~(const LogType logType) noexcept
	{
		return static_cast<LogType>(~static_cast<std::underlying_type_t<LogType>>(logType)) & LogType::All;
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

	std::string ToString(const LogType logType, const bool addNumber)
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
				if (logType == LogType::None)
				{
					answer = "None";
				}
				else
				{
					answer = "Unknown";
				}

				answer += delimiter;
			}

			answer.erase(answer.end() - delimiter.size(), answer.end());

			if (!addNumber)
			{
				return answer;
			}

			auto number = static_cast<std::underlying_type_t<LogType>>(logType);
			return std::format("{} ({})", answer, number);
	}
}
