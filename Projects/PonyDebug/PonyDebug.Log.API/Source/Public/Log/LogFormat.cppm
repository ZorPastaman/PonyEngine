/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyDebug.Log:LogFormat;

import <cstddef>;
import <chrono>;
import <format>;
import <string>;

import :LogType;

export namespace PonyDebug::Log
{
	/// @brief Formats a log string.
	/// @param logType Log type.
	/// @param message Log message.
	/// @param timePoint Time when the log has been created.
	/// @return Formatted log string.
	[[nodiscard("Pure function")]]
	std::string LogFormat(LogType logType, const char* message, std::chrono::time_point<std::chrono::system_clock> timePoint);
	/// @brief Formats a log string.
	/// @param logType Log type.
	/// @param message Log message.
	/// @param timePoint Time when the log has been created.
	/// @param frameCount Frame when the log has been created.
	/// @return Formatted log string.
	[[nodiscard("Pure function")]]
	std::string LogFormat(LogType logType, const char* message, std::chrono::time_point<std::chrono::system_clock> timePoint, std::size_t frameCount);
	/// @brief Formats a log string.
	/// @param logType Log type.
	/// @param firstMessage First log message.
	/// @param secondMessage Second log message.
	/// @param timePoint Time when the log has been created.
	/// @return Formatted log string.
	[[nodiscard("Pure function")]]
	std::string LogFormat(LogType logType, const char* firstMessage, const char* secondMessage, std::chrono::time_point<std::chrono::system_clock> timePoint);
	/// @brief Formats a log string.
	/// @param logType Log type.
	/// @param firstMessage First log message.
	/// @param secondMessage Second log message.
	/// @param timePoint Time when the log has been created.
	/// @param frameCount Frame when the log has been created.
	/// @return Formatted log string.
	[[nodiscard("Pure function")]]
	std::string LogFormat(LogType logType, const char* firstMessage, const char* secondMessage, std::chrono::time_point<std::chrono::system_clock> timePoint, std::size_t frameCount);

}

namespace PonyDebug::Log
{
	std::string LogFormat(const LogType logType, const char* const message, const std::chrono::time_point<std::chrono::system_clock> timePoint)
	{
		return std::format("[{}] [{:%F %R:%OS UTC}] {}\n", ToString(logType), timePoint, message);
	}

	std::string LogFormat(const LogType logType, const char* const message, const std::chrono::time_point<std::chrono::system_clock> timePoint, const std::size_t frameCount)
	{
		return std::format("[{}] [{:%F %R:%OS UTC} ({})] {}\n", ToString(logType), timePoint, frameCount, message);
	}

	std::string LogFormat(const LogType logType, const char* const firstMessage, const char* const secondMessage, const std::chrono::time_point<std::chrono::system_clock> timePoint)
	{
		return std::format("[{}] [{:%F %R:%OS UTC}] {} - {}\n", ToString(logType), timePoint, firstMessage, secondMessage);
	}

	std::string LogFormat(const LogType logType, const char* const firstMessage, const char* const secondMessage, const std::chrono::time_point<std::chrono::system_clock> timePoint, const std::size_t frameCount)
	{
		return std::format("[{}] [{:%F %R:%OS UTC} ({})] {} - {}\n", ToString(logType), timePoint, frameCount, firstMessage, secondMessage);
	}
}
