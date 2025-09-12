/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/Log/ConsoleModule.h"

import PonyEngine.Application;
import PonyEngine.Log.Console;

namespace PonyEngine::Log
{
	ConsoleSubLoggerModule ConsoleModule; ///< Console sub-logger module.

	Application::IModule* GetConsoleModule()
	{
		return &ConsoleModule;
	}
}
