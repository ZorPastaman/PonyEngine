/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/World/Meta/Meta.h"

import PonyEngine.Application;
import PonyEngine.World.Meta.Impl;

namespace PonyEngine::World::Meta
{
	std::shared_ptr<Application::IModule> CreateMetaModule()
	{
		return std::make_shared<MetaModule>();
	}
}
