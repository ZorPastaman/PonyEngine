/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Log:LogHelper;

import std;

import :ILogService;
import :LogType;

export namespace PonyEngine::Log
{
	/// @brief Logs to the log service.
	/// @param logService log service.
	/// @param logType Log type.
	/// @param message Log message.
	/// @note The function is thread-safe.
	void LogToLogService(const ILogService& logService, LogType logType, std::string_view message) noexcept;
	/// @brief Logs to the log service.
	/// @tparam Args Format argument types.
	/// @param logService log service.
	/// @param logType Log type.
	/// @param format Log message format.
	/// @param args Log message format arguments.
	/// @note The function is thread-safe.
	template<typename... Args>
	void LogToLogService(const ILogService& logService, LogType logType, std::format_string<Args...> format, Args&&... args) noexcept;
	/// @brief Logs to the log service.
	/// @param logService log service.
	/// @param logType Log type.
	/// @param stacktrace Stacktrace.
	/// @param message Log message.
	/// @note The function is thread-safe.
	void LogToLogService(const ILogService& logService, LogType logType, const std::stacktrace& stacktrace, std::string_view message) noexcept;
	/// @brief Logs to the log service.
	/// @tparam Args Format argument types.
	/// @param logService log service.
	/// @param logType Log type.
	/// @param stacktrace Stacktrace.
	/// @param format Log message format.
	/// @param args Log message format arguments.
	/// @note The function is thread-safe.
	template<typename... Args>
	void LogToLogService(const ILogService& logService, LogType logType, const std::stacktrace& stacktrace, std::format_string<Args...> format, Args&&... args) noexcept;

	/// @brief Logs to the log service.
	/// @param logService log service.
	/// @param logType Log type.
	/// @param exception Exception.
	/// @note The function is thread-safe.
	void LogToLogService(const ILogService& logService, LogType logType, const std::exception_ptr& exception) noexcept;
	/// @brief Logs to the log service.
	/// @param logService log service.
	/// @param logType Log type.
	/// @param exception Exception.
	/// @param message Log message.
	/// @note The function is thread-safe.
	void LogToLogService(const ILogService& logService, LogType logType, const std::exception_ptr& exception, std::string_view message) noexcept;
	/// @brief Logs to the log service.
	/// @tparam Args Format argument types.
	/// @param logService log service.
	/// @param logType Log type.
	/// @param exception Exception.
	/// @param format Log message format.
	/// @param args Log message format arguments.
	/// @note The function is thread-safe.
	template<typename... Args>
	void LogToLogService(const ILogService& logService, LogType logType, const std::exception_ptr& exception, std::format_string<Args...> format, Args&&... args) noexcept;
	/// @brief Logs to the log service.
	/// @param logService log service.
	/// @param logType Log type.
	/// @param exception Exception.
	/// @param stacktrace Stacktrace.
	/// @note The function is thread-safe.
	void LogToLogService(const ILogService& logService, LogType logType, const std::stacktrace& stacktrace, const std::exception_ptr& exception) noexcept;
	/// @brief Logs to the log service.
	/// @param logService log service.
	/// @param logType Log type.
	/// @param exception Exception.
	/// @param stacktrace Stacktrace.
	/// @param message Log message.
	/// @note The function is thread-safe.
	void LogToLogService(const ILogService& logService, LogType logType, const std::stacktrace& stacktrace, const std::exception_ptr& exception, std::string_view message) noexcept;
	/// @brief Logs to the log service.
	/// @tparam Args Format argument types.
	/// @param logService log service.
	/// @param logType Log type.
	/// @param exception Exception.
	/// @param stacktrace Stacktrace.
	/// @param format Log message format.
	/// @param args Log message format arguments.
	/// @note The function is thread-safe.
	template<typename... Args>
	void LogToLogService(const ILogService& logService, LogType logType, const std::stacktrace& stacktrace, const std::exception_ptr& exception, std::format_string<Args...> format, Args&&... args) noexcept;

	/// @brief Logs to the log service.
	/// @param logService log service.
	/// @param logType Log type.
	/// @param message Log message.
	/// @note The function is thread-safe.
	void LogToLogService(const ILogService* logService, LogType logType, std::string_view message) noexcept;
	/// @brief Logs to the log service.
	/// @tparam Args Format argument types.
	/// @param logService log service.
	/// @param logType Log type.
	/// @param format Log message format.
	/// @param args Log message format arguments.
	/// @note The function is thread-safe.
	template<typename... Args>
	void LogToLogService(const ILogService* logService, LogType logType, std::format_string<Args...> format, Args&&... args) noexcept;
	/// @brief Logs to the log service.
	/// @param logService log service.
	/// @param logType Log type.
	/// @param stacktrace Stacktrace.
	/// @param message Log message.
	/// @note The function is thread-safe.
	void LogToLogService(const ILogService* logService, LogType logType, const std::stacktrace& stacktrace, std::string_view message) noexcept;
	/// @brief Logs to the log service.
	/// @tparam Args Format argument types.
	/// @param logService log service.
	/// @param logType Log type.
	/// @param stacktrace Stacktrace.
	/// @param format Log message format.
	/// @param args Log message format arguments.
	/// @note The function is thread-safe.
	template<typename... Args>
	void LogToLogService(const ILogService* logService, LogType logType, const std::stacktrace& stacktrace, std::format_string<Args...> format, Args&&... args) noexcept;

	/// @brief Logs to the log service.
	/// @param logService log service.
	/// @param logType Log type.
	/// @param exception Exception.
	/// @note The function is thread-safe.
	void LogToLogService(const ILogService* logService, LogType logType, const std::exception_ptr& exception) noexcept;
	/// @brief Logs to the log service.
	/// @param logService log service.
	/// @param logType Log type.
	/// @param exception Exception.
	/// @param message Log message.
	/// @note The function is thread-safe.
	void LogToLogService(const ILogService* logService, LogType logType, const std::exception_ptr& exception, std::string_view message) noexcept;
	/// @brief Logs to the log service.
	/// @tparam Args Format argument types.
	/// @param logService log service.
	/// @param logType Log type.
	/// @param exception Exception.
	/// @param format Log message format.
	/// @param args Log message format arguments.
	/// @note The function is thread-safe.
	template<typename... Args>
	void LogToLogService(const ILogService* logService, LogType logType, const std::exception_ptr& exception, std::format_string<Args...> format, Args&&... args) noexcept;
	/// @brief Logs to the log service.
	/// @param logService log service.
	/// @param logType Log type.
	/// @param exception Exception.
	/// @param stacktrace Stacktrace.
	/// @note The function is thread-safe.
	void LogToLogService(const ILogService* logService, LogType logType, const std::stacktrace& stacktrace, const std::exception_ptr& exception) noexcept;
	/// @brief Logs to the log service.
	/// @param logService log service.
	/// @param logType Log type.
	/// @param exception Exception.
	/// @param stacktrace Stacktrace.
	/// @param message Log message.
	/// @note The function is thread-safe.
	void LogToLogService(const ILogService* logService, LogType logType, const std::stacktrace& stacktrace, const std::exception_ptr& exception, std::string_view message) noexcept;
	/// @brief Logs to the log service.
	/// @tparam Args Format argument types.
	/// @param logService log service.
	/// @param logType Log type.
	/// @param exception Exception.
	/// @param stacktrace Stacktrace.
	/// @param format Log message format.
	/// @param args Log message format arguments.
	/// @note The function is thread-safe.
	template<typename... Args>
	void LogToLogService(const ILogService* logService, LogType logType, const std::stacktrace& stacktrace, const std::exception_ptr& exception, std::format_string<Args...> format, Args&&... args) noexcept;
}

namespace PonyEngine::Log
{
	void LogToLogService(const ILogService& logService, const LogType logType, const std::string_view message) noexcept
	{
		logService.Log(logType, message);
	}

	template<typename... Args>
	void LogToLogService(const ILogService& logService, const LogType logType, const std::format_string<Args...> format, Args&&... args) noexcept
	{
		logService.Log(logType, format.get(), std::make_format_args(args...));
	}

	void LogToLogService(const ILogService& logService, const LogType logType, const std::stacktrace& stacktrace, const std::string_view message) noexcept
	{
		logService.Log(logType, message, stacktrace);
	}

	template<typename... Args>
	void LogToLogService(const ILogService& logService, const LogType logType, const std::stacktrace& stacktrace, const std::format_string<Args...> format, Args&&... args) noexcept
	{
		logService.Log(logType, format.get(), std::make_format_args(args...), stacktrace);
	}

	void LogToLogService(const ILogService& logService, const LogType logType, const std::exception_ptr& exception) noexcept
	{
		logService.Log(logType, exception);
	}

	void LogToLogService(const ILogService& logService, const LogType logType, const std::exception_ptr& exception, const std::string_view message) noexcept
	{
		logService.Log(logType, exception, message);
	}

	template<typename... Args>
	void LogToLogService(const ILogService& logService, const LogType logType, const std::exception_ptr& exception, const std::format_string<Args...> format, Args&&... args) noexcept
	{
		logService.Log(logType, exception, format.get(), std::make_format_args(args...));
	}

	void LogToLogService(const ILogService& logService, const LogType logType, const std::stacktrace& stacktrace, const std::exception_ptr& exception) noexcept
	{
		logService.Log(logType, exception, stacktrace);
	}

	void LogToLogService(const ILogService& logService, const LogType logType, const std::stacktrace& stacktrace, const std::exception_ptr& exception, const std::string_view message) noexcept
	{
		logService.Log(logType, exception, message, stacktrace);
	}

	template<typename... Args>
	void LogToLogService(const ILogService& logService, const LogType logType, const std::stacktrace& stacktrace, const std::exception_ptr& exception, const std::format_string<Args...> format, Args&&... args) noexcept
	{
		logService.Log(logType, exception, format.get(), std::make_format_args(args...), stacktrace);
	}

	void LogToLogService(const ILogService* const logService, const LogType logType, const std::string_view message) noexcept
	{
		if (logService)
		{
			LogToLogService(*logService, logType, message);
		}
	}

	template<typename... Args>
	void LogToLogService(const ILogService* const logService, const LogType logType, const std::format_string<Args...> format, Args&&... args) noexcept
	{
		if (logService)
		{
			LogToLogService(*logService, logType, format, std::forward<Args>(args)...);
		}
	}

	void LogToLogService(const ILogService* const logService, const LogType logType, const std::stacktrace& stacktrace, const std::string_view message) noexcept
	{
		if (logService)
		{
			LogToLogService(*logService, logType, stacktrace, message);
		}
	}

	template<typename... Args>
	void LogToLogService(const ILogService* const logService, const LogType logType, const std::stacktrace& stacktrace, const std::format_string<Args...> format, Args&&... args) noexcept
	{
		if (logService)
		{
			LogToLogService(*logService, logType, stacktrace, format, std::forward<Args>(args)...);
		}
	}

	void LogToLogService(const ILogService* const logService, const LogType logType, const std::exception_ptr& exception) noexcept
	{
		if (logService)
		{
			LogToLogService(*logService, logType, exception);
		}
	}

	void LogToLogService(const ILogService* const logService, const LogType logType, const std::exception_ptr& exception, const std::string_view message) noexcept
	{
		if (logService)
		{
			LogToLogService(*logService, logType, exception, message);
		}
	}

	template<typename... Args>
	void LogToLogService(const ILogService* const logService, const LogType logType, const std::exception_ptr& exception, const std::format_string<Args...> format, Args&&... args) noexcept
	{
		if (logService)
		{
			LogToLogService(*logService, logType, exception, format, std::forward<Args>(args)...);
		}
	}

	void LogToLogService(const ILogService* const logService, const LogType logType, const std::stacktrace& stacktrace, const std::exception_ptr& exception) noexcept
	{
		if (logService)
		{
			LogToLogService(*logService, logType, stacktrace, exception);
		}
	}

	void LogToLogService(const ILogService* const logService, const LogType logType, const std::stacktrace& stacktrace, const std::exception_ptr& exception, const std::string_view message) noexcept
	{
		if (logService)
		{
			LogToLogService(*logService, logType, stacktrace, exception, message);
		}
	}

	template<typename... Args>
	void LogToLogService(const ILogService* const logService, const LogType logType, const std::stacktrace& stacktrace, const std::exception_ptr& exception, const std::format_string<Args...> format, Args&&... args) noexcept
	{
		if (logService)
		{
			LogToLogService(*logService, logType, stacktrace, exception, format, std::forward<Args>(args)...);
		}
	}
}
