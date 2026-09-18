/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/Resource/ResourceServiceModule.h"

import PonyEngine.Resource.Impl;

namespace PonyEngine::Resource
{
	std::shared_ptr<Application::IModule> CreateResourceServiceModule()
	{
		return std::make_shared<ResourceServiceModule>();
	}
}
