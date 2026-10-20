/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/Resource/World/Meta/MetaDeserializerModule.h"

import PonyEngine.Resource.World.Meta.Impl;

namespace PonyEngine::Resource::World::Meta
{
	std::shared_ptr<Application::IModule> CreateMetaDeserializerModule()
	{
		return std::make_shared<MetaDeserializerModule>();
	}
}
