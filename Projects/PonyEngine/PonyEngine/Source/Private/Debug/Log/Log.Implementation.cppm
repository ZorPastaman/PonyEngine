/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Debug.Log.Implementation;

import PonyEngine.Core;
import PonyEngine.Debug.Log;

export import :ConsoleSubLogger;
export import :FileSubLogger;
export import :Logger;

namespace PonyEngine::Debug::Log
{
	export ILogger* CreateLogger(Core::IEngine& engine);
	export void DestroyLogger(ILogger* logger);

	ILogger* CreateLogger(Core::IEngine& engine)
	{
		return new Logger(engine);
	}

	void DestroyLogger(ILogger* logger)
	{
		delete static_cast<Logger*>(logger);
	}
}
