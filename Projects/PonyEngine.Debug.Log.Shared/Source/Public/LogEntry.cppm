/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <chrono>

export module PonyEngine.Debug.Log.LogEntry;

import <cstddef>;
import <string>;

import PonyEngine.Debug.Log.LogType;

namespace PonyEngine::Debug::Log
{
	/// @brief Information that must be logged.
	export struct LogEntry final
	{
	public:
		/// @brief Creates a log entry.
		/// @param message Log message.
		/// @param timePoint Time when the log entry is created.
		/// @param frameCount Frame when the log entry is created.
		/// @param logType Log type.
		constexpr LogEntry(const std::string& message, std::chrono::time_point<std::chrono::system_clock> timePoint, std::size_t frameCount, LogType logType) noexcept;

		constexpr ~LogEntry() = default;

		const std::string& message; /// @brief Log message.
		std::chrono::time_point<std::chrono::system_clock> timePoint; /// @brief Time when the log entry is created.
		std::size_t frameCount; /// @brief Frame when the log entry is created.
		LogType logType; /// @brief Log type.
	};

	constexpr LogEntry::LogEntry(const std::string& message, std::chrono::time_point<std::chrono::system_clock> timePoint, std::size_t frameCount, LogType logType) noexcept :
		message(message),
		timePoint(timePoint),
		frameCount{frameCount},
		logType{logType}
	{
	}
}
