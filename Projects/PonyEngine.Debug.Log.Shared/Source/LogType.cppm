/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Debug.Log.LogType;

import <cstdint>;
import <type_traits>;

namespace PonyEngine::Debug::Log
{
	export enum class LogType : std::uint_fast8_t
	{
		Verbose = 1 << 0,
		Debug = 1 << 1,
		Info = 1 << 2,
		Warning = 1 << 3,
		Error = 1 << 4,
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
}
