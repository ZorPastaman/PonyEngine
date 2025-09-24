/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Log:LogInput;

import std;

export namespace PonyEngine::Log
{
	/// @brief Log data input.
	struct LogInput final
	{
		std::string_view message; ///< Log message.
		const std::basic_stacktrace<std::allocator<std::stacktrace_entry>>* stacktrace = nullptr; ///< Stacktrace.
	};
}
