/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/Resource/World/Hierarchy/HierarchyDeserializerModule.h"

import PonyEngine.Resource.World.Hierarchy.Impl;

namespace PonyEngine::Resource::World::Hierarchy
{
	std::shared_ptr<Application::IModule> CreateHierarchyDeserializerModule()
	{
		return std::make_shared<HierarchyDeserializerModule>();
	}
}
