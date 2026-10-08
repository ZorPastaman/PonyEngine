/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/Resource/World/WorldDefinitionLoaderModule.h"

import PonyEngine.Resource.World.Impl;

namespace PonyEngine::Resource::World
{
	std::shared_ptr<Application::IModule> CreateWorldDefinitionLoaderModule()
	{
		return std::make_shared<WorldDefinitionLoaderModule>();
	}
}
