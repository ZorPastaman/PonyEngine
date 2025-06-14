/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Log:LogData;

import std;

import :LogType;

export namespace PonyEngine::Log
{
	/// @brief Log data.
	struct LogData final
	{
		std::optional<std::basic_stacktrace<std::allocator<std::stacktrace_entry>>> stacktrace = std::nullopt; ///< Stacktrace.
	};
}
