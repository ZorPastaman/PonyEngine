/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Log.Ext:LogEntry;

import std;

import PonyEngine.Log;

export namespace PonyEngine::Log
{
	/// @brief Information that must be logged.
	struct LogEntry final
	{
		std::string_view formattedMessage; ///< Pre-formatted log message.
		std::string_view message; ///< Log message.
		const std::stacktrace* stacktrace = nullptr; ///< Stacktrace attached to the log entry.
		std::exception_ptr exceptionPtr; ///< Exception pointer attached to the log entry. It always points the @p exception.
		std::chrono::time_point<std::chrono::system_clock> timePoint; ///< Time when the log entry is created.
		std::uint64_t frameCount = 0ull; ///< Frame when the log entry is created.
		LogType logType = LogType::Verbose; ///< Log type.
	};
}
