/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/Log/Console/ConsoleLoggerModule.h"

import PonyEngine.Log.Console.Impl;

namespace PonyEngine::Log::Console
{
	std::shared_ptr<Application::IModule> CreateConsoleLoggerModule()
	{
		return std::make_shared<ConsoleLoggerModule>();
	}
}
