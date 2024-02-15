/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Debug.Log.Implementation:LoggerFactory;

import <functional>;

import :ConsoleSubLogger;
import :FileSubLogger;
import :IEngineLogger;
import :Logger;

namespace PonyEngine::Debug::Log
{
	export IEngineLogger* CreateLogger(const std::function<std::size_t()>& frameCountProvider)
	{
		return new Logger(frameCountProvider);
	}

	export ISubLogger* CreateConsoleSubLogger()
	{
		return new ConsoleSubLogger();
	}

	export ISubLogger* CreateFileSubLogger(const std::filesystem::path& logPath)
	{
		return new FileSubLogger(logPath);
	}
}
