/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <cassert>

#include "PonyEngine/Log/LogMacro.h"

export module PonyEngine.Log:LogEntry;

import <chrono>;
import <cstddef>;
import <exception>;
import <format>;
import <iostream>;
import <ostream>;
import <string>;

import :LogType;

export namespace PonyEngine::Log
{
	/// @brief Information that must be logged.
	class LogEntry final
	{
	public:
		/// @brief Creates a log entry.
		/// @param message Log message.
		/// @param exception Exception. Optional - can be nullptr.
		/// @param timePoint Time when the log entry is created.
		/// @param frameCount Frame when the log entry is created.
		/// @param logType Log type. It must be Exception if @p exception isn't nullptr.
		[[nodiscard("Pure constructor")]]
		LogEntry(const char* message, const std::exception* exception, std::chrono::time_point<std::chrono::system_clock> timePoint, std::size_t frameCount, LogType logType) noexcept;
		[[nodiscard("Pure constructor")]]
		LogEntry(const LogEntry& other) = default;
		[[nodiscard("Pure constructor")]]
		LogEntry(LogEntry&& other) noexcept = default;

		~LogEntry() noexcept = default;

		/// @brief Gets the log message.
		/// @return Log message. May be nullptr.
		[[nodiscard("Pure function")]]
		const char* GetMessage() const noexcept;
		/// @brief Gets the exception.
		/// @return Exception. May be nullptr.
		[[nodiscard("Pure function")]]
		const std::exception* GetException() const noexcept;
		/// @brief Gets the time point.
		/// @return Time point.
		[[nodiscard("Pure function")]]
		std::chrono::time_point<std::chrono::system_clock> GetTimePoint() const noexcept;
		/// @brief Gets the frame count.
		/// @return Frame count.
		[[nodiscard("Pure function")]]
		std::size_t GetFrameCount() const noexcept;
		/// @brief Gets the log type.
		/// @return Log type.
		[[nodiscard("Pure function")]]
		LogType GetLogType() const noexcept;

		/// @brief Creates a string representing this @p LogEntry.
		/// @return Representing string.
		[[nodiscard("Pure function")]]
		std::string ToString() const noexcept;

		LogEntry& operator =(const LogEntry& other) = default;
		LogEntry& operator =(LogEntry&& other) noexcept = default;

	private:
		/// @brief Makes a string for the function @p ToString().
		[[nodiscard("Pure function")]]
		std::string MakeString() const noexcept;

		const char* message; ///< Log message.
		const std::exception* exception; ///< Exception attached to the log entry. This field isn't null only when @p logType is @a LogType::Exception.
		std::chrono::time_point<std::chrono::system_clock> timePoint; ///< Time when the log entry is created.
		std::size_t frameCount; ///< Frame when the log entry is created.
		LogType logType; ///< Log type.

		mutable std::string stringCache; ///< ToString() cache.
		mutable bool isDirty; ///< If it's @a true, the cache is invalid.
	};

	/// @brief Puts logEntry.ToString() into the @p stream.
	/// @param stream Target stream.
	/// @param logEntry Input source.
	/// @return @p stream.
	std::ostream& operator <<(std::ostream& stream, const LogEntry& logEntry);
}

namespace PonyEngine::Log
{
	LogEntry::LogEntry(const char* const message, const std::exception* const exception, const std::chrono::time_point<std::chrono::system_clock> timePoint, const std::size_t frameCount, const LogType logType) noexcept :
		message(message),
		exception(exception),
		timePoint(timePoint),
		frameCount{frameCount},
		logType{logType},
		isDirty{true}
	{
		assert(((logType != LogType::Exception && exception == nullptr) || (logType == LogType::Exception && exception != nullptr)));
	}

	const char* LogEntry::GetMessage() const noexcept
	{
		return message;
	}

	const std::exception* LogEntry::GetException() const noexcept
	{
		return exception;
	}

	std::chrono::time_point<std::chrono::system_clock> LogEntry::GetTimePoint() const noexcept
	{
		return timePoint;
	}

	std::size_t LogEntry::GetFrameCount() const noexcept
	{
		return frameCount;
	}

	LogType LogEntry::GetLogType() const noexcept
	{
		return logType;
	}

	std::string LogEntry::ToString() const noexcept
	{
		if (isDirty)
		{
			stringCache = MakeString();
			isDirty = false;
		}

		return stringCache;
	}

	std::string LogEntry::MakeString() const noexcept
	{
		try
		{
			const std::string logTypeString = Log::ToString(logType, false);
			const std::string messageToFormat = exception == nullptr
				? message
				: message == nullptr || *message == '\0'
				? exception->what()
				: std::format("{} - {}", exception->what(), message);

			return std::format("[{}] [{:%F %R:%OS UTC} ({})] {}", logTypeString, timePoint, frameCount, messageToFormat);
		}
		catch (const std::exception& e)
		{
			PONY_CONSOLE(LogType::Exception, std::format("{} - On making a log entry string.", e.what()).c_str());
		}

		return std::string();
	}

	std::ostream& operator <<(std::ostream& stream, const LogEntry& logEntry)
	{
		return stream << logEntry.ToString();
	}
}
