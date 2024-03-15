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

export module PonyEngine.Debug.Log.Implementation;

import <filesystem>;

import PonyEngine.Core;
import PonyEngine.Debug.Log;
import PonyEngine.Debug.Log.Factories;

import :ConsoleSubLoggerFactory;
import :FileSubLoggerFactory;
import :Logger;

namespace PonyEngine::Debug::Log
{
	/// @brief Creates a logger.
	/// @param engine Engine that owns the logger.
	/// @return Created logger.
	export [[nodiscard("Pure function")]]
	inline ILogger* CreateLogger(Core::IEngine& engine);
	/// @brief Destroys a previously created logger.
	/// @param logger Logger to destroy.
	export inline void DestroyLogger(ILogger* logger) noexcept;

	/// @brief Creates a console sub-logger factory.
	/// @return Created console sub-logger factory.
	export [[nodiscard("Pure function")]]
	__declspec(dllexport) inline ISubLoggerFactory* CreateConsoleSubLoggerFactory();
	/// @brief Destroys a previously created console sub-logger factory.
	/// @param subLogger Console sub-logger factory to destroy.
	export __declspec(dllexport) inline void DestroyConsoleSubLoggerFactory(ISubLoggerFactory* subLogger);

	/// @brief Creates a file sub-logger factory with the default log file path, Log.log.
	/// @return Created file sub-logger factory.
	export [[nodiscard("Pure function")]]
	__declspec(dllexport) inline ISubLoggerFactory* CreateFileSubLoggerFactory();
	/// @brief Creates a file sub-logger factory with the @p path.
	/// @param path Log file path.
	/// @return Created file sub-logger factory.
	export [[nodiscard("Pure function")]]
	__declspec(dllexport) inline ISubLoggerFactory* CreateFileSubLoggerFactory(const std::filesystem::path& path);
	/// @brief Destroys a previously created file sub-logger factory.
	/// @param subLogger File sub-logger factory to destroy.
	export __declspec(dllexport) inline void DestroyFileSubLoggerFactory(ISubLoggerFactory* subLogger);

	inline ILogger* CreateLogger(Core::IEngine& engine)
	{
		return new Logger(engine);
	}

	inline void DestroyLogger(ILogger* const logger) noexcept
	{
		assert((dynamic_cast<Logger*>(logger) != nullptr));
		delete static_cast<Logger*>(logger);
	}

	inline ISubLoggerFactory* CreateConsoleSubLoggerFactory()
	{
		return new ConsoleSubLoggerFactory();
	}

	inline void DestroyConsoleSubLoggerFactory(ISubLoggerFactory* subLogger)
	{
		assert((dynamic_cast<ConsoleSubLoggerFactory*>(subLogger) != nullptr));
		delete static_cast<ConsoleSubLoggerFactory*>(subLogger);
	}

	inline ISubLoggerFactory* CreateFileSubLoggerFactory()
	{
		return new FileSubLoggerFactory();
	}

	inline ISubLoggerFactory* CreateFileSubLoggerFactory(const std::filesystem::path& path)
	{
		return new FileSubLoggerFactory(path);
	}

	inline void DestroyFileSubLoggerFactory(ISubLoggerFactory* subLogger)
	{
		assert((dynamic_cast<FileSubLoggerFactory*>(subLogger) != nullptr));
		delete static_cast<FileSubLoggerFactory*>(subLogger);
	}
}
