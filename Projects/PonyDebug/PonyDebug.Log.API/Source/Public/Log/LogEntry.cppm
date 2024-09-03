/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyDebug/Log/Log.h"

export module PonyDebug.Log:LogEntry;

import <chrono>;
import <cstddef>;
import <exception>;
import <string>;

import :LogFormat;
import :LogConsoleHelper;
import :LogType;

export namespace PonyDebug::Log
{
	/// @brief Information that must be logged.
	class LogEntry final
	{
	public:
		/// @brief Creates a log entry.
		/// @param message Log message.
		/// @param exception Exception.
		/// @param timePoint Time when the log entry has been created.
		/// @param frameCount Frame when the log entry has been created.
		/// @param logType Log type.
		[[nodiscard("Pure constructor")]]
		LogEntry(const char* message, const std::exception* exception, std::chrono::time_point<std::chrono::system_clock> timePoint, std::size_t frameCount, LogType logType) noexcept;
		LogEntry(const LogEntry&) = delete;
		LogEntry(LogEntry&&) = delete;

		~LogEntry() noexcept = default;

		/// @brief Gets the log message.
		/// @return Log message.
		[[nodiscard("Pure function")]]
		const char* Message() const noexcept;
		/// @brief Gets the exception.
		/// @return Exception.
		[[nodiscard("Pure function")]]
		const std::exception* Exception() const noexcept;
		/// @brief Gets the time point.
		/// @return Time point.
		[[nodiscard("Pure function")]]
		std::chrono::time_point<std::chrono::system_clock> TimePoint() const noexcept;
		/// @brief Gets the frame count.
		/// @return Frame count.
		[[nodiscard("Pure function")]]
		std::size_t FrameCount() const noexcept;
		/// @brief Gets the log type.
		/// @return Log type.
		[[nodiscard("Pure function")]]
		LogType LogType() const noexcept;

		/// @brief Creates a string representing this @p LogEntry.
		/// @return Representing string.
		[[nodiscard("Pure function")]]
		const char* ToString() const noexcept;

		LogEntry& operator =(const LogEntry&) = delete;
		LogEntry& operator =(LogEntry&&) = delete;

	private:
		/// @brief Makes a string for the function @p ToString().
		[[nodiscard("Pure function")]]
		std::string MakeString() const noexcept;

		const char* const message; ///< Log message.
		const std::exception* const exception; ///< Exception attached to the log entry.
		const std::chrono::time_point<std::chrono::system_clock> timePoint; ///< Time when the log entry is created.
		const std::size_t frameCount; ///< Frame when the log entry is created.
		const Log::LogType logType; ///< Log type.

		mutable std::string stringCache; ///< ToString() cache.
		mutable bool isDirty; ///< If it's @a true, the cache is invalid.
	};

	/// @brief Puts logEntry.ToString() into the @p stream.
	/// @param stream Target stream.
	/// @param logEntry Input source.
	/// @return @p stream.
	std::ostream& operator <<(std::ostream& stream, const LogEntry& logEntry);
}

namespace PonyDebug::Log
{
	LogEntry::LogEntry(const char* const message, const std::exception* const exception, const std::chrono::time_point<std::chrono::system_clock> timePoint, const std::size_t frameCount, const Log::LogType logType) noexcept :
		message{message},
		exception{exception},
		timePoint{timePoint},
		frameCount{frameCount},
		logType{logType},
		isDirty{true}
	{
	}

	const char* LogEntry::Message() const noexcept
	{
		return message;
	}

	const std::exception* LogEntry::Exception() const noexcept
	{
		return exception;
	}

	std::chrono::time_point<std::chrono::system_clock> LogEntry::TimePoint() const noexcept
	{
		return timePoint;
	}

	std::size_t LogEntry::FrameCount() const noexcept
	{
		return frameCount;
	}

	LogType LogEntry::LogType() const noexcept
	{
		return logType;
	}

	const char* LogEntry::ToString() const noexcept
	{
		if (isDirty)
		{
			stringCache = MakeString();
			isDirty = false;
		}

		return stringCache.c_str();
	}

	std::string LogEntry::MakeString() const noexcept
	{
		try
		{
			if (exception)
			{
				if (message)
				{
					return LogFormat(logType, exception->what(), message, timePoint, frameCount);
				}

				return LogFormat(logType, exception->what(), timePoint, frameCount);
			}
			
			if (message)
			{
				return LogFormat(logType, message, timePoint, frameCount);
			}

			return LogFormat(logType, "", timePoint, frameCount);
		}
		catch (const std::exception& e)
		{
			PONY_CONSOLE_E(e, "On making a log string");
			return std::string();
		}
	}

	std::ostream& operator <<(std::ostream& stream, const LogEntry& logEntry)
	{
		return stream << logEntry.ToString();
	}
}
