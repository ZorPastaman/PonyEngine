/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Log.Impl:LogTypeSymbol;

import std;

import PonyEngine.Log;

export namespace PonyEngine::Log
{
	/// @brief Gets a log type symbol for the @p logType.
	/// @param logType Log type.
	/// @return Log type symbol.
	[[nodiscard("Pure function")]]
	constexpr char GetLogTypeSymbol(LogType logType) noexcept;
}

namespace PonyEngine::Log
{
	/// @brief Log type symbols by index. The last one is used for incorrect log types.
	constexpr std::array<char, 7> LogTypeSymbols
	{
		'V',
		'D',
		'I',
		'W',
		'E',
		'X',
		'U'
	};

	constexpr char GetLogTypeSymbol(const LogType logType) noexcept
	{
		return LogTypeSymbols[std::min(static_cast<std::size_t>(logType), LogTypeSymbols.size() - 1uz)];
	}
}
