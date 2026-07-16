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

import PonyEngine.Application;
import PonyEngine.Log.Ext;

import :LogTypeSymbol;

using namespace std::literals::string_view_literals;

export namespace PonyEngine::Log
{
	void FillData(LogEntry& logEntry, std::string& formattedMessage, LogType logType, std::string_view message) noexcept;
	void FillData(LogEntry& logEntry, std::string& formattedMessage, LogType logType, std::string_view format, std::format_args formatArgs) noexcept;
	void FillData(LogEntry& logEntry, std::string& formattedMessage, LogType logType, std::string_view message, const std::stacktrace& stacktrace) noexcept;
	void FillData(LogEntry& logEntry, std::string& formattedMessage, LogType logType, std::string_view format, std::format_args formatArgs, const std::stacktrace& stacktrace) noexcept;

	void FillData(LogEntry& logEntry, std::string& formattedMessage, LogType logType, const std::exception_ptr& exception) noexcept;
	void FillData(LogEntry& logEntry, std::string& formattedMessage, LogType logType, const std::exception_ptr& exception, std::string_view message) noexcept;
	void FillData(LogEntry& logEntry, std::string& formattedMessage, LogType logType, const std::exception_ptr& exception, std::string_view format, std::format_args formatArgs) noexcept;
	void FillData(LogEntry& logEntry, std::string& formattedMessage, LogType logType, const std::exception_ptr& exception, const std::stacktrace& stacktrace) noexcept;
	void FillData(LogEntry& logEntry, std::string& formattedMessage, LogType logType, const std::exception_ptr& exception, std::string_view message, const std::stacktrace& stacktrace) noexcept;
	void FillData(LogEntry& logEntry, std::string& formattedMessage, LogType logType, const std::exception_ptr& exception, std::string_view format, std::format_args formatArgs, const std::stacktrace& stacktrace) noexcept;
}

namespace PonyEngine::Log
{
	void FillLogEntry(LogEntry& logEntry, LogType logType) noexcept;
	void FillLogEntry(LogEntry& logEntry, LogType logType, const std::stacktrace& stacktrace) noexcept;
	void FillLogEntry(LogEntry& logEntry, LogType logType, const std::exception_ptr& exception) noexcept;
	void FillLogEntry(LogEntry& logEntry, LogType logType, const std::exception_ptr& exception, const std::stacktrace& stacktrace) noexcept;

	void FillHeader(const LogEntry& logEntry, std::string& formattedMessage);

	std::pair<std::size_t, std::size_t> FillMessage(std::string& formattedMessage, std::string_view message);
	std::pair<std::size_t, std::size_t> FillMessage(std::string& formattedMessage, std::string_view format, std::format_args formatArgs);
	std::pair<std::size_t, std::size_t> FillException(std::string& formattedMessage, const std::exception_ptr& exception);
	
	void FillStacktrace(std::string& formattedMessage, const std::stacktrace& stacktrace);

	void SetMainMessage(LogEntry& logEntry, const std::string& formattedMessage, const std::pair<std::size_t, std::size_t>& messageBounds) noexcept;

	[[nodiscard("Pure function")]]
	std::pair<std::size_t, std::size_t> MergeBounds(const std::pair<std::size_t, std::size_t>& exceptionBounds, const std::pair<std::size_t, std::size_t>& messageBounds) noexcept;

	void FillData(LogEntry& logEntry, std::string& formattedMessage, const LogType logType, const std::string_view message) noexcept
	{
		FillLogEntry(logEntry, logType);

		auto messageBounds = std::pair<std::size_t, std::size_t>(0uz, 0uz);
		try
		{
			FillHeader(logEntry, formattedMessage);
			formattedMessage += ' ';
			messageBounds = FillMessage(formattedMessage, message);
		}
		catch (...)
		{
			// Something strange happened. It's better to log anything it has.
		}
		try
		{
			formattedMessage += '\n';
		}
		catch (...)
		{
			// Something strange happened. It's better to log anything it has.
		}

		SetMainMessage(logEntry, formattedMessage, messageBounds);
	}

	void FillData(LogEntry& logEntry, std::string& formattedMessage, const LogType logType, const std::string_view format, const std::format_args formatArgs) noexcept
	{
		FillLogEntry(logEntry, logType);

		auto messageBounds = std::pair<std::size_t, std::size_t>(0uz, 0uz);
		try
		{
			FillHeader(logEntry, formattedMessage);
			formattedMessage += ' ';
			messageBounds = FillMessage(formattedMessage, format, formatArgs);
		}
		catch (...)
		{
			// Something strange happened. It's better to log anything it has.
		}
		try
		{
			formattedMessage += '\n';
		}
		catch (...)
		{
			// Something strange happened. It's better to log anything it has.
		}

		SetMainMessage(logEntry, formattedMessage, messageBounds);
	}

	void FillData(LogEntry& logEntry, std::string& formattedMessage, const LogType logType, const std::string_view message, const std::stacktrace& stacktrace) noexcept
	{
		FillLogEntry(logEntry, logType, stacktrace);

		auto messageBounds = std::pair<std::size_t, std::size_t>(0uz, 0uz);
		try
		{
			FillHeader(logEntry, formattedMessage);
			formattedMessage += ' ';
			messageBounds = FillMessage(formattedMessage, message);
			formattedMessage += '\n';
			FillStacktrace(formattedMessage, stacktrace);
		}
		catch (...)
		{
			// Something strange happened. It's better to log anything it has.
		}
		try
		{
			formattedMessage += '\n';
		}
		catch (...)
		{
			// Something strange happened. It's better to log anything it has.
		}

		SetMainMessage(logEntry, formattedMessage, messageBounds);
	}

	void FillData(LogEntry& logEntry, std::string& formattedMessage, const LogType logType, const std::string_view format, const std::format_args formatArgs, const std::stacktrace& stacktrace) noexcept
	{
		FillLogEntry(logEntry, logType, stacktrace);

		auto messageBounds = std::pair<std::size_t, std::size_t>(0uz, 0uz);
		try
		{
			FillHeader(logEntry, formattedMessage);
			formattedMessage += ' ';
			messageBounds = FillMessage(formattedMessage, format, formatArgs);
			formattedMessage += '\n';
			FillStacktrace(formattedMessage, stacktrace);
		}
		catch (...)
		{
			// Something strange happened. It's better to log anything it has.
		}
		try
		{
			formattedMessage += '\n';
		}
		catch (...)
		{
			// Something strange happened. It's better to log anything it has.
		}

		SetMainMessage(logEntry, formattedMessage, messageBounds);
	}

	void FillData(LogEntry& logEntry, std::string& formattedMessage, const LogType logType, const std::exception_ptr& exception) noexcept
	{
		FillLogEntry(logEntry, logType, exception);

		auto exceptionBounds = std::pair<std::size_t, std::size_t>(0uz, 0uz);
		try
		{
			FillHeader(logEntry, formattedMessage);
			formattedMessage += ' ';
			exceptionBounds = FillException(formattedMessage, exception);
		}
		catch (...)
		{
			// Something strange happened. It's better to log anything it has.
		}
		try
		{
			formattedMessage += '\n';
		}
		catch (...)
		{
			// Something strange happened. It's better to log anything it has.
		}

		SetMainMessage(logEntry, formattedMessage, exceptionBounds);
	}

	void FillData(LogEntry& logEntry, std::string& formattedMessage, const LogType logType, const std::exception_ptr& exception, const std::string_view message) noexcept
	{
		FillLogEntry(logEntry, logType, exception);

		auto exceptionBounds = std::pair<std::size_t, std::size_t>(0uz, 0uz);
		auto messageBounds = std::pair<std::size_t, std::size_t>(0uz, 0uz);
		try
		{
			FillHeader(logEntry, formattedMessage);
			formattedMessage += ' ';
			exceptionBounds = FillException(formattedMessage, exception);
			formattedMessage += '\n';
			messageBounds = FillMessage(formattedMessage, message);
		}
		catch (...)
		{
			// Something strange happened. It's better to log anything it has.
		}
		try
		{
			formattedMessage += '\n';
		}
		catch (...)
		{
			// Something strange happened. It's better to log anything it has.
		}

		SetMainMessage(logEntry, formattedMessage, MergeBounds(exceptionBounds, messageBounds));
	}

	void FillData(LogEntry& logEntry, std::string& formattedMessage, const LogType logType, const std::exception_ptr& exception, const std::string_view format, const std::format_args formatArgs) noexcept
	{
		FillLogEntry(logEntry, logType, exception);

		auto exceptionBounds = std::pair<std::size_t, std::size_t>(0uz, 0uz);
		auto messageBounds = std::pair<std::size_t, std::size_t>(0uz, 0uz);
		try
		{
			FillHeader(logEntry, formattedMessage);
			formattedMessage += ' ';
			exceptionBounds = FillException(formattedMessage, exception);
			formattedMessage += '\n';
			messageBounds = FillMessage(formattedMessage, format, formatArgs);
		}
		catch (...)
		{
			// Something strange happened. It's better to log anything it has.
		}
		try
		{
			formattedMessage += '\n';
		}
		catch (...)
		{
			// Something strange happened. It's better to log anything it has.
		}

		SetMainMessage(logEntry, formattedMessage, MergeBounds(exceptionBounds, messageBounds));
	}

	void FillData(LogEntry& logEntry, std::string& formattedMessage, const LogType logType, const std::exception_ptr& exception, const std::stacktrace& stacktrace) noexcept
	{
		FillLogEntry(logEntry, logType, exception, stacktrace);

		auto exceptionBounds = std::pair<std::size_t, std::size_t>(0uz, 0uz);
		try
		{
			FillHeader(logEntry, formattedMessage);
			formattedMessage += ' ';
			exceptionBounds = FillException(formattedMessage, exception);
			formattedMessage += '\n';
			FillStacktrace(formattedMessage, stacktrace);
		}
		catch (...)
		{
			// Something strange happened. It's better to log anything it has.
		}
		try
		{
			formattedMessage += '\n';
		}
		catch (...)
		{
			// Something strange happened. It's better to log anything it has.
		}

		SetMainMessage(logEntry, formattedMessage, exceptionBounds);
	}

	void FillData(LogEntry& logEntry, std::string& formattedMessage, const LogType logType, const std::exception_ptr& exception, const std::string_view message, const std::stacktrace& stacktrace) noexcept
	{
		FillLogEntry(logEntry, logType, exception, stacktrace);

		auto exceptionBounds = std::pair<std::size_t, std::size_t>(0uz, 0uz);
		auto messageBounds = std::pair<std::size_t, std::size_t>(0uz, 0uz);
		try
		{
			FillHeader(logEntry, formattedMessage);
			formattedMessage += ' ';
			exceptionBounds = FillException(formattedMessage, exception);
			formattedMessage += '\n';
			messageBounds = FillMessage(formattedMessage, message);
			formattedMessage += '\n';
			FillStacktrace(formattedMessage, stacktrace);
		}
		catch (...)
		{
			// Something strange happened. It's better to log anything it has.
		}
		try
		{
			formattedMessage += '\n';
		}
		catch (...)
		{
			// Something strange happened. It's better to log anything it has.
		}

		SetMainMessage(logEntry, formattedMessage, MergeBounds(exceptionBounds, messageBounds));
	}

	void FillData(LogEntry& logEntry, std::string& formattedMessage, const LogType logType, const std::exception_ptr& exception, const std::string_view format, const std::format_args formatArgs, const std::stacktrace& stacktrace) noexcept
	{
		FillLogEntry(logEntry, logType, exception, stacktrace);

		auto exceptionBounds = std::pair<std::size_t, std::size_t>(0uz, 0uz);
		auto messageBounds = std::pair<std::size_t, std::size_t>(0uz, 0uz);
		try
		{
			FillHeader(logEntry, formattedMessage);
			formattedMessage += ' ';
			exceptionBounds = FillException(formattedMessage, exception);
			formattedMessage += '\n';
			messageBounds = FillMessage(formattedMessage, format, formatArgs);
			formattedMessage += '\n';
			FillStacktrace(formattedMessage, stacktrace);
		}
		catch (...)
		{
			// Something strange happened. It's better to log anything it has.
		}
		try
		{
			formattedMessage += '\n';
		}
		catch (...)
		{
			// Something strange happened. It's better to log anything it has.
		}

		SetMainMessage(logEntry, formattedMessage, MergeBounds(exceptionBounds, messageBounds));
	}

	void FillLogEntry(LogEntry& logEntry, const LogType logType) noexcept
	{
		logEntry.timePoint = std::chrono::system_clock::now();
		logEntry.threadId = std::this_thread::get_id();
		logEntry.logType = logType;
	}

	void FillLogEntry(LogEntry& logEntry, const LogType logType, const std::stacktrace& stacktrace) noexcept
	{
		FillLogEntry(logEntry, logType);
		logEntry.stacktrace = &stacktrace;
	}

	void FillLogEntry(LogEntry& logEntry, const LogType logType, const std::exception_ptr& exception) noexcept
	{
		FillLogEntry(logEntry, logType);
		logEntry.exception = &exception;
	}

	void FillLogEntry(LogEntry& logEntry, const LogType logType, const std::exception_ptr& exception, const std::stacktrace& stacktrace) noexcept
	{
		FillLogEntry(logEntry, logType);
		logEntry.stacktrace = &stacktrace;
		logEntry.exception = &exception;
	}

	void FillHeader(const LogEntry& logEntry, std::string& formattedMessage)
	{
		std::format_to(std::back_inserter(formattedMessage), "{} | {} : [{:%F %R:%OS UTC}]", GetLogTypeSymbol(logEntry.logType), logEntry.threadId, logEntry.timePoint);
	}

	std::pair<std::size_t, std::size_t> FillMessage(std::string& formattedMessage, const std::string_view message)
	{
		const std::size_t messageStart = formattedMessage.size();
		formattedMessage += message;
		const std::size_t messageFinish = formattedMessage.size();

		return std::pair(messageStart, messageFinish);
	}

	std::pair<std::size_t, std::size_t> FillMessage(std::string& formattedMessage, const std::string_view format, const std::format_args formatArgs)
	{
		const std::size_t messageStart = formattedMessage.size();
		std::vformat_to(std::back_inserter(formattedMessage), format, formatArgs);
		const std::size_t messageFinish = formattedMessage.size();

		return std::pair(messageStart, messageFinish);
	}

	std::pair<std::size_t, std::size_t> FillException(std::string& formattedMessage, const std::exception_ptr& exception)
	{
		const std::size_t messageStart = formattedMessage.size();
		try
		{
			std::rethrow_exception(exception);
		}
		catch (const std::exception& e)
		{
			std::format_to(std::back_inserter(formattedMessage), "{}({})", typeid(e).name(), e.what());
		}
		catch (...)
		{
			formattedMessage += "Unknown exception";
		}
		const std::size_t messageFinish = formattedMessage.size();

		return std::pair(messageStart, messageFinish);
	}

	void FillStacktrace(std::string& formattedMessage, const std::stacktrace& stacktrace)
	{
		std::format_to(std::back_inserter(formattedMessage), "{}", stacktrace);
	}

	void SetMainMessage(LogEntry& logEntry, const std::string& formattedMessage, const std::pair<std::size_t, std::size_t>& messageBounds) noexcept
	{
		logEntry.message = std::string_view(formattedMessage).substr(messageBounds.first, messageBounds.second - messageBounds.first);
	}

	std::pair<std::size_t, std::size_t> MergeBounds(const std::pair<std::size_t, std::size_t>& exceptionBounds, const std::pair<std::size_t, std::size_t>& messageBounds) noexcept
	{
		return std::pair(std::min(exceptionBounds.first, messageBounds.first), std::max(exceptionBounds.second, messageBounds.second));
	}
}
