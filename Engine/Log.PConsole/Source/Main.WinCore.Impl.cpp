/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/Log/WinCore/PlatformConsoleModule.h"

import PonyEngine.Application;
import PonyEngine.Log.PlatformConsole.WinCore;

namespace PonyEngine::Log::WinCore
{
	PlatformConsoleSubLoggerModule PlatformConsoleModule; ///< WinCore platform console sub-logger module.

	Application::IModule* GetPlatformConsoleModule()
	{
		return &PlatformConsoleModule;
	}
}
