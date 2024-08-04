/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Log:LogHelper;

import <cstddef>;
import <format>;
import <exception>;
import <string>;

import :ILogger;
import :LogInput;
import :LogType;
import :SafeFormat;

export namespace PonyEngine::Log
{
	/// @brief Additional log information.
	struct AdditionalInfo final
	{
		std::size_t frameCount = 0; ///< Frame count.
	};

	/// @brief Logs to the @p logger.
	/// @param logger Logger.
	/// @param logType Log type.
	/// @param message Log message.
	void LogToLogger(ILogger& logger, LogType logType, const char* message) noexcept;
	/// @brief Logs to the @p logger.
	/// @param logger Logger.
	/// @param logType Log type.
	/// @param additionalInfo Additional log information.
	/// @param message Log message.
	void LogToLogger(ILogger& logger, LogType logType, const AdditionalInfo& additionalInfo, const char* message) noexcept;
	/// @brief Logs to the @p logger.
	/// @tparam Args Format argument types.
	/// @param logger Logger.
	/// @param logType Log type.
	/// @param format Format.
	/// @param args Format arguments.
	template<typename... Args>
	void LogToLogger(ILogger& logger, LogType logType, std::format_string<Args...> format, Args&&... args) noexcept;
	/// @brief Logs to the @p logger.
	/// @tparam Args Format argument types.
	/// @param logger Logger.
	/// @param logType Log type.
	/// @param additionalInfo Additional log information.
	/// @param format Format.
	/// @param args Format arguments.
	template<typename... Args>
	void LogToLogger(ILogger& logger, LogType logType, const AdditionalInfo& additionalInfo, std::format_string<Args...> format, Args&&... args) noexcept;

	/// @brief Logs the @p exception to the @p logger.
	/// @param logger Logger.
	/// @param exception Exception to log.
	void LogExceptionToLogger(ILogger& logger, const std::exception& exception) noexcept;
	/// @brief Logs the @p exception to the @p logger.
	/// @param logger Logger.
	/// @param additionalInfo Additional log information.
	/// @param exception Exception to log.
	void LogExceptionToLogger(ILogger& logger, const AdditionalInfo& additionalInfo, const std::exception& exception) noexcept;
	/// @brief Logs the @p exception to the @p logger.
	/// @param logger Logger.
	/// @param exception Exception to log.
	/// @param message Log message.
	void LogExceptionToLogger(ILogger& logger, const std::exception& exception, const char* message) noexcept;
	/// @brief Logs the @p exception to the @p logger.
	/// @param logger Logger.
	/// @param additionalInfo Additional log information.
	/// @param exception Exception to log.
	/// @param message Log message.
	void LogExceptionToLogger(ILogger& logger, const AdditionalInfo& additionalInfo, const std::exception& exception, const char* message) noexcept;
	/// @brief Logs the @p exception to the @p logger.
	/// @tparam Args Format argument types.
	/// @param logger Logger.
	/// @param exception Exception to log.
	/// @param format Format.
	/// @param args Format arguments.
	template<typename... Args>
	void LogExceptionToLogger(ILogger& logger, const std::exception& exception, std::format_string<Args...> format, Args&&... args) noexcept;
	/// @brief Logs the @p exception to the @p logger.
	/// @tparam Args Format argument types.
	/// @param logger Logger.
	/// @param additionalInfo Additional log information.
	/// @param exception Exception to log.
	/// @param format Format.
	/// @param args Format arguments.
	template<typename... Args>
	void LogExceptionToLogger(ILogger& logger, const AdditionalInfo& additionalInfo, const std::exception& exception, std::format_string<Args...> format, Args&&... args) noexcept;
}

namespace PonyEngine::Log
{
	void LogToLogger(ILogger& logger, const LogType logType, const char* const message) noexcept
	{
		const auto logInput = LogInput{.message = message, .frameCount = 0};
		logger.Log(logType, logInput);
	}

	void LogToLogger(ILogger& logger, const LogType logType, const AdditionalInfo& additionalInfo, const char* const message) noexcept
	{
		const auto logInput = LogInput{.message = message, .frameCount = additionalInfo.frameCount};
		logger.Log(logType, logInput);
	}

	template<typename... Args>
	void LogToLogger(ILogger& logger, const LogType logType, std::format_string<Args...> format, Args&&... args) noexcept
	{
		LogToLogger(logger, logType, SafeFormat(format, std::forward<Args>(args)...).c_str());
	}

	template<typename... Args>
	void LogToLogger(ILogger& logger, const LogType logType, const AdditionalInfo& additionalInfo, std::format_string<Args...> format, Args&&... args) noexcept
	{
		LogToLogger(logger, logType, additionalInfo, SafeFormat(format, std::forward<Args>(args)...).c_str());
	}

	void LogExceptionToLogger(ILogger& logger, const std::exception& exception) noexcept
	{
		constexpr auto logInput = LogInput{.message = nullptr, .frameCount = 0};
		logger.LogException(exception, logInput);
	}

	void LogExceptionToLogger(ILogger& logger, const AdditionalInfo& additionalInfo, const std::exception& exception) noexcept
	{
		const auto logInput = LogInput{.message = nullptr, .frameCount = additionalInfo.frameCount};
		logger.LogException(exception, logInput);
	}

	void LogExceptionToLogger(ILogger& logger, const std::exception& exception, const char* const message) noexcept
	{
		const auto logInput = LogInput{.message = message, .frameCount = 0};
		logger.LogException(exception, logInput);
	}

	void LogExceptionToLogger(ILogger& logger, const AdditionalInfo& additionalInfo, const std::exception& exception, const char* const message) noexcept
	{
		const auto logInput = LogInput{.message = message, .frameCount = additionalInfo.frameCount};
		logger.LogException(exception, logInput);
	}

	template<typename... Args>
	void LogExceptionToLogger(ILogger& logger, const std::exception& exception, std::format_string<Args...> format, Args&&... args) noexcept
	{
		LogExceptionToLogger(logger, exception, SafeFormat(format, std::forward<Args>(args)...).c_str());
	}

	template<typename... Args>
	void LogExceptionToLogger(ILogger& logger, const AdditionalInfo& additionalInfo, const std::exception& exception, std::format_string<Args...> format, Args&&... args) noexcept
	{
		LogExceptionToLogger(logger, additionalInfo, exception, SafeFormat(format, std::forward<Args>(args)...).c_str());
	}
}
