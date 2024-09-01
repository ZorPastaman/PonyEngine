/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Core:LogHelper;

import <format>;

import PonyEngine.Log;

import :IEngine;

export namespace PonyEngine::Core
{
	/// @brief Logs to the @p engine logger.
	/// @param engine Engine to use.
	/// @param logType Log type.
	/// @param message Log message.
	void LogToLogger(const IEngine& engine, Log::LogType logType, const char* message) noexcept;
	/// @brief Logs to the @p engine logger.
	/// @tparam Args Format argument types.
	/// @param engine Engine to use.
	/// @param logType Log type.
	/// @param format Format.
	/// @param args Format arguments.
	template<typename... Args>
	void LogToLogger(const IEngine& engine, Log::LogType logType, std::format_string<Args...> format, Args&&... args) noexcept;

	/// @brief Logs the @p exception to the @p logger.
	/// @param engine Engine to use.
	/// @param exception Exception to log.
	void LogExceptionToLogger(const IEngine& engine, const std::exception& exception) noexcept;
	/// @brief Logs the @p exception to the @p logger.
	/// @param engine Engine to use.
	/// @param exception Exception to log.
	/// @param message Log message.
	void LogExceptionToLogger(const IEngine& engine, const std::exception& exception, const char* message) noexcept;
	/// @brief Logs the @p exception to the @p logger.
	/// @tparam Args Format argument types.
	/// @param engine Engine to use.
	/// @param exception Exception to log.
	/// @param format Format.
	/// @param args Format arguments.
	template<typename... Args>
	void LogExceptionToLogger(const IEngine& engine, const std::exception& exception, std::format_string<Args...> format, Args&&... args) noexcept;
}

namespace PonyEngine::Core
{
	void LogToLogger(const IEngine& engine, const Log::LogType logType, const char* const message) noexcept
	{
		const auto additionalInfo = Log::AdditionalInfo{.frameCount = engine.FrameCount()};
		Log::LogToLogger(engine.Logger(), logType, additionalInfo, message);
	}

	template<typename... Args>
	void LogToLogger(const IEngine& engine, const Log::LogType logType, std::format_string<Args...> format, Args&&... args) noexcept
	{
		return LogToLogger(engine, logType, Log::SafeFormat(format, std::forward<Args>(args)...).c_str());
	}

	void LogExceptionToLogger(const IEngine& engine, const std::exception& exception) noexcept
	{
		const auto additionalInfo = Log::AdditionalInfo{.frameCount = engine.FrameCount()};
		Log::LogExceptionToLogger(engine.Logger(), additionalInfo, exception);
	}

	void LogExceptionToLogger(const IEngine& engine, const std::exception& exception, const char* const message) noexcept
	{
		const auto additionalInfo = Log::AdditionalInfo{.frameCount = engine.FrameCount()};
		Log::LogExceptionToLogger(engine.Logger(), additionalInfo, exception, message);
	}

	template<typename... Args>
	void LogExceptionToLogger(const IEngine& engine, const std::exception& exception, std::format_string<Args...> format, Args&&... args) noexcept
	{
		return LogExceptionToLogger(engine, exception, Log::SafeFormat(format, std::forward<Args>(args)...).c_str());
	}
}
