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

#define PONY_ENGINE_LOGGER_MODULE_NAME PonyEngineLogger

namespace PonyEngine::Log::Core
{
	/// @brief Gets the logger module.
	/// @return Logger module.
	PONY_DLL_EXPORT PonyEngine::Core::IModule* GetLoggerModule();
}
