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

#define PONY_ENGINE_CONSOLE_SUBLOGGER_MODULE_NAME PonyEngineConsoleSubLogger

namespace PonyEngine::Log::Console
{
	/// @brief Gets the console sub-logger module.
	/// @return Console sub-logger module.
	PONY_DLL_EXPORT Core::IModule* GetConsoleModule();
}
