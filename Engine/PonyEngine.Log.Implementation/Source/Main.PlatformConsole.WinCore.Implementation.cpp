/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/Log/PlatformConsole/WinCore/PlatformConsoleModule.h"

import PonyEngine.Core;
import PonyEngine.Log.PlatformConsole.WinCore;

namespace PonyEngine::Log::PlatformConsole::WinCore
{
	PlatformConsoleSubLoggerModule PlatformConsoleModule; ///< WinCore platform console sub-logger module.

	Core::IModule* GetPlatformConsoleModule()
	{
		return &PlatformConsoleModule;
	}
}
