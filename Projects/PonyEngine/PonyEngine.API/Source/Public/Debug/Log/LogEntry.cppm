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

#include "Debug/Log/LogMacro.h"

export module PonyEngine.Debug.Log:LogEntry;

import <chrono>;
import <cstddef>;
import <exception>;
import <format>;
import <iostream>;
import <ostream>;
import <string>;

import :LogType;

namespace PonyEngine::Debug::Log
{
	/// @brief Information that must be logged.
	export class LogEntry final
	{
	public:
		/// @brief Creates a log entry.
		/// @param message Log message.
		/// @param timePoint Time when the log entry is created.
		/// @param frameCount Frame when the log entry is created.
		/// @param logType Log type.
		[[nodiscard("Pure constructor")]]
		LogEntry(const char* message, const std::exception* exception, std::chrono::time_point<std::chrono::system_clock> timePoint, std::size_t frameCount, LogType logType) noexcept;
		[[nodiscard("Pure constructor")]]
		LogEntry(const LogEntry& other) = default;
		[[nodiscard("Pure constructor")]]
		LogEntry(LogEntry&& other) noexcept = default;

		~LogEntry() noexcept = default;

		/// @brief Gets a log message.
		/// @return Log message. May be nullptr.
		[[nodiscard("Pure function")]]
		inline const char* GetMessage() const noexcept;
		/// @brief Gets an exception.
		/// @return Exception. May be nullptr.
		[[nodiscard("Pure function")]]
		inline const std::exception* GetException() const noexcept;
		/// @brief Gets a time point.
		/// @return Time point.
		[[nodiscard("Pure function")]]
		inline std::chrono::time_point<std::chrono::system_clock> GetTimePoint() const noexcept;
		/// @brief Gets a frame count.
		/// @return Frame count.
		[[nodiscard("Pure function")]]
		inline std::size_t GetFrameCount() const noexcept;
		/// @brief Gets a log type.
		/// @return Log type.
		[[nodiscard("Pure function")]]
		inline LogType GetLogType() const noexcept;

		/// @brief Creates a string representing this @p LogEntry.
		/// @return Created string.
		[[nodiscard("Pure function")]]
		std::string ToString() const noexcept;

		LogEntry& operator =(const LogEntry& other) = default;
		LogEntry& operator =(LogEntry&& other) noexcept = default;

	private:
		/// @brief Makes a string for the function ToString().
		[[nodiscard("Pure function")]]
		std::string MakeString() const noexcept;

		const char* const m_message; /// @brief Log message.
		const std::exception* const m_exception; /// @brief Exception attached to the log entry. This field isn't null only when @p logType is @a LogType::Exception.
		const std::chrono::time_point<std::chrono::system_clock> m_timePoint; /// @brief Time when the log entry is created.
		const std::size_t m_frameCount; /// @brief Frame when the log entry is created.
		const LogType m_logType; /// @brief Log type.

		mutable std::string m_stringCache; /// @brief ToString() cache.
		mutable bool m_isDirty; /// @brief If it's @a true, the cache is invalid.
	};

	/// @brief Puts logEntry.ToString() into the @p stream.
	/// @param stream Target stream.
	/// @param logEntry Input source.
	/// @return @p stream.
	export inline std::ostream& operator <<(std::ostream& stream, const LogEntry& logEntry);

	inline std::ostream& operator <<(std::ostream& stream, const LogEntry& logEntry)
	{
		return stream << logEntry.ToString();
	}

	LogEntry::LogEntry(const char* const message, const std::exception* const exception, const std::chrono::time_point<std::chrono::system_clock> timePoint, const std::size_t frameCount, const LogType logType) noexcept :
		m_message(message),
		m_exception(exception),
		m_timePoint(timePoint),
		m_frameCount{frameCount},
		m_logType{logType},
		m_stringCache(),
		m_isDirty{true}
	{
		assert(((logType != LogType::Exception && exception == nullptr) || (logType == LogType::Exception && exception != nullptr)));
	}

	inline const char* LogEntry::GetMessage() const noexcept
	{
		return m_message;
	}

	inline const std::exception* LogEntry::GetException() const noexcept
	{
		return m_exception;
	}

	inline std::chrono::time_point<std::chrono::system_clock> LogEntry::GetTimePoint() const noexcept
	{
		return m_timePoint;
	}

	inline std::size_t LogEntry::GetFrameCount() const noexcept
	{
		return m_frameCount;
	}

	inline LogType LogEntry::GetLogType() const noexcept
	{
		return m_logType;
	}

	std::string LogEntry::ToString() const noexcept
	{
		if (m_isDirty)
		{
			m_stringCache = MakeString();
			m_isDirty = false;
		}

		return m_stringCache;
	}

	std::string LogEntry::MakeString() const noexcept
	{
		try
		{
			const std::string logTypeString = Log::ToString(m_logType, false);
			const std::string messageToFormat = m_exception == nullptr
				? m_message
				: m_message == nullptr || *m_message == '\0'
				? m_exception->what()
				: std::format("{} - {}", m_exception->what(), m_message);

			return std::format("[{}] [{:%F %R:%OS UTC} ({})] {}", logTypeString, m_timePoint, m_frameCount, messageToFormat);
		}
		catch (const std::exception& e)
		{
			PONY_CONSOLE(LogType::Exception, std::format("{} - {}.", e.what(), "On making a log entry string").c_str());
		}

		return std::string();
	}
}
