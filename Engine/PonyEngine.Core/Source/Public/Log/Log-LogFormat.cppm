/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: cybercode.smith@pm.me                    *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <cstdint>
#include <chrono>
#include <format>
#include <string>
#include <string_view>

export module PonyEngine.Log:LogFormat;

import :LogType;

export namespace PonyEngine::Log
{
	/// @brief Formats a log string.
	/// @param logType Log type.
	/// @param timePoint Time when the log has been created. Must be UTC.
	/// @return Formatted log string.
	[[nodiscard("Pure function")]]
	std::string LogFormat(LogType logType, std::chrono::time_point<std::chrono::system_clock> timePoint);
	/// @brief Formats a log string.
	/// @param logType Log type.
	/// @param timePoint Time when the log has been created. Must be UTC.
	/// @param frameCount Frame when the log has been created.
	/// @return Formatted log string.
	[[nodiscard("Pure function")]]
	std::string LogFormat(LogType logType, std::chrono::time_point<std::chrono::system_clock> timePoint, std::uint64_t frameCount);
	/// @brief Formats a log string.
	/// @param logType Log type.
	/// @param message Log message.
	/// @param timePoint Time when the log has been created. Must be UTC.
	/// @return Formatted log string.
	[[nodiscard("Pure function")]]
	std::string LogFormat(LogType logType, std::string_view message, std::chrono::time_point<std::chrono::system_clock> timePoint);
	/// @brief Formats a log string.
	/// @param logType Log type.
	/// @param message Log message.
	/// @param timePoint Time when the log has been created. Must be UTC.
	/// @param frameCount Frame when the log has been created.
	/// @return Formatted log string.
	[[nodiscard("Pure function")]]
	std::string LogFormat(LogType logType, std::string_view message, std::chrono::time_point<std::chrono::system_clock> timePoint, std::uint64_t frameCount);
	/// @brief Formats a log string.
	/// @param logType Log type.
	/// @param firstMessage First log message.
	/// @param secondMessage Second log message.
	/// @param timePoint Time when the log has been created. Must be UTC.
	/// @return Formatted log string.
	[[nodiscard("Pure function")]]
	std::string LogFormat(LogType logType, std::string_view firstMessage, std::string_view secondMessage, std::chrono::time_point<std::chrono::system_clock> timePoint);
	/// @brief Formats a log string.
	/// @param logType Log type.
	/// @param firstMessage First log message.
	/// @param secondMessage Second log message.
	/// @param timePoint Time when the log has been created. Must be UTC.
	/// @param frameCount Frame when the log has been created.
	/// @return Formatted log string.
	[[nodiscard("Pure function")]]
	std::string LogFormat(LogType logType, std::string_view firstMessage, std::string_view secondMessage, std::chrono::time_point<std::chrono::system_clock> timePoint, std::uint64_t frameCount);

}

namespace PonyEngine::Log
{
	std::string LogFormat(const LogType logType, const std::chrono::time_point<std::chrono::system_clock> timePoint)
	{
		return std::format("[{}] [{:%F %R:%OS UTC}]\n", logType, timePoint);
	}

	std::string LogFormat(const LogType logType, const std::chrono::time_point<std::chrono::system_clock> timePoint, const std::uint64_t frameCount)
	{
		return std::format("[{}] [{:%F %R:%OS UTC} ({})]\n", logType, timePoint, frameCount);
	}

	std::string LogFormat(const LogType logType, const std::string_view message, const std::chrono::time_point<std::chrono::system_clock> timePoint)
	{
		return std::format("[{}] [{:%F %R:%OS UTC}] {}\n", logType, timePoint, message);
	}

	std::string LogFormat(const LogType logType, const std::string_view message, const std::chrono::time_point<std::chrono::system_clock> timePoint, const std::uint64_t frameCount)
	{
		return std::format("[{}] [{:%F %R:%OS UTC} ({})] {}\n", logType, timePoint, frameCount, message);
	}

	std::string LogFormat(const LogType logType, const std::string_view firstMessage, const std::string_view secondMessage, const std::chrono::time_point<std::chrono::system_clock> timePoint)
	{
		return std::format("[{}] [{:%F %R:%OS UTC}] {} - {}\n", logType, timePoint, firstMessage, secondMessage);
	}

	std::string LogFormat(const LogType logType, const std::string_view firstMessage, const std::string_view secondMessage, const std::chrono::time_point<std::chrono::system_clock> timePoint, const std::uint64_t frameCount)
	{
		return std::format("[{}] [{:%F %R:%OS UTC} ({})] {} - {}\n", logType, timePoint, frameCount, firstMessage, secondMessage);
	}
}
