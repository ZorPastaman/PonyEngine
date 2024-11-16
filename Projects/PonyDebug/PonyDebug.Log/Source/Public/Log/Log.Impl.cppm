/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Core/Linking.h"

export module PonyDebug.Log.Impl;

export import PonyDebug.Log;

import <memory>;

import PonyDebug.Log.Detail;

export namespace PonyDebug::Log
{
	/// @brief Creates a logger.
	/// @param params Logger parameters.
	/// @return Created logger.
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT LoggerData CreateLogger(const LoggerParams& params);

	/// @brief Creates a console sub-logger.
	/// @param params Console sub-logger parameters.
	/// @return Created console sub-logger.
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT ConsoleSubLoggerData CreateConsoleSubLogger(const ConsoleSubLoggerParams& params);
	/// @brief Creates a file sub-logger with the @p path.
	/// @param params File sub-logger parameters.
	/// @return Created file sub-logger.
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT FileSubLoggerData CreateFileSubLogger(const FileSubLoggerParams& params);
}

namespace PonyDebug::Log
{
	LoggerData CreateLogger(const LoggerParams& params)
	{
		return LoggerData{.logger = std::make_unique<LoggerImpl>(params)};
	}

	ConsoleSubLoggerData CreateConsoleSubLogger(const ConsoleSubLoggerParams& params)
	{
		return ConsoleSubLoggerData{.subLogger = std::make_unique<ConsoleSubLogger>(params)};
	}

	FileSubLoggerData CreateFileSubLogger(const FileSubLoggerParams& params)
	{
		return FileSubLoggerData{.subLogger = std::make_unique<FileSubLogger>(params)};
	}
}
