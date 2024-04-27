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

#include "Core/Linking.h"

export module PonyEngine.Log.Implementation;

import <filesystem>;

import PonyEngine.Core;
import PonyEngine.Log;

import :ConsoleSubLogger;
import :FileSubLogger;
import :Logger;

export namespace PonyEngine::Log
{
	/// @brief Creates a logger.
	/// @return Created logger.
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT ILogger* CreateLogger();
	/// @brief Destroys a previously created logger.
	/// @param logger Logger to destroy.
	PONY_DLL_EXPORT void DestroyLogger(ILogger* logger) noexcept;

	/// @brief Creates a console sub-logger.
	/// @return Created console sub-logger.
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT ISubLogger* CreateConsoleSubLogger();
	/// @brief Destroys a previously created console sub-logger.
	/// @param subLogger Console sub-logger to destroy.
	PONY_DLL_EXPORT void DestroyConsoleSubLogger(ISubLogger* subLogger) noexcept;

	/// @brief Creates a file sub-logger with the @p path.
	/// @param path Log file path.
	/// @return Created file sub-logger.
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT ISubLogger* CreateFileSubLogger(const std::filesystem::path& path);
	/// @brief Destroys a previously created file sub-logger.
	/// @param subLogger File sub-logger to destroy.
	PONY_DLL_EXPORT void DestroyFileSubLogger(ISubLogger* subLogger) noexcept;
}

namespace PonyEngine::Log
{
	ILogger* CreateLogger()
	{
		return new Logger();
	}

	void DestroyLogger(ILogger* const logger) noexcept
	{
		assert((dynamic_cast<Logger*>(logger) != nullptr));
		delete static_cast<Logger*>(logger);
	}

	ISubLogger* CreateConsoleSubLogger()
	{
		return new ConsoleSubLogger();
	}

	void DestroyConsoleSubLogger(ISubLogger* const subLogger) noexcept
	{
		assert((dynamic_cast<ConsoleSubLogger*>(subLogger) != nullptr));
		delete static_cast<ConsoleSubLogger*>(subLogger);
	}

	ISubLogger* CreateFileSubLogger(const std::filesystem::path& path)
	{
		return new FileSubLogger(path);
	}

	void DestroyFileSubLogger(ISubLogger* const subLogger) noexcept
	{
		assert((dynamic_cast<FileSubLogger*>(subLogger) != nullptr));
		delete static_cast<FileSubLogger*>(subLogger);
	}
}
