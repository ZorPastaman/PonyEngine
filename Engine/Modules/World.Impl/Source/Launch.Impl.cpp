/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/World/WorldServiceModule.h"

import PonyEngine.Application;
import PonyEngine.World.Impl;

namespace PonyEngine::World
{
	std::shared_ptr<Application::IModule> CreateWorldServiceModule()
	{
		return std::make_shared<WorldServiceModule>();
	}
}
