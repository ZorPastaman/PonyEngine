/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Log:LogFormat;

import std;

import PonyEngine.Utility;

import :LogType;

export namespace PonyEngine::Log
{
	/// @brief Formats a log string.
	/// @param logType Log type.
	/// @param message Log message.
	/// @return Formatted log string.
	[[nodiscard("Pure function")]]
	std::string LogFormat(LogType logType, std::string_view message) noexcept;
	/// @brief Formats a log string.
	/// @param logType Log type.
	/// @param message Log message.
	/// @param timePoint Time when the log has been created. Must be UTC.
	/// @return Formatted log string.
	[[nodiscard("Pure function")]]
	std::string LogFormat(LogType logType, std::string_view message, std::chrono::time_point<std::chrono::system_clock> timePoint) noexcept;
	/// @brief Formats a log string.
	/// @param logType Log type.
	/// @param message Log message.
	/// @param timePoint Time when the log has been created. Must be UTC.
	/// @param frameCount Frame when the log has been created.
	/// @return Formatted log string.
	[[nodiscard("Pure function")]]
	std::string LogFormat(LogType logType, std::string_view message, std::chrono::time_point<std::chrono::system_clock> timePoint, std::uint64_t frameCount) noexcept;
	/// @brief Formats a log string.
	/// @param logType Log type.
	/// @param firstMessage First log message.
	/// @param secondMessage Second log message.
	/// @return Formatted log string.
	[[nodiscard("Pure function")]]
	std::string LogFormat(LogType logType, std::string_view firstMessage, std::string_view secondMessage) noexcept;
	/// @brief Formats a log string.
	/// @param logType Log type.
	/// @param firstMessage First log message.
	/// @param secondMessage Second log message.
	/// @param timePoint Time when the log has been created. Must be UTC.
	/// @return Formatted log string.
	[[nodiscard("Pure function")]]
	std::string LogFormat(LogType logType, std::string_view firstMessage, std::string_view secondMessage, std::chrono::time_point<std::chrono::system_clock> timePoint) noexcept;
	/// @brief Formats a log string.
	/// @param logType Log type.
	/// @param firstMessage First log message.
	/// @param secondMessage Second log message.
	/// @param timePoint Time when the log has been created. Must be UTC.
	/// @param frameCount Frame when the log has been created.
	/// @return Formatted log string.
	[[nodiscard("Pure function")]]
	std::string LogFormat(LogType logType, std::string_view firstMessage, std::string_view secondMessage, std::chrono::time_point<std::chrono::system_clock> timePoint, std::uint64_t frameCount) noexcept;
	/// @brief Formats a log string.
	/// @param logType Log type.
	/// @param message Log message.
	/// @param stacktrace Stacktrace.
	/// @return Formatted log string.
	[[nodiscard("Pure function")]]
	std::string LogFormat(LogType logType, std::string_view message, const std::stacktrace& stacktrace) noexcept;
	/// @brief Formats a log string.
	/// @param logType Log type.
	/// @param message Log message.
	/// @param timePoint Time when the log has been created. Must be UTC.
	/// @param stacktrace Stacktrace.
	/// @return Formatted log string.
	[[nodiscard("Pure function")]]
	std::string LogFormat(LogType logType, std::string_view message, std::chrono::time_point<std::chrono::system_clock> timePoint, const std::stacktrace& stacktrace) noexcept;
	/// @brief Formats a log string.
	/// @param logType Log type.
	/// @param message Log message.
	/// @param timePoint Time when the log has been created. Must be UTC.
	/// @param frameCount Frame when the log has been created.
	/// @param stacktrace Stacktrace.
	/// @return Formatted log string.
	[[nodiscard("Pure function")]]
	std::string LogFormat(LogType logType, std::string_view message, std::chrono::time_point<std::chrono::system_clock> timePoint, std::uint64_t frameCount, const std::stacktrace& stacktrace) noexcept;
	/// @brief Formats a log string.
	/// @param logType Log type.
	/// @param firstMessage First log message.
	/// @param secondMessage Second log message.
	/// @param stacktrace Stacktrace.
	/// @return Formatted log string.
	[[nodiscard("Pure function")]]
	std::string LogFormat(LogType logType, std::string_view firstMessage, std::string_view secondMessage, const std::stacktrace& stacktrace) noexcept;
	/// @brief Formats a log string.
	/// @param logType Log type.
	/// @param firstMessage First log message.
	/// @param secondMessage Second log message.
	/// @param timePoint Time when the log has been created. Must be UTC.
	/// @param stacktrace Stacktrace.
	/// @return Formatted log string.
	[[nodiscard("Pure function")]]
	std::string LogFormat(LogType logType, std::string_view firstMessage, std::string_view secondMessage, std::chrono::time_point<std::chrono::system_clock> timePoint, const std::stacktrace& stacktrace) noexcept;
	/// @brief Formats a log string.
	/// @param logType Log type.
	/// @param firstMessage First log message.
	/// @param secondMessage Second log message.
	/// @param timePoint Time when the log has been created. Must be UTC.
	/// @param frameCount Frame when the log has been created.
	/// @param stacktrace Stacktrace.
	/// @return Formatted log string.
	[[nodiscard("Pure function")]]
	std::string LogFormat(LogType logType, std::string_view firstMessage, std::string_view secondMessage, std::chrono::time_point<std::chrono::system_clock> timePoint, std::uint64_t frameCount, const std::stacktrace& stacktrace) noexcept;

}

namespace PonyEngine::Log
{
	std::string LogFormat(const LogType logType, const std::string_view message) noexcept
	{
		return Utility::SafeFormat("[{}] {}\n", logType, message);
	}

	std::string LogFormat(const LogType logType, const std::string_view message, const std::chrono::time_point<std::chrono::system_clock> timePoint) noexcept
	{
		return Utility::SafeFormat("[{}] [{:%F %R:%OS UTC}] {}\n", logType, timePoint, message);
	}

	std::string LogFormat(const LogType logType, const std::string_view message, const std::chrono::time_point<std::chrono::system_clock> timePoint, const std::uint64_t frameCount) noexcept
	{
		return Utility::SafeFormat("[{}] [{:%F %R:%OS UTC} ({})] {}\n", logType, timePoint, frameCount, message);
	}

	std::string LogFormat(const LogType logType, const std::string_view firstMessage, const std::string_view secondMessage) noexcept
	{
		return Utility::SafeFormat("[{}] {} - {}\n", logType, firstMessage, secondMessage);
	}

	std::string LogFormat(const LogType logType, const std::string_view firstMessage, const std::string_view secondMessage, const std::chrono::time_point<std::chrono::system_clock> timePoint) noexcept
	{
		return Utility::SafeFormat("[{}] [{:%F %R:%OS UTC}] {} - {}\n", logType, timePoint, firstMessage, secondMessage);
	}

	std::string LogFormat(const LogType logType, const std::string_view firstMessage, const std::string_view secondMessage, const std::chrono::time_point<std::chrono::system_clock> timePoint, const std::uint64_t frameCount) noexcept
	{
		return Utility::SafeFormat("[{}] [{:%F %R:%OS UTC} ({})] {} - {}\n", logType, timePoint, frameCount, firstMessage, secondMessage);
	}

	std::string LogFormat(const LogType logType, const std::string_view message, const std::stacktrace& stacktrace) noexcept
	{
		return Utility::SafeFormat("[{}] {}\n{}\n", logType, message, stacktrace);
	}

	std::string LogFormat(const LogType logType, const std::string_view message, const std::chrono::time_point<std::chrono::system_clock> timePoint, const std::stacktrace& stacktrace) noexcept
	{
		return Utility::SafeFormat("[{}] [{:%F %R:%OS UTC}] {}\n{}\n", logType, timePoint, message, stacktrace);
	}

	std::string LogFormat(const LogType logType, const std::string_view message, const std::chrono::time_point<std::chrono::system_clock> timePoint, const std::uint64_t frameCount, const std::stacktrace& stacktrace) noexcept
	{
		return Utility::SafeFormat("[{}] [{:%F %R:%OS UTC} ({})] {}\n{}\n", logType, timePoint, frameCount, message, stacktrace);
	}

	std::string LogFormat(const LogType logType, const std::string_view firstMessage, const std::string_view secondMessage, const std::stacktrace& stacktrace) noexcept
	{
		return Utility::SafeFormat("[{}] {} - {}\n{}\n", logType, firstMessage, secondMessage, stacktrace);
	}

	std::string LogFormat(const LogType logType, const std::string_view firstMessage, const std::string_view secondMessage, const std::chrono::time_point<std::chrono::system_clock> timePoint, const std::stacktrace& stacktrace) noexcept
	{
		return Utility::SafeFormat("[{}] [{:%F %R:%OS UTC}] {} - {}\n{}\n", logType, timePoint, firstMessage, secondMessage, stacktrace);
	}

	std::string LogFormat(const LogType logType, const std::string_view firstMessage, const std::string_view secondMessage, const std::chrono::time_point<std::chrono::system_clock> timePoint, const std::uint64_t frameCount, const std::stacktrace& stacktrace) noexcept
	{
		return Utility::SafeFormat("[{}] [{:%F %R:%OS UTC} ({})] {} - {}\n{}\n", logType, timePoint, frameCount, firstMessage, secondMessage, stacktrace);
	}
}
