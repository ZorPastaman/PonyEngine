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

export module PonyDebug.Log.Implementation;

export import PonyDebug.Log.Factory;

import <filesystem>;

import :ConsoleSubLogger;
import :ConsoleSubLoggerDestroyer;
import :FileSubLogger;
import :FileSubLoggerDestroyer;
import :Logger;
import :LoggerDestroyer;

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
	auto DefaultLoggerDestroyer = LoggerDestroyer(); ///< Default logger destroyer.

	auto DefaultConsoleSubLoggerDestroyer = ConsoleSubLoggerDestroyer(); ///< Default console sub-logger destroyer.
	auto DefaultFileSubLoggerDestroyer = FileSubLoggerDestroyer(); ///< Default file sub-logger destroyer.

	LoggerData CreateLogger(const LoggerParams&)
	{
		ILogger* const logger = new Logger();

		return LoggerData{.logger = LoggerUniquePtr(*logger, DefaultLoggerDestroyer)};
	}

	ConsoleSubLoggerData CreateConsoleSubLogger(const ConsoleSubLoggerParams&)
	{
		ISubLogger* const consoleSubLogger = new ConsoleSubLogger();

		return ConsoleSubLoggerData{.subLogger = SubLoggerUniquePtr(*consoleSubLogger, DefaultConsoleSubLoggerDestroyer)};
	}

	FileSubLoggerData CreateFileSubLogger(const FileSubLoggerParams& params)
	{
		ISubLogger* const fileSubLogger = new FileSubLogger(params.logPath);

		return FileSubLoggerData{.subLogger = SubLoggerUniquePtr(*fileSubLogger, DefaultFileSubLoggerDestroyer)};
	}
}
