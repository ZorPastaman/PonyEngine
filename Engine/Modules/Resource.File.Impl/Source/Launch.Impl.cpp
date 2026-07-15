/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/Resource/FileResourceProviderModule.h"

import PonyEngine.Application;
import PonyEngine.Resource.File.Impl;

namespace PonyEngine::Resource::File
{
	Application::IModule* GetFileResourceProviderModule()
	{
		static FileResourceProviderModule fileResourceProviderModule;
		return &fileResourceProviderModule;
	}
}
