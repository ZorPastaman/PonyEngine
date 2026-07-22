/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/Log/PlatformConsoleLoggerModule.h"

import PonyEngine.Log.PlatformConsole.Impl;

namespace PonyEngine::Log::PlatformConsole
{
	std::shared_ptr<Application::IModule> CreatePlatformConsoleLoggerModule()
	{
		return std::make_shared<PlatformConsoleLoggerModule>();
	}
}
