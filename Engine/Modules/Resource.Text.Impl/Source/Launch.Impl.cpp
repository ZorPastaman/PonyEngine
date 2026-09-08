/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/Resource/Text/TextLoaderModule.h"

import PonyEngine.Resource.Text.Impl;

namespace PonyEngine::Resource::Text
{
	std::shared_ptr<Application::IModule> CreateTextLoaderModule()
	{
		return std::make_shared<TextLoaderModule>();
	}
}
