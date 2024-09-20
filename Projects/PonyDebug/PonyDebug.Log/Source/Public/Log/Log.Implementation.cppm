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
		const auto logger = new Logger();
		const auto loggerDeleter = LoggerDeleter(DefaultLoggerDestroyer);

		return LoggerData{.logger = LoggerUniquePtr(logger, loggerDeleter)};
	}

	ConsoleSubLoggerData CreateConsoleSubLogger(const ConsoleSubLoggerParams&)
	{
		const auto consoleSubLogger = new ConsoleSubLogger();
		const auto consoleSubLoggerDeleter = SubLoggerDeleter(DefaultConsoleSubLoggerDestroyer);

		return ConsoleSubLoggerData{.subLogger = SubLoggerUniquePtr(consoleSubLogger, consoleSubLoggerDeleter)};
	}

	FileSubLoggerData CreateFileSubLogger(const FileSubLoggerParams& params)
	{
		const auto fileSubLogger = new FileSubLogger(params.logPath);
		const auto fileSubLoggerDeleter = SubLoggerDeleter(DefaultFileSubLoggerDestroyer);

		return FileSubLoggerData{.subLogger = SubLoggerUniquePtr(fileSubLogger, fileSubLoggerDeleter)};
	}
}
