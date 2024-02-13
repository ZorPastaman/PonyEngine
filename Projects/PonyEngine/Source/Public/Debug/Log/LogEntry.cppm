/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Debug.Log:LogEntry;

import <cassert>;
import <chrono>;
import <cstddef>;
import <exception>;
import <format>;
import <ostream>;
import <string>;

import :LogType;

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
		[[nodiscard("Pure constructor")]]
		LogEntry(const std::string& message, const std::exception* exception, std::chrono::time_point<std::chrono::system_clock> timePoint, std::size_t frameCount, LogType logType) noexcept;

		~LogEntry() noexcept = default;

		/// @brief Creates a string representing this @p LogEntry.
		/// @return Created string.
		[[nodiscard("Pure function")]]
		std::string ToString() const;

		const std::string& message; /// @brief Log message.
		const std::exception* const exception; /// @brief Exception attached to the log entry. This field isn't null only when @p logType is @a LogType::Exception.
		std::chrono::time_point<std::chrono::system_clock> timePoint; /// @brief Time when the log entry is created.
		std::size_t frameCount; /// @brief Frame when the log entry is created.
		LogType logType; /// @brief Log type.
	};

	/// @brief Puts logEntry.ToString() into the @p stream.
	/// @param stream Target stream.
	/// @param logEntry Input source.
	/// @return @p stream.
	export [[nodiscard("Pure function")]]
	inline std::ostream& operator <<(std::ostream& stream, const LogEntry& logEntry);

	inline std::ostream& operator <<(std::ostream& stream, const LogEntry& logEntry)
	{
		return stream << logEntry.ToString();
	}

	LogEntry::LogEntry(const std::string& message, const std::exception* const exception, std::chrono::time_point<std::chrono::system_clock> timePoint, std::size_t frameCount, LogType logType) noexcept :
		message(message),
		exception(exception),
		timePoint(timePoint),
		frameCount{frameCount},
		logType{logType}
	{
		assert(((logType != LogType::Exception && exception == nullptr) || (logType == LogType::Exception && exception != nullptr)));
	}

	std::string LogEntry::ToString() const
	{
		std::string messageOut;
		if (exception != nullptr)
		{
			if (message.empty())
			{
				messageOut = exception->what();
			}
			else
			{
				messageOut = std::format("{} - {}", exception->what(), message);
			}
		}
		else
		{
			messageOut = message;
		}

		return std::format("[{}] [{:%F %R:%OS UTC} ({})] {}.", PonyEngine::Debug::Log::ToString(logType, false), timePoint, frameCount, messageOut);
	}
}
