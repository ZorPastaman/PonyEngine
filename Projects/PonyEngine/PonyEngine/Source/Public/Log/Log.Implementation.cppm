/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <cassert>

#include "PonyEngine/Compiler/Linking.h"

export module PonyEngine.Log.Implementation;

import <filesystem>;
import <functional>;
import <memory>;

import PonyEngine.Core;
import PonyEngine.Log;

import :ConsoleSubLogger;
import :FileSubLogger;
import :Logger;

export namespace PonyEngine::Log
{
	using LoggerUniquePtr = std::unique_ptr<ILogger, std::function<void(ILogger*)>>; ///< Logger unique_ptr typedef.
	using SubLoggerUniquePtr = std::unique_ptr<ISubLogger, std::function<void(ISubLogger*)>>; ///< Sub-logger unique_ptr typedef.

	/// @brief Creates a logger.
	/// @return Created logger.
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT LoggerUniquePtr CreateLogger();

	/// @brief Creates a console sub-logger.
	/// @return Created console sub-logger.
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT SubLoggerUniquePtr CreateConsoleSubLogger();

	/// @brief Creates a file sub-logger with the @p path.
	/// @param path Log file path.
	/// @return Created file sub-logger.
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT SubLoggerUniquePtr CreateFileSubLogger(const std::filesystem::path& path);
}

namespace PonyEngine::Log
{
	/// @brief Destroys a previously created logger.
	/// @param logger Logger to destroy.
	void DestroyLogger(ILogger* logger) noexcept;

	/// @brief Destroys a previously created console sub-logger.
	/// @param subLogger Console sub-logger to destroy.
	void DestroyConsoleSubLogger(ISubLogger* subLogger) noexcept;

	/// @brief Destroys a previously created file sub-logger.
	/// @param subLogger File sub-logger to destroy.
	void DestroyFileSubLogger(ISubLogger* subLogger) noexcept;

	LoggerUniquePtr CreateLogger()
	{
		return std::unique_ptr<ILogger, std::function<void(ILogger*)>>(new Logger(), DestroyLogger);
	}

	SubLoggerUniquePtr CreateConsoleSubLogger()
	{
		return std::unique_ptr<ISubLogger, std::function<void(ISubLogger*)>>(new ConsoleSubLogger(), DestroyConsoleSubLogger);
	}

	SubLoggerUniquePtr CreateFileSubLogger(const std::filesystem::path& path)
	{
		return std::unique_ptr<ISubLogger, std::function<void(ISubLogger*)>>(new FileSubLogger(path), DestroyFileSubLogger);
	}

	void DestroyLogger(ILogger* const logger) noexcept
	{
		assert((dynamic_cast<Logger*>(logger) && "A logger of the wrong type is tried to be destroyed."));
		delete static_cast<Logger*>(logger);
	}

	void DestroyConsoleSubLogger(ISubLogger* const subLogger) noexcept
	{
		assert((dynamic_cast<ConsoleSubLogger*>(subLogger) && "A console sub logger of the wrong type is tried to be destroyed."));
		delete static_cast<ConsoleSubLogger*>(subLogger);
	}

	void DestroyFileSubLogger(ISubLogger* const subLogger) noexcept
	{
		assert((dynamic_cast<FileSubLogger*>(subLogger) && "A file sub logger of the wrong type is tried to be destroyed."));
		delete static_cast<FileSubLogger*>(subLogger);
	}
}
