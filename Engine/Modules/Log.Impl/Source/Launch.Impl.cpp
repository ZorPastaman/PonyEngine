/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/Log/LogServiceModule.h"

import PonyEngine.Application;
import PonyEngine.Log.Impl;

namespace PonyEngine::Log
{
	Application::IModule* GetLogServiceModule()
	{
		static LogServiceModule loggerModule;
		return &loggerModule;
	}
}
