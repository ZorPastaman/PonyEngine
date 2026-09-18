/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/Resource/Pack/PackServiceModule.h"

import PonyEngine.Resource.Pack.Impl;

namespace PonyEngine::Resource::Pack
{
	std::shared_ptr<Application::IModule> CreatePackServiceModule()
	{
		return std::make_shared<PackServiceModule>();
	}
}
