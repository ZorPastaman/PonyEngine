/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Debug.Log.Implementation:LoggerFactory;

import PonyEngine.Core;

import :ConsoleSubLogger;
import :FileSubLogger;
import :IEngineLogger;
import :Logger;

namespace PonyEngine::Debug::Log
{
	/// @brief Creates an engine logger.
	/// @param engine Engine that owns the logger.
	/// @return Created logger.
	export [[nodiscard("Pure function")]]
	inline IEngineLogger* CreateLogger(const Core::IEngine& engine);

	/// @brief Create an engine console sub-logger.
	/// @return Created sub-logger.
	export [[nodiscard("Pure function")]]
	inline IEngineSubLogger* CreateConsoleSubLogger();

	/// @brief Creates an engine file sub-logger.
	/// @param logPath Log file path.
	/// @return Created sub-logger.
	export [[nodiscard("Pure function")]]
	inline IEngineSubLogger* CreateFileSubLogger(const std::filesystem::path& logPath);

	inline IEngineLogger* CreateLogger(const Core::IEngine& engine)
	{
		return new Logger(engine);
	}

	inline IEngineSubLogger* CreateConsoleSubLogger()
	{
		return new ConsoleSubLogger();
	}

	inline IEngineSubLogger* CreateFileSubLogger(const std::filesystem::path& logPath)
	{
		return new FileSubLogger(logPath);
	}
}
