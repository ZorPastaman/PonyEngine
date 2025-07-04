/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/Log/LoggerModule.h"

import PonyEngine.Core;
import PonyEngine.Log.Main;

namespace PonyEngine::Log
{
	LoggerModule LoggerModule; ///< Logger module.

	Core::IModule* GetLoggerModule()
	{
		return &LoggerModule;
	}
}
