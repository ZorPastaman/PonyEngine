/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#pragma once

#include "PonyEngine/Utility/Compiler.h"

import PonyEngine.Core;

#define PONY_ENGINE_WINCORE_PLATFORM_CONSOLE_SUBLOGGER_MODULE_NAME PonyEngineWinCorePlatformConsoleSubLogger

namespace PonyEngine::Log::WinCore
{
	/// @brief Gets the WinCore platform console sub-logger module.
	/// @return Platform console sub-logger module.
	PONY_DLL_EXPORT Core::IModule* GetPlatformConsoleModule();
}
