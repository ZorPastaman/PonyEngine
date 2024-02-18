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
	export [[nodiscard("Pure function")]]
	IEngineLogger* CreateLogger(const Core::IEngine& engine)
	{
		return new Logger(engine);
	}

	export [[nodiscard("Pure function")]]
	ISubLogger* CreateConsoleSubLogger()
	{
		return new ConsoleSubLogger();
	}

	export [[nodiscard("Pure function")]]
	ISubLogger* CreateFileSubLogger(const std::filesystem::path& logPath)
	{
		return new FileSubLogger(logPath);
	}
}
