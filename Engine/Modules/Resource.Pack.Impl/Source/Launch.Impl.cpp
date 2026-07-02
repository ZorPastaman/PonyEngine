/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/Resource/PackResourceProviderModule.h"

import PonyEngine.Application.Ext;
import PonyEngine.Resource.Pack.Impl;

namespace PonyEngine::Resource::Pack
{
	Application::IModule* GetPackResourceProviderModule()
	{
		static PackResourceProviderModule packResourceProviderModule;
		return &packResourceProviderModule;
	}
}
