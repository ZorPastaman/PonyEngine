/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Log.Impl:LogFiller;

import std;

import PonyEngine.Application.Ext;
import PonyEngine.Log.Ext;

import :LogTypeSymbol;

export namespace PonyEngine::Log
{
	/// @brief Fills a time data.
	/// @param timePoint Time point.
	/// @param frameCount Frame count.
	/// @param context Logger context.
	void FillTime(std::chrono::time_point<std::chrono::system_clock>& timePoint, std::uint64_t& frameCount, const Application::ILoggerContext& context) noexcept;

	/// @brief Fills a log header.
	/// @param target Log target.
	/// @param logType Log type.
	/// @param timePoint Time point.
	/// @param frameCount Frame count.
	void FillHeader(std::string& target, LogType logType, std::chrono::time_point<std::chrono::system_clock> timePoint, std::uint64_t frameCount);

	/// @brief Fills a log message.
	/// @param target Log target.
	/// @param message Log message.
	/// @return Log message start and end indices in the target.
	std::pair<std::size_t, std::size_t> FillMessage(std::string& target, std::string_view message);
	/// @brief Fills a log message.
	/// @param target Log target.
	/// @param format Log message format.
	/// @param formatArgs Log message format arguments.
	/// @return Log message start and end indices in the target.
	std::pair<std::size_t, std::size_t> FillMessage(std::string& target, std::string_view format, std::format_args formatArgs);

	/// @brief Fills a log message.
	/// @param target Log target.
	/// @param exception Exception.
	/// @return Log message start and end indices in the target.
	std::pair<std::size_t, std::size_t> FillMessage(std::string& target, const std::optional<const std::exception*>& exception);

	/// @brief Fills a complete log text.
	/// @param targetString Log target.
	/// @param logType Log type.
	/// @param timePoint Time point.
	/// @param frameCount Frame count.
	/// @param message Log message.
	/// @return Message view in the target string.
	std::string_view FillText(std::string& targetString, LogType logType, std::chrono::time_point<std::chrono::system_clock> timePoint, std::uint64_t frameCount, 
		std::string_view message);
	/// @brief Fills a complete log text.
	/// @param targetString Log target.
	/// @param logType Log type.
	/// @param timePoint Time point.
	/// @param frameCount Frame count.
	/// @param format Log message format.
	/// @param formatArgs Log message format arguments.
	/// @return Message view in the target string.
	std::string_view FillText(std::string& targetString, LogType logType, std::chrono::time_point<std::chrono::system_clock> timePoint, std::uint64_t frameCount,
		std::string_view format, std::format_args formatArgs);
	/// @brief Fills a complete log text.
	/// @param targetString Log target.
	/// @param logType Log type.
	/// @param timePoint Time point.
	/// @param frameCount Frame count.
	/// @param message Log message.
	/// @param stacktrace Stacktrace.
	/// @return Message view in the target string.
	std::string_view FillText(std::string& targetString, LogType logType, std::chrono::time_point<std::chrono::system_clock> timePoint, std::uint64_t frameCount,
		std::string_view message, const std::stacktrace& stacktrace);
	/// @brief Fills a complete log text.
	/// @param targetString Log target.
	/// @param logType Log type.
	/// @param timePoint Time point.
	/// @param frameCount Frame count.
	/// @param format Log message format.
	/// @param formatArgs Log message format arguments.
	/// @param stacktrace Stacktrace.
	/// @return Message view in the target string.
	std::string_view FillText(std::string& targetString, LogType logType, std::chrono::time_point<std::chrono::system_clock> timePoint, std::uint64_t frameCount,
		std::string_view format, std::format_args formatArgs, const std::stacktrace& stacktrace);

	/// @brief Fills a complete log text.
	/// @param targetString Log target.
	/// @param timePoint Time point.
	/// @param frameCount Frame count.
	/// @param exception Exception.
	/// @return Message view in the target string.
	std::string_view FillText(std::string& targetString, std::chrono::time_point<std::chrono::system_clock> timePoint, std::uint64_t frameCount,
		const std::optional<const std::exception*>& exception);
	/// @brief Fills a complete log text.
	/// @param targetString Log target.
	/// @param timePoint Time point.
	/// @param frameCount Frame count.
	/// @param exception Exception.
	/// @param message Log message.
	/// @return Message view in the target string.
	std::string_view FillText(std::string& targetString, std::chrono::time_point<std::chrono::system_clock> timePoint, std::uint64_t frameCount,
		const std::optional<const std::exception*>& exception, std::string_view message);
	/// @brief Fills a complete log text.
	/// @param targetString Log target.
	/// @param timePoint Time point.
	/// @param frameCount Frame count.
	/// @param exception Exception.
	/// @param format Log message format.
	/// @param formatArgs Log message format arguments.
	/// @return Message view in the target string.
	std::string_view FillText(std::string& targetString, std::chrono::time_point<std::chrono::system_clock> timePoint, std::uint64_t frameCount,
		const std::optional<const std::exception*>& exception, std::string_view format, std::format_args formatArgs);
	/// @brief Fills a complete log text.
	/// @param targetString Log target.
	/// @param timePoint Time point.
	/// @param frameCount Frame count.
	/// @param exception Exception.
	/// @param stacktrace Stacktrace.
	/// @return Message view in the target string.
	std::string_view FillText(std::string& targetString, std::chrono::time_point<std::chrono::system_clock> timePoint, std::uint64_t frameCount,
		const std::optional<const std::exception*>& exception, const std::stacktrace& stacktrace);
	/// @brief Fills a complete log text.
	/// @param targetString Log target.
	/// @param timePoint Time point.
	/// @param frameCount Frame count.
	/// @param exception Exception.
	/// @param message Log message.
	/// @param stacktrace Stacktrace.
	/// @return Message view in the target string.
	std::string_view FillText(std::string& targetString, std::chrono::time_point<std::chrono::system_clock> timePoint, std::uint64_t frameCount,
		const std::optional<const std::exception*>& exception, std::string_view message, const std::stacktrace& stacktrace);
	/// @brief Fills a complete log text.
	/// @param targetString Log target.
	/// @param timePoint Time point.
	/// @param frameCount Frame count.
	/// @param exception Exception.
	/// @param format Log message format.
	/// @param formatArgs Log message format arguments.
	/// @param stacktrace Stacktrace.
	/// @return Message view in the target string.
	std::string_view FillText(std::string& targetString, std::chrono::time_point<std::chrono::system_clock> timePoint, std::uint64_t frameCount,
		const std::optional<const std::exception*>& exception, std::string_view format, std::format_args formatArgs, const std::stacktrace& stacktrace);

	/// @brief Fills log data.
	/// @param targetEntry Log entry.
	/// @param targetString Log target.
	/// @param logType Log type.
	/// @param message Log message.
	/// @param context Logger context.
	void FillData(LogEntry& targetEntry, std::string& targetString, LogType logType, std::string_view message, 
		const Application::ILoggerContext& context) noexcept;
	/// @brief Fills log data.
	/// @param targetEntry Log entry.
	/// @param targetString Log target.
	/// @param logType Log type.
	/// @param format Log message format.
	/// @param formatArgs Log message format arguments.
	/// @param context Logger context.
	void FillData(LogEntry& targetEntry, std::string& targetString, LogType logType, std::string_view format, std::format_args formatArgs, 
		const Application::ILoggerContext& context) noexcept;
	/// @brief Fills log data.
	/// @param targetEntry Log entry.
	/// @param targetString Log target.
	/// @param logType Log type.
	/// @param message Log message.
	/// @param stacktrace Stacktrace.
	/// @param context Logger context.
	void FillData(LogEntry& targetEntry, std::string& targetString, LogType logType, std::string_view message, const std::stacktrace& stacktrace, 
		const Application::ILoggerContext& context) noexcept;
	/// @brief Fills log data.
	/// @param targetEntry Log entry.
	/// @param targetString Log target.
	/// @param logType Log type.
	/// @param format Log message format.
	/// @param formatArgs Log message format arguments.
	/// @param stacktrace Stacktrace.
	/// @param context Logger context.
	void FillData(LogEntry& targetEntry, std::string& targetString, LogType logType, std::string_view format, std::format_args formatArgs, const std::stacktrace& stacktrace,
		const Application::ILoggerContext& context) noexcept;

	/// @brief Fills log data.
	/// @param targetEntry Log entry.
	/// @param targetString Log target.
	/// @param exception Exception.
	/// @param context Logger context.
	void FillData(LogEntry& targetEntry, std::string& targetString, const std::exception_ptr& exception, const Application::ILoggerContext& context) noexcept;
	/// @brief Fills log data.
	/// @param targetEntry Log entry.
	/// @param targetString Log target.
	/// @param exception Exception.
	/// @param message Log message.
	/// @param context Logger context.
	void FillData(LogEntry& targetEntry, std::string& targetString, const std::exception_ptr& exception, std::string_view message,
		const Application::ILoggerContext& context) noexcept;
	/// @brief Fills log data.
	/// @param targetEntry Log entry.
	/// @param targetString Log target.
	/// @param exception Exception.
	/// @param format Log message format.
	/// @param formatArgs Log message format arguments.
	/// @param context Logger context.
	void FillData(LogEntry& targetEntry, std::string& targetString, const std::exception_ptr& exception, std::string_view format, std::format_args formatArgs,
		const Application::ILoggerContext& context) noexcept;
	/// @brief Fills log data.
	/// @param targetEntry Log entry.
	/// @param targetString Log target.
	/// @param exception Exception.
	/// @param stacktrace Stacktrace.
	/// @param context Logger context.
	void FillData(LogEntry& targetEntry, std::string& targetString, const std::exception_ptr& exception, const std::stacktrace& stacktrace, 
		const Application::ILoggerContext& context) noexcept;
	/// @brief Fills log data.
	/// @param targetEntry Log entry.
	/// @param targetString Log target.
	/// @param exception Exception.
	/// @param message Log message.
	/// @param stacktrace Stacktrace.
	/// @param context Logger context.
	void FillData(LogEntry& targetEntry, std::string& targetString, const std::exception_ptr& exception, std::string_view message, const std::stacktrace& stacktrace,
		const Application::ILoggerContext& context) noexcept;
	/// @brief Fills log data.
	/// @param targetEntry Log entry.
	/// @param targetString Log target.
	/// @param exception Exception.
	/// @param format Log message format.
	/// @param formatArgs Log message format arguments.
	/// @param stacktrace Stacktrace.
	/// @param context Logger context.
	void FillData(LogEntry& targetEntry, std::string& targetString, const std::exception_ptr& exception, std::string_view format, std::format_args formatArgs,
		const std::stacktrace& stacktrace, const Application::ILoggerContext& context) noexcept;

	/// @brief Fills log data.
	/// @param targetString Log target.
	/// @param logType Log type.
	/// @param message Log message.
	/// @param context Logger context.
	/// @return String to log.
	std::string_view FillData(std::string& targetString, LogType logType, std::string_view message, 
		const Application::ILoggerContext& context) noexcept;
	/// @brief Fills log data.
	/// @param targetString Log target.
	/// @param logType Log type.
	/// @param format Log message format.
	/// @param formatArgs Log message format arguments.
	/// @param context Logger context.
	/// @return String to log.
	std::string_view FillData(std::string& targetString, LogType logType, std::string_view format, std::format_args formatArgs, 
		const Application::ILoggerContext& context) noexcept;
	/// @brief Fills log data.
	/// @param targetString Log target.
	/// @param logType Log type.
	/// @param message Log message.
	/// @param stacktrace Stacktrace.
	/// @param context Logger context.
	/// @return String to log.
	std::string_view FillData(std::string& targetString, LogType logType, std::string_view message, const std::stacktrace& stacktrace,
		const Application::ILoggerContext& context) noexcept;
	/// @brief Fills log data.
	/// @param targetString Log target.
	/// @param logType Log type.
	/// @param format Log message format.
	/// @param formatArgs Log message format arguments.
	/// @param stacktrace Stacktrace.
	/// @param context Logger context.
	/// @return String to log.
	std::string_view FillData(std::string& targetString, LogType logType, std::string_view format, std::format_args formatArgs, const std::stacktrace& stacktrace,
		const Application::ILoggerContext& context) noexcept;

	/// @brief Fills log data.
	/// @param targetString Log target.
	/// @param exception Exception.
	/// @param context Logger context.
	/// @return String to log.
	std::string_view FillData(std::string& targetString, const std::exception_ptr& exception, const Application::ILoggerContext& context) noexcept;
	/// @brief Fills log data.
	/// @param targetString Log target.
	/// @param exception Exception.
	/// @param message Log message.
	/// @param context Logger context.
	/// @return String to log.
	std::string_view FillData(std::string& targetString, const std::exception_ptr& exception, std::string_view message,
		const Application::ILoggerContext& context) noexcept;
	/// @brief Fills log data.
	/// @param targetString Log target.
	/// @param exception Exception.
	/// @param format Log message format.
	/// @param formatArgs Log message format arguments.
	/// @param context Logger context.
	/// @return String to log.
	std::string_view FillData(std::string& targetString, const std::exception_ptr& exception, std::string_view format, std::format_args formatArgs,
		const Application::ILoggerContext& context) noexcept;
	/// @brief Fills log data.
	/// @param targetString Log target.
	/// @param exception Exception.
	/// @param stacktrace Stacktrace.
	/// @param context Logger context.
	/// @return String to log.
	std::string_view FillData(std::string& targetString, const std::exception_ptr& exception, const std::stacktrace& stacktrace, 
		const Application::ILoggerContext& context) noexcept;
	/// @brief Fills log data.
	/// @param targetString Log target.
	/// @param exception Exception.
	/// @param message Log message.
	/// @param stacktrace Stacktrace.
	/// @param context Logger context.
	/// @return String to log.
	std::string_view FillData(std::string& targetString, const std::exception_ptr& exception, std::string_view message, const std::stacktrace& stacktrace,
		const Application::ILoggerContext& context) noexcept;
	/// @brief Fills log data.
	/// @param targetString Log target.
	/// @param exception Exception.
	/// @param format Log message format.
	/// @param formatArgs Log message format arguments.
	/// @param stacktrace Stacktrace.
	/// @param context Logger context.
	/// @return String to log.
	std::string_view FillData(std::string& targetString, const std::exception_ptr& exception, std::string_view format, std::format_args formatArgs, 
		const std::stacktrace& stacktrace, const Application::ILoggerContext& context) noexcept;
}

namespace PonyEngine::Log
{
	constexpr std::string_view AllocationError = "Log message allocation failed."; ///< Allocation error message.
	constexpr std::string_view FormatError = "Log message format failed: "; ///< Format error message prefix.
	constexpr std::string_view NullptrException = "Nullptr exception."; ///< Nullptr exception message.
	constexpr std::string_view UnknownException = "Unknown exception"; ///< Unknown exception message.

	void FillTime(std::chrono::time_point<std::chrono::system_clock>& timePoint, std::uint64_t& frameCount, const Application::ILoggerContext& context) noexcept
	{
		timePoint = std::chrono::system_clock::now();
		frameCount = context.Application().FrameCount();
	}

	void FillHeader(std::string& target, const LogType logType, const std::chrono::time_point<std::chrono::system_clock> timePoint, const std::uint64_t frameCount)
	{
		std::format_to(std::back_inserter(target), "{}: [{:%F %R:%OS UTC} ({})]", GetLogTypeSymbol(logType), timePoint, frameCount);
	}

	std::pair<std::size_t, std::size_t> FillMessage(std::string& target, const std::string_view message)
	{
		const std::size_t messageStartIndex = target.size();
		target.append_range(message);
		const std::size_t messageEndIndex = target.size();

		return std::pair(messageStartIndex, messageEndIndex);
	}

	std::pair<std::size_t, std::size_t> FillMessage(std::string& target, const std::string_view format, const std::format_args formatArgs)
	{
		const std::size_t messageStartIndex = target.size();

		try
		{
			std::vformat_to(std::back_inserter(target), format, formatArgs);
		}
		catch (...)
		{
			target.erase(target.cbegin() + messageStartIndex, target.cend());
			target.append_range(FormatError);
			target.append_range(format);
		}

		const std::size_t messageEndIndex = target.size();

		return std::pair(messageStartIndex, messageEndIndex);
	}

	std::pair<std::size_t, std::size_t> FillMessage(std::string& target, const std::optional<const std::exception*>& exception)
	{
		const std::size_t messageStartIndex = target.size();
		if (exception) [[likely]]
		{
			if (*exception) [[likely]]
			{
				target.append_range(std::string_view((*exception)->what()));
			}
			else [[unlikely]]
			{
				target.append_range(UnknownException);
			}
		}
		else [[unlikely]]
		{
			target.append_range(NullptrException);
		}
		const std::size_t messageEndIndex = target.size();

		return std::pair(messageStartIndex, messageEndIndex);
	}

	std::string_view FillText(std::string& targetString, const LogType logType, const std::chrono::time_point<std::chrono::system_clock> timePoint, const  std::uint64_t frameCount,
		const std::string_view message)
	{
		FillHeader(targetString, logType, timePoint, frameCount);
		targetString.push_back(' ');
		const auto [messageStartIndex, messageEndIndex] = FillMessage(targetString, message);
		targetString.push_back('\n');

		return std::string_view(&targetString[messageStartIndex], messageEndIndex - messageStartIndex);
	}

	std::string_view FillText(std::string& targetString, const LogType logType, const std::chrono::time_point<std::chrono::system_clock> timePoint, const std::uint64_t frameCount,
		const std::string_view format, const std::format_args formatArgs)
	{
		FillHeader(targetString, logType, timePoint, frameCount);
		targetString.push_back(' ');
		const auto [messageStartIndex, messageEndIndex] = FillMessage(targetString, format, formatArgs);
		targetString.push_back('\n');

		return std::string_view(&targetString[messageStartIndex], messageEndIndex - messageStartIndex);
	}

	std::string_view FillText(std::string& targetString, const LogType logType, const std::chrono::time_point<std::chrono::system_clock> timePoint, const std::uint64_t frameCount,
		const std::string_view message, const std::stacktrace& stacktrace)
	{
		FillHeader(targetString, logType, timePoint, frameCount);
		targetString.push_back(' ');
		const auto [messageStartIndex, messageEndIndex] = FillMessage(targetString, message);
		std::format_to(std::back_inserter(targetString), "\n{}\n", stacktrace);

		return std::string_view(&targetString[messageStartIndex], messageEndIndex - messageStartIndex);
	}

	std::string_view FillText(std::string& targetString, const LogType logType, const std::chrono::time_point<std::chrono::system_clock> timePoint, const std::uint64_t frameCount, 
		const std::string_view format, const std::format_args formatArgs, const std::stacktrace& stacktrace)
	{
		FillHeader(targetString, logType, timePoint, frameCount);
		targetString.push_back(' ');
		const auto [messageStartIndex, messageEndIndex] = FillMessage(targetString, format, formatArgs);
		std::format_to(std::back_inserter(targetString), "\n{}\n", stacktrace);

		return std::string_view(&targetString[messageStartIndex], messageEndIndex - messageStartIndex);
	}

	std::string_view FillText(std::string& targetString, const std::chrono::time_point<std::chrono::system_clock> timePoint, const std::uint64_t frameCount, 
		const std::optional<const std::exception*>& exception)
	{
		FillHeader(targetString, LogType::Exception, timePoint, frameCount);
		targetString.push_back(' ');
		const auto [exceptionStartIndex, exceptionEndIndex] = FillMessage(targetString, exception);
		targetString.push_back('\n');

		return std::string_view(&targetString[exceptionStartIndex], exceptionEndIndex - exceptionStartIndex);
	}

	std::string_view FillText(std::string& targetString, const std::chrono::time_point<std::chrono::system_clock> timePoint, const std::uint64_t frameCount, 
		const std::optional<const std::exception*>& exception, const std::string_view message)
	{
		FillHeader(targetString, LogType::Exception, timePoint, frameCount);
		targetString.push_back(' ');
		const auto [exceptionStartIndex, exceptionEndIndex] = FillMessage(targetString, exception);
		targetString.assign_range(" - ");
		const auto [messageStartIndex, messageEndIndex] = FillMessage(targetString, message);
		targetString.push_back('\n');

		return std::string_view(&targetString[exceptionStartIndex], messageEndIndex - exceptionStartIndex);
	}

	std::string_view FillText(std::string& targetString, const std::chrono::time_point<std::chrono::system_clock> timePoint, const std::uint64_t frameCount, 
		const std::optional<const std::exception*>& exception, const std::string_view format, const std::format_args formatArgs)
	{
		FillHeader(targetString, LogType::Exception, timePoint, frameCount);
		targetString.push_back(' ');
		const auto [exceptionStartIndex, exceptionEndIndex] = FillMessage(targetString, exception);
		targetString.assign_range(" - ");
		const auto [messageStartIndex, messageEndIndex] = FillMessage(targetString, format, formatArgs);
		targetString.push_back('\n');

		return std::string_view(&targetString[exceptionStartIndex], messageEndIndex - exceptionStartIndex);
	}

	std::string_view FillText(std::string& targetString, const std::chrono::time_point<std::chrono::system_clock> timePoint, const std::uint64_t frameCount, 
		const std::optional<const std::exception*>& exception, const std::stacktrace& stacktrace)
	{
		FillHeader(targetString, LogType::Exception, timePoint, frameCount);
		targetString.push_back(' ');
		const auto [exceptionStartIndex, exceptionEndIndex] = FillMessage(targetString, exception);
		std::format_to(std::back_inserter(targetString), "\n{}\n", stacktrace);

		return std::string_view(&targetString[exceptionStartIndex], exceptionEndIndex - exceptionStartIndex);
	}

	std::string_view FillText(std::string& targetString, const std::chrono::time_point<std::chrono::system_clock> timePoint, const std::uint64_t frameCount, 
		const std::optional<const std::exception*>& exception, const std::string_view message, const std::stacktrace& stacktrace)
	{
		FillHeader(targetString, LogType::Exception, timePoint, frameCount);
		targetString.push_back(' ');
		const auto [exceptionStartIndex, exceptionEndIndex] = FillMessage(targetString, exception);
		targetString.assign_range(" - ");
		const auto [messageStartIndex, messageEndIndex] = FillMessage(targetString, message);
		std::format_to(std::back_inserter(targetString), "\n{}\n", stacktrace);

		return std::string_view(&targetString[exceptionStartIndex], messageEndIndex - exceptionStartIndex);
	}

	std::string_view FillText(std::string& targetString, const std::chrono::time_point<std::chrono::system_clock> timePoint, const std::uint64_t frameCount, 
		const std::optional<const std::exception*>& exception, const std::string_view format, const std::format_args formatArgs, const std::stacktrace& stacktrace)
	{
		FillHeader(targetString, LogType::Exception, timePoint, frameCount);
		targetString.push_back(' ');
		const auto [exceptionStartIndex, exceptionEndIndex] = FillMessage(targetString, exception);
		targetString.assign_range(" - ");
		const auto [messageStartIndex, messageEndIndex] = FillMessage(targetString, format, formatArgs);
		std::format_to(std::back_inserter(targetString), "\n{}\n", stacktrace);

		return std::string_view(&targetString[exceptionStartIndex], messageEndIndex - exceptionStartIndex);
	}

	void FillData(LogEntry& targetEntry, std::string& targetString, const LogType logType, const std::string_view message, const Application::ILoggerContext& context) noexcept
	{
		FillTime(targetEntry.timePoint, targetEntry.frameCount, context);
		targetEntry.logType = logType;

		try
		{
			targetEntry.message = FillText(targetString, logType, targetEntry.timePoint, targetEntry.frameCount, message);
			targetEntry.formattedMessage = targetString;
		}
		catch (...)
		{
			targetEntry.message = AllocationError;
			targetEntry.formattedMessage = targetEntry.message;
		}
	}

	void FillData(LogEntry& targetEntry, std::string& targetString, const LogType logType, const std::string_view format, const std::format_args formatArgs, 
		const Application::ILoggerContext& context) noexcept
	{
		FillTime(targetEntry.timePoint, targetEntry.frameCount, context);
		targetEntry.logType = logType;

		try
		{
			targetEntry.message = FillText(targetString, logType, targetEntry.timePoint, targetEntry.frameCount, format, formatArgs);
			targetEntry.formattedMessage = targetString;
		}
		catch (...)
		{
			targetEntry.message = AllocationError;
			targetEntry.formattedMessage = targetEntry.message;
		}
	}

	void FillData(LogEntry& targetEntry, std::string& targetString, const LogType logType, const std::string_view message, const std::stacktrace& stacktrace, 
		const Application::ILoggerContext& context) noexcept
	{
		FillTime(targetEntry.timePoint, targetEntry.frameCount, context);
		targetEntry.logType = logType;
		targetEntry.stacktrace = &stacktrace;

		try
		{
			targetEntry.message = FillText(targetString, logType, targetEntry.timePoint, targetEntry.frameCount, message, stacktrace);
			targetEntry.formattedMessage = targetString;
		}
		catch (...)
		{
			targetEntry.message = AllocationError;
			targetEntry.formattedMessage = targetEntry.message;
		}
	}

	void FillData(LogEntry& targetEntry, std::string& targetString, const LogType logType, const std::string_view format, const std::format_args formatArgs, 
		const std::stacktrace& stacktrace, const Application::ILoggerContext& context) noexcept
	{
		FillTime(targetEntry.timePoint, targetEntry.frameCount, context);
		targetEntry.logType = logType;
		targetEntry.stacktrace = &stacktrace;

		try
		{
			targetEntry.message = FillText(targetString, logType, targetEntry.timePoint, targetEntry.frameCount, format, formatArgs, stacktrace);
			targetEntry.formattedMessage = targetString;
		}
		catch (...)
		{
			targetEntry.message = AllocationError;
			targetEntry.formattedMessage = targetEntry.message;
		}
	}

	void FillData(LogEntry& targetEntry, std::string& targetString, const std::exception_ptr& exception,
		const Application::ILoggerContext& context) noexcept
	{
		FillTime(targetEntry.timePoint, targetEntry.frameCount, context);
		targetEntry.logType = LogType::Exception;
		targetEntry.exceptionPtr = exception;

		try
		{
			if (exception) [[likely]]
			{
				try
				{
					std::rethrow_exception(exception);
				}
				catch (const std::exception& e)
				{
					targetEntry.message = FillText(targetString, targetEntry.timePoint, targetEntry.frameCount, &e);
				}
				catch (...)
				{
					targetEntry.message = FillText(targetString, targetEntry.timePoint, targetEntry.frameCount, nullptr);
				}
			}
			else [[unlikely]]
			{
				targetEntry.message = FillText(targetString, targetEntry.timePoint, targetEntry.frameCount, std::nullopt);
			}
			targetEntry.formattedMessage = targetString;
		}
		catch (...)
		{
			targetEntry.message = AllocationError;
			targetEntry.formattedMessage = targetEntry.message;
		}
	}

	void FillData(LogEntry& targetEntry, std::string& targetString, const std::exception_ptr& exception, const std::string_view message, 
		const Application::ILoggerContext& context) noexcept
	{
		FillTime(targetEntry.timePoint, targetEntry.frameCount, context);
		targetEntry.logType = LogType::Exception;
		targetEntry.exceptionPtr = exception;

		try
		{
			if (exception) [[likely]]
			{
				try
				{
					std::rethrow_exception(exception);
				}
				catch (const std::exception& e)
				{
					targetEntry.message = FillText(targetString, targetEntry.timePoint, targetEntry.frameCount, &e, message);
				}
				catch (...)
				{
					targetEntry.message = FillText(targetString, targetEntry.timePoint, targetEntry.frameCount, nullptr, message);
				}
			}
			else [[unlikely]]
			{
				targetEntry.message = FillText(targetString, targetEntry.timePoint, targetEntry.frameCount, std::nullopt, message);
			}
			targetEntry.formattedMessage = targetString;
		}
		catch (...)
		{
			targetEntry.message = AllocationError;
			targetEntry.formattedMessage = targetEntry.message;
		}
	}

	void FillData(LogEntry& targetEntry, std::string& targetString, const std::exception_ptr& exception, const std::string_view format, const std::format_args formatArgs, 
		const Application::ILoggerContext& context) noexcept
	{
		FillTime(targetEntry.timePoint, targetEntry.frameCount, context);
		targetEntry.logType = LogType::Exception;
		targetEntry.exceptionPtr = exception;

		try
		{
			if (exception) [[likely]]
			{
				try
				{
					std::rethrow_exception(exception);
				}
				catch (const std::exception& e)
				{
					targetEntry.message = FillText(targetString, targetEntry.timePoint, targetEntry.frameCount, &e, format, formatArgs);
				}
				catch (...)
				{
					targetEntry.message = FillText(targetString, targetEntry.timePoint, targetEntry.frameCount, nullptr, format, formatArgs);
				}
			}
			else [[unlikely]]
			{
				targetEntry.message = FillText(targetString, targetEntry.timePoint, targetEntry.frameCount, std::nullopt, format, formatArgs);
			}
			targetEntry.formattedMessage = targetString;
		}
		catch (...)
		{
			targetEntry.message = AllocationError;
			targetEntry.formattedMessage = targetEntry.message;
		}
	}

	void FillData(LogEntry& targetEntry, std::string& targetString, const std::exception_ptr& exception, const std::stacktrace& stacktrace, 
		const Application::ILoggerContext& context) noexcept
	{
		FillTime(targetEntry.timePoint, targetEntry.frameCount, context);
		targetEntry.logType = LogType::Exception;
		targetEntry.exceptionPtr = exception;
		targetEntry.stacktrace = &stacktrace;

		try
		{
			if (exception) [[likely]]
			{
				try
				{
					std::rethrow_exception(exception);
				}
				catch (const std::exception& e)
				{
					targetEntry.message = FillText(targetString, targetEntry.timePoint, targetEntry.frameCount, &e, stacktrace);
				}
				catch (...)
				{
					targetEntry.message = FillText(targetString, targetEntry.timePoint, targetEntry.frameCount, nullptr, stacktrace);
				}
			}
			else [[unlikely]]
			{
				targetEntry.message = FillText(targetString, targetEntry.timePoint, targetEntry.frameCount, std::nullopt, stacktrace);
			}
			targetEntry.formattedMessage = targetString;
		}
		catch (...)
		{
			targetEntry.message = AllocationError;
			targetEntry.formattedMessage = targetEntry.message;
		}
	}

	void FillData(LogEntry& targetEntry, std::string& targetString, const std::exception_ptr& exception, const std::string_view message, const std::stacktrace& stacktrace,
		const Application::ILoggerContext& context) noexcept
	{
		FillTime(targetEntry.timePoint, targetEntry.frameCount, context);
		targetEntry.logType = LogType::Exception;
		targetEntry.exceptionPtr = exception;

		try
		{
			if (exception) [[likely]]
			{
				try
				{
					std::rethrow_exception(exception);
				}
				catch (const std::exception& e)
				{
					targetEntry.message = FillText(targetString, targetEntry.timePoint, targetEntry.frameCount, &e, message, stacktrace);
				}
				catch (...)
				{
					targetEntry.message = FillText(targetString, targetEntry.timePoint, targetEntry.frameCount, nullptr, message, stacktrace);
				}
			}
			else [[unlikely]]
			{
				targetEntry.message = FillText(targetString, targetEntry.timePoint, targetEntry.frameCount, std::nullopt, message, stacktrace);
			}
			targetEntry.formattedMessage = targetString;
		}
		catch (...)
		{
			targetEntry.message = AllocationError;
			targetEntry.formattedMessage = targetEntry.message;
		}
	}

	void FillData(LogEntry& targetEntry, std::string& targetString, const std::exception_ptr& exception, const std::string_view format, const std::format_args formatArgs, 
		const std::stacktrace& stacktrace, const Application::ILoggerContext& context) noexcept
	{
		FillTime(targetEntry.timePoint, targetEntry.frameCount, context);
		targetEntry.logType = LogType::Exception;
		targetEntry.exceptionPtr = exception;

		try
		{
			if (exception) [[likely]]
			{
				try
				{
					std::rethrow_exception(exception);
				}
				catch (const std::exception& e)
				{
					targetEntry.message = FillText(targetString, targetEntry.timePoint, targetEntry.frameCount, &e, format, formatArgs, stacktrace);
				}
				catch (...)
				{
					targetEntry.message = FillText(targetString, targetEntry.timePoint, targetEntry.frameCount, nullptr, format, formatArgs, stacktrace);
				}
			}
			else [[unlikely]]
			{
				targetEntry.message = FillText(targetString, targetEntry.timePoint, targetEntry.frameCount, std::nullopt, format, formatArgs, stacktrace);
			}
			targetEntry.formattedMessage = targetString;
		}
		catch (...)
		{
			targetEntry.message = AllocationError;
			targetEntry.formattedMessage = targetEntry.message;
		}
	}

	std::string_view FillData(std::string& targetString, const LogType logType, const std::string_view message, const Application::ILoggerContext& context) noexcept
	{
		std::chrono::time_point<std::chrono::system_clock> timePoint;
		std::uint64_t frameCount;
		FillTime(timePoint, frameCount, context);

		try
		{
			FillText(targetString, logType, timePoint, frameCount, message);
			return targetString;
		}
		catch (...)
		{
			return AllocationError;
		}
	}

	std::string_view FillData(std::string& targetString, const LogType logType, const std::string_view format, const std::format_args formatArgs, 
		const Application::ILoggerContext& context) noexcept
	{
		std::chrono::time_point<std::chrono::system_clock> timePoint;
		std::uint64_t frameCount;
		FillTime(timePoint, frameCount, context);

		try
		{
			FillText(targetString, logType, timePoint, frameCount, format, formatArgs);
			return targetString;
		}
		catch (...)
		{
			return AllocationError;
		}
	}

	std::string_view FillData(std::string& targetString, const LogType logType, const std::string_view message, const std::stacktrace& stacktrace, 
		const Application::ILoggerContext& context) noexcept
	{
		std::chrono::time_point<std::chrono::system_clock> timePoint;
		std::uint64_t frameCount;
		FillTime(timePoint, frameCount, context);

		try
		{
			FillText(targetString, logType, timePoint, frameCount, message, stacktrace);
			return targetString;
		}
		catch (...)
		{
			return AllocationError;
		}
	}

	std::string_view FillData(std::string& targetString, const LogType logType, const std::string_view format, const std::format_args formatArgs, 
		const std::stacktrace& stacktrace, const Application::ILoggerContext& context) noexcept
	{
		std::chrono::time_point<std::chrono::system_clock> timePoint;
		std::uint64_t frameCount;
		FillTime(timePoint, frameCount, context);

		try
		{
			FillText(targetString, logType, timePoint, frameCount, format, formatArgs, stacktrace);
			return targetString;
		}
		catch (...)
		{
			return AllocationError;
		}
	}

	std::string_view FillData(std::string& targetString, const std::exception_ptr& exception, const Application::ILoggerContext& context) noexcept
	{
		std::chrono::time_point<std::chrono::system_clock> timePoint;
		std::uint64_t frameCount;
		FillTime(timePoint, frameCount, context);

		try
		{
			if (exception) [[likely]]
			{
				try
				{
					std::rethrow_exception(exception);
				}
				catch (const std::exception& e)
				{
					FillText(targetString, timePoint, frameCount, &e);
					return targetString;
				}
				catch (...)
				{
					FillText(targetString, timePoint, frameCount, nullptr);
					return targetString;
				}
			}
			else [[unlikely]]
			{
				FillText(targetString, timePoint, frameCount, std::nullopt);
				return targetString;
			}
		}
		catch (...)
		{
			return AllocationError;
		}
	}

	std::string_view FillData(std::string& targetString, const std::exception_ptr& exception, const std::string_view message,
		const Application::ILoggerContext& context) noexcept
	{
		std::chrono::time_point<std::chrono::system_clock> timePoint;
		std::uint64_t frameCount;
		FillTime(timePoint, frameCount, context);

		try
		{
			if (exception) [[likely]]
			{
				try
				{
					std::rethrow_exception(exception);
				}
				catch (const std::exception& e)
				{
					FillText(targetString, timePoint, frameCount, &e, message);
					return targetString;
				}
				catch (...)
				{
					FillText(targetString, timePoint, frameCount, nullptr, message);
					return targetString;
				}
			}
			else [[unlikely]]
			{
				FillText(targetString, timePoint, frameCount, std::nullopt, message);
				return targetString;
			}
		}
		catch (...)
		{
			return AllocationError;
		}
	}

	std::string_view FillData(std::string& targetString, const std::exception_ptr& exception, const std::string_view format, const std::format_args formatArgs, 
		const Application::ILoggerContext& context) noexcept
	{
		std::chrono::time_point<std::chrono::system_clock> timePoint;
		std::uint64_t frameCount;
		FillTime(timePoint, frameCount, context);

		try
		{
			if (exception) [[likely]]
			{
				try
				{
					std::rethrow_exception(exception);
				}
				catch (const std::exception& e)
				{
					FillText(targetString, timePoint, frameCount, &e, format, formatArgs);
					return targetString;
				}
				catch (...)
				{
					FillText(targetString, timePoint, frameCount, nullptr, format, formatArgs);
					return targetString;
				}
			}
			else [[unlikely]]
			{
				FillText(targetString, timePoint, frameCount, std::nullopt, format, formatArgs);
				return targetString;
			}
		}
		catch (...)
		{
			return AllocationError;
		}
	}

	std::string_view FillData(std::string& targetString, const std::exception_ptr& exception, const std::stacktrace& stacktrace, const Application::ILoggerContext& context) noexcept
	{
		std::chrono::time_point<std::chrono::system_clock> timePoint;
		std::uint64_t frameCount;
		FillTime(timePoint, frameCount, context);

		try
		{
			if (exception) [[likely]]
			{
				try
				{
					std::rethrow_exception(exception);
				}
				catch (const std::exception& e)
				{
					FillText(targetString, timePoint, frameCount, &e, stacktrace);
					return targetString;
				}
				catch (...)
				{
					FillText(targetString, timePoint, frameCount, nullptr, stacktrace);
					return targetString;
				}
			}
			else [[unlikely]]
			{
				FillText(targetString, timePoint, frameCount, std::nullopt, stacktrace);
				return targetString;
			}
		}
		catch (...)
		{
			return AllocationError;
		}
	}

	std::string_view FillData(std::string& targetString, const std::exception_ptr& exception, const std::string_view message,
		const std::stacktrace& stacktrace, const Application::ILoggerContext& context) noexcept
	{
		std::chrono::time_point<std::chrono::system_clock> timePoint;
		std::uint64_t frameCount;
		FillTime(timePoint, frameCount, context);

		try
		{
			if (exception) [[likely]]
			{
				try
				{
					std::rethrow_exception(exception);
				}
				catch (const std::exception& e)
				{
					FillText(targetString, timePoint, frameCount, &e, message, stacktrace);
					return targetString;
				}
				catch (...)
				{
					FillText(targetString, timePoint, frameCount, nullptr, message, stacktrace);
					return targetString;
				}
			}
			else [[unlikely]]
			{
				FillText(targetString, timePoint, frameCount, std::nullopt, message, stacktrace);
				return targetString;
			}
		}
		catch (...)
		{
			return AllocationError;
		}
	}

	std::string_view FillData(std::string& targetString, const std::exception_ptr& exception, const std::string_view format, const std::format_args formatArgs, 
		const std::stacktrace& stacktrace, const Application::ILoggerContext& context) noexcept
	{
		std::chrono::time_point<std::chrono::system_clock> timePoint;
		std::uint64_t frameCount;
		FillTime(timePoint, frameCount, context);

		try
		{
			if (exception) [[likely]]
			{
				try
				{
					std::rethrow_exception(exception);
				}
				catch (const std::exception& e)
				{
					FillText(targetString, timePoint, frameCount, &e, format, formatArgs, stacktrace);
					return targetString;
				}
				catch (...)
				{
					FillText(targetString, timePoint, frameCount, nullptr, format, formatArgs, stacktrace);
					return targetString;
				}
			}
			else [[unlikely]]
			{
				FillText(targetString, timePoint, frameCount, std::nullopt, format, formatArgs, stacktrace);
				return targetString;
			}
		}
		catch (...)
		{
			return AllocationError;
		}
	}
}
