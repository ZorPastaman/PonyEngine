/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/Log/LoggerModule.h"

import PonyEngine.Application.Extension;
import PonyEngine.Log.Main;

namespace PonyEngine::Log
{
	Application::IModule* GetLoggerModule()
	{
		static LoggerModule loggerModule;
		return &loggerModule;
	}
}
