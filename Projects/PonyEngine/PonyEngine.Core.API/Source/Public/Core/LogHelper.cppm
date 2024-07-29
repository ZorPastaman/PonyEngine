/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Core:LogHelper;

import PonyEngine.Log;

import :IEngine;

export namespace PonyEngine::Core
{
	/// @brief Logs to the @p engine logger.
	/// @param engine Engine to use.
	/// @param logType Log type.
	/// @param message Log message.
	void LogToLogger(const IEngine& engine, Log::LogType logType, const char* message) noexcept;

	/// @brief Logs the @p exception to the @p logger.
	/// @param engine Engine to use.
	/// @param exception Exception to log.
	void LogExceptionToLogger(const IEngine& engine, const std::exception& exception) noexcept;
	/// @brief Logs the @p exception to the @p logger.
	/// @param engine Engine to use.
	/// @param exception Exception to log.
	/// @param message Log message.
	void LogExceptionToLogger(const IEngine& engine, const std::exception& exception, const char* message) noexcept;
}

namespace PonyEngine::Core
{
	void LogToLogger(const IEngine& engine, const Log::LogType logType, const char* const message) noexcept
	{
		Log::LogToLogger(engine.GetLogger(), logType, message, engine.GetTimeManager().GetFrameCount());
	}

	void LogExceptionToLogger(const IEngine& engine, const std::exception& exception) noexcept
	{
		Log::LogExceptionToLogger(engine.GetLogger(), exception, engine.GetTimeManager().GetFrameCount());
	}

	void LogExceptionToLogger(const IEngine& engine, const std::exception& exception, const char* const message) noexcept
	{
		Log::LogExceptionToLogger(engine.GetLogger(), exception, message, engine.GetTimeManager().GetFrameCount());
	}
}
