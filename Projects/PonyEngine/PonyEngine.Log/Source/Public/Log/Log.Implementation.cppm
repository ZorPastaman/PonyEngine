/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Compiler/Linking.h"

export module PonyEngine.Log.Implementation;

import <filesystem>;

export import PonyEngine.Log.Factory;

import :ConsoleSubLogger;
import :ConsoleSubLoggerDestroyer;
import :FileSubLogger;
import :FileSubLoggerDestroyer;
import :Logger;
import :LoggerDestroyer;

export namespace PonyEngine::Log
{
	/// @brief Creates a logger.
	/// @return Created logger.
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT LoggerData CreateLogger();

	/// @brief Creates a console sub-logger.
	/// @return Created console sub-logger.
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT ConsoleSubLoggerData CreateConsoleSubLogger();
	/// @brief Creates a file sub-logger with the @p path.
	/// @param path Log file path.
	/// @return Created file sub-logger.
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT FileSubLoggerData CreateFileSubLogger(const std::filesystem::path& path);
}

namespace PonyEngine::Log
{
	auto DefaultLoggerDestroyer = LoggerDestroyer(); ///< Default logger destroyer.

	auto DefaultConsoleSubLoggerDestroyer = ConsoleSubLoggerDestroyer(); ///< Default console sub-logger destroyer.
	auto DefaultFileSubLoggerDestroyer = FileSubLoggerDestroyer(); ///< Default file sub-logger destroyer.

	LoggerData CreateLogger()
	{
		const auto logger = new Logger();
		const auto loggerDeleter = LoggerDeleter(DefaultLoggerDestroyer);

		return LoggerData{.logger = LoggerUniquePtr(logger, loggerDeleter)};
	}

	ConsoleSubLoggerData CreateConsoleSubLogger()
	{
		const auto consoleSubLogger = new ConsoleSubLogger();
		const auto consoleSubLoggerDeleter = SubLoggerDeleter(DefaultConsoleSubLoggerDestroyer);

		return ConsoleSubLoggerData{.subLogger = SubLoggerUniquePtr(consoleSubLogger, consoleSubLoggerDeleter)};
	}

	FileSubLoggerData CreateFileSubLogger(const std::filesystem::path& path)
	{
		const auto fileSubLogger = new FileSubLogger(path);
		const auto fileSubLoggerDeleter = SubLoggerDeleter(DefaultFileSubLoggerDestroyer);

		return FileSubLoggerData{.subLogger = SubLoggerUniquePtr(fileSubLogger, fileSubLoggerDeleter)};
	}
}
