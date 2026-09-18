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
	/// @brief Source data of the log.
	struct LogEntry final
	{
		std::string_view message; ///< Log message.
		const std::stacktrace* stacktrace = nullptr; ///< Stacktrace attached to the log entry. May be nullptr.
		const std::exception_ptr* exception = nullptr; ///< Exception attached to the log entry. May be nullptr.
		std::chrono::time_point<std::chrono::system_clock> timePoint; ///< Time when the log entry is created.
		std::thread::id threadId; ///< Thread on which the log function was called.
		LogType logType = LogType::Verbose; ///< Log type.
	};
}
