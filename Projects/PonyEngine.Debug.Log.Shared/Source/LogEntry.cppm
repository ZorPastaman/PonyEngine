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

import <string>;

import PonyEngine.Debug.Log.LogType;

namespace PonyEngine::Debug::Log
{
	export struct LogEntry final
	{
	public:
		constexpr LogEntry(const std::string& message, std::chrono::time_point<std::chrono::system_clock> timePoint, std::size_t frameCount, LogType logType) noexcept;

		constexpr ~LogEntry() = default;

		const std::string& message;
		std::chrono::time_point<std::chrono::system_clock> timePoint;
		std::size_t frameCount;
		LogType logType;
	};

	constexpr LogEntry::LogEntry(const std::string& message, std::chrono::time_point<std::chrono::system_clock> timePoint, std::size_t frameCount, LogType logType) noexcept :
		message(message),
		timePoint(timePoint),
		frameCount{frameCount},
		logType{logType}
	{
	}
}
