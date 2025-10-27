/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Log.Ext:LogEntry;

import std;

import PonyEngine.Log;

export namespace PonyEngine::Log
{
	/// @brief Information that must be logged.
	class LogEntry final
	{
	public:
		/// @brief Creates a log entry.
		/// @param message Log message.
		/// @param stacktrace Stacktrace.
		/// @param exception Exception.
		/// @param timePoint Time when the log entry has been created.
		/// @param frameCount Frame when the log entry has been created.
		/// @param logType Log type.
		[[nodiscard("Pure constructor")]]
		LogEntry(std::string_view message, const std::stacktrace* stacktrace, const std::exception* exception, std::chrono::time_point<std::chrono::system_clock> timePoint, std::uint64_t frameCount, LogType logType) noexcept;
		LogEntry(const LogEntry&) = delete;
		LogEntry(LogEntry&&) = delete;

		~LogEntry() noexcept = default;

		/// @brief Gets the log message.
		/// @return Log message.
		[[nodiscard("Pure function")]]
		std::string_view Message() const noexcept;
		/// @brief Gets the stacktrace.
		/// @return Stacktrace.
		[[nodiscard("Pure function")]]
		const std::stacktrace* Stacktrace() const noexcept;
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
		std::optional<std::uint64_t> FrameCount() const noexcept;
		/// @brief Gets the log type.
		/// @return Log type.
		[[nodiscard("Pure function")]]
		LogType LogType() const noexcept;

		/// @brief Creates a string representing this @p LogEntry.
		/// @return Representing string.
		[[nodiscard("Pure function")]]
		std::string_view ToString() const noexcept;

		LogEntry& operator =(const LogEntry&) = delete;
		LogEntry& operator =(LogEntry&&) = delete;

	private:
		/// @brief Makes a string for the function @p ToString().
		[[nodiscard("Pure function")]]
		std::string MakeString() const noexcept;

		const std::string_view message; ///< Log message.
		const std::stacktrace* const stacktrace; ///< Stacktrace attached to the log entry.
		const std::exception* const exception; ///< Exception attached to the log entry.
		const std::chrono::time_point<std::chrono::system_clock> timePoint; ///< Time when the log entry is created.
		const std::uint64_t frameCount; ///< Frame when the log entry is created.
		const Log::LogType logType; ///< Log type.

		const std::string logString; ///< Log string.
	};

	/// @brief Puts logEntry.ToString() into the @p stream.
	/// @param stream Target stream.
	/// @param logEntry Input source.
	/// @return @p stream.
	std::ostream& operator <<(std::ostream& stream, const LogEntry& logEntry);
}

/// @brief Log entry formatter.
export template<>
struct std::formatter<PonyEngine::Log::LogEntry, char>
{
	static constexpr auto parse(std::format_parse_context& context)
	{
		if (context.begin() == context.end()) [[unlikely]]
		{
			throw std::format_error("Unexpected context end.");
		}
		if (*context.begin() != '}') [[unlikely]]
		{
			throw std::format_error("Unexpected format specifier.");
		}

		return context.begin();
	}

	static auto format(const PonyEngine::Log::LogEntry& entry, std::format_context& context)
	{
		return std::ranges::copy(entry.ToString(), context.out()).out;
	}
};

namespace PonyEngine::Log
{
	LogEntry::LogEntry(const std::string_view message, const std::stacktrace* const stacktrace, const std::exception* const exception, const std::chrono::time_point<std::chrono::system_clock> timePoint, const std::uint64_t frameCount, const Log::LogType logType) noexcept :
		message{message},
		stacktrace{stacktrace},
		exception{exception},
		timePoint{timePoint},
		frameCount{frameCount},
		logType{logType},
		logString(MakeString())
	{
	}

	std::string_view LogEntry::Message() const noexcept
	{
		return message;
	}

	const std::stacktrace* LogEntry::Stacktrace() const noexcept
	{
		return stacktrace;
	}

	const std::exception* LogEntry::Exception() const noexcept
	{
		return exception;
	}

	std::chrono::time_point<std::chrono::system_clock> LogEntry::TimePoint() const noexcept
	{
		return timePoint;
	}

	std::optional<std::uint64_t> LogEntry::FrameCount() const noexcept
	{
		return frameCount;
	}

	LogType LogEntry::LogType() const noexcept
	{
		return logType;
	}

	std::string_view LogEntry::ToString() const noexcept
	{
		return logString;
	}

	std::string LogEntry::MakeString() const noexcept
	{
		switch ((stacktrace != nullptr) << 2 | !message.empty() << 1 | (exception != nullptr) << 0)
		{
		case 0:
			return LogFormat(logType, message, timePoint, frameCount);
		case 1:
			return LogFormat(logType, exception->what(), timePoint, frameCount);
		case 2:
			return LogFormat(logType, message, timePoint, frameCount);
		case 3:
			return LogFormat(logType, exception->what(), message, timePoint, frameCount);
		case 4:
			return LogFormat(logType, message, timePoint, frameCount, *stacktrace);
		case 5:
			return LogFormat(logType, exception->what(), timePoint, frameCount, *stacktrace);
		case 6:
			return LogFormat(logType, message, timePoint, frameCount, *stacktrace);
		case 7:
			return LogFormat(logType, exception->what(), message, timePoint, frameCount, *stacktrace);
		default: [[unlikely]]
			return LogFormat(logType, exception ? exception->what() : "Unknown exception", message.empty() ? "Unknown message" : message, timePoint, frameCount);
		}
	}

	std::ostream& operator <<(std::ostream& stream, const LogEntry& logEntry)
	{
		return stream << logEntry.ToString();
	}
}
