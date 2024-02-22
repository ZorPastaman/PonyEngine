/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module EngineRunner:EngineParams;

import PonyEngine.Core;

namespace Game
{
	static void GetLoggerParams(PonyEngine::Core::LoggerParams& loggerParams)
	{
		// Set logger parameters here
	}

	static void GetWindowParams(PonyEngine::Core::WindowParams& windowParams)
	{
		// Set window parameters here
	}

	export [[nodiscard("Pure function")]] 
	PonyEngine::Core::EngineParams GetEngineParams()
	{
		PonyEngine::Core::EngineParams engineParams;
		GetLoggerParams(engineParams.loggerParams);
		GetWindowParams(engineParams.windowParams);

		return engineParams;
	}
}
