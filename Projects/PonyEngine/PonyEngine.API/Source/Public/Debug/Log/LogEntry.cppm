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
		LogEntry(const LogEntry& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		LogEntry(LogEntry&& other) noexcept = default;

		~LogEntry() noexcept = default;

		/// @brief Gets a log message.
		/// @return Log message. May be nullptr.
		[[nodiscard("Pure function")]]
		inline const char* GetMessage() const noexcept;
		/// @brief Sets a log message.
		/// @param message Log message to set.
		inline void SetMessage(const char* message) noexcept;

		/// @brief Gets an exception.
		/// @return Exception. May be nullptr.
		[[nodiscard("Pure function")]]
		inline const std::exception* GetException() const noexcept;
		/// @brief Sets an exception.
		/// @param exception Exception to set.
		inline void SetException(const std::exception* exception) noexcept;

		/// @brief Gets a time point.
		/// @return Time point.
		[[nodiscard("Pure function")]]
		inline std::chrono::time_point<std::chrono::system_clock> GetTimePoint() const noexcept;
		/// @brief Sets a time point.
		/// @param timePoint Time point to set.
		inline void SetTimePoint(std::chrono::time_point<std::chrono::system_clock> timePoint) noexcept;

		/// @brief Gets a frame count.
		/// @return Frame count.
		[[nodiscard("Pure function")]]
		inline std::size_t GetFrameCount() const noexcept;
		/// @brief Sets a frame count.
		/// @param frameCount Frame count to set.
		inline void SetFrameCount(std::size_t frameCount) noexcept;

		/// @brief Gets a log type.
		/// @return Log type.
		[[nodiscard("Pure function")]]
		inline LogType GetLogType() const noexcept;
		/// @brief Sets a log type.
		/// @param logType Log type to set.
		inline void SetLogType(LogType logType) noexcept;

		/// @brief Creates a string representing this @p LogEntry.
		/// @return Created string.
		[[nodiscard("Pure function")]]
		std::string ToString() const noexcept;

		LogEntry& operator =(const LogEntry& other) noexcept = default;

	private:
		void MakeString() const noexcept;

		const char* m_message; /// @brief Log message.
		const std::exception* m_exception; /// @brief Exception attached to the log entry. This field isn't null only when @p logType is @a LogType::Exception.
		std::chrono::time_point<std::chrono::system_clock> m_timePoint; /// @brief Time when the log entry is created.
		std::size_t m_frameCount; /// @brief Frame when the log entry is created.
		LogType m_logType; /// @brief Log type.

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

	inline void LogEntry::SetMessage(const char* const message) noexcept
	{
		m_message = message;
		m_isDirty = true;
	}

	inline const std::exception* LogEntry::GetException() const noexcept
	{
		return m_exception;
	}

	inline void LogEntry::SetException(const std::exception* const exception) noexcept
	{
		m_exception = exception;
		m_isDirty = true;
	}

	inline std::chrono::time_point<std::chrono::system_clock> LogEntry::GetTimePoint() const noexcept
	{
		return m_timePoint;
	}

	inline void LogEntry::SetTimePoint(const std::chrono::time_point<std::chrono::system_clock> timePoint) noexcept
	{
		m_timePoint = timePoint;
		m_isDirty = true;
	}

	inline std::size_t LogEntry::GetFrameCount() const noexcept
	{
		return m_frameCount;
	}

	inline void LogEntry::SetFrameCount(const std::size_t frameCount) noexcept
	{
		m_frameCount = frameCount;
		m_isDirty = true;
	}

	inline LogType LogEntry::GetLogType() const noexcept
	{
		return m_logType;
	}

	inline void LogEntry::SetLogType(const LogType logType) noexcept
	{
		m_logType = logType;
		m_isDirty = true;
	}

	std::string LogEntry::ToString() const noexcept
	{
		if (m_isDirty)
		{
			MakeString();
			m_isDirty = false;
		}

		return m_stringCache;
	}

	void LogEntry::MakeString() const noexcept
	{
		try
		{
			try
			{
				const std::string logTypeString = Log::ToString(m_logType, false);
				const std::string messageToFormat = m_exception == nullptr
					? m_message
					: m_message == nullptr || *m_message == '\0'
						? m_exception->what()
						: std::format("{} - {}", m_exception->what(), m_message);
				m_stringCache = std::format("[{}] [{:%F %R:%OS UTC} ({})] {}", logTypeString, m_timePoint, m_frameCount, messageToFormat);
			}
			catch (const std::exception& e)
			{
				PONY_CONSOLE(LogType::Exception, e.what());
				m_stringCache = "";
			}
		}
		catch (const std::exception& e)
		{
			m_stringCache = "";
		}
	}
}
