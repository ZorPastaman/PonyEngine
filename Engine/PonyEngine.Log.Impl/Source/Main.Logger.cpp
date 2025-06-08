/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/Log/Core/LoggerModule.h"

import PonyEngine.Core;
import PonyEngine.Log.Core;

namespace PonyEngine::Log::Core
{
	LoggerModule LoggerModule;

	PonyEngine::Core::IModule* GetLoggerModule()
	{
		return &LoggerModule;
	}
}
