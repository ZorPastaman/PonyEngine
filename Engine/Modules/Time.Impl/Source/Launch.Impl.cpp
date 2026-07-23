/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/Time/TimeServiceModule.h"

import PonyEngine.Application;
import PonyEngine.Time.Impl;

namespace PonyEngine::Time
{
	std::shared_ptr<Application::IModule> CreateTimeServiceModule()
	{
		return std::make_shared<TimeServiceModule>();
	}
}
