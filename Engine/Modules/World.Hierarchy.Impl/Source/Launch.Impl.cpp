/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/World/Hierarchy/HierarchyService.h"

import PonyEngine.World.Hierarchy.Impl;

namespace PonyEngine::World::Hierarchy
{
	std::shared_ptr<Application::IModule> CreateHierarchyModule()
	{
		return std::make_shared<HierarchyServiceModule>();
	}
}
