/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/RawInput/RawInputServiceModule.h"

import PonyEngine.RawInput.Impl;

namespace PonyEngine::RawInput
{
	std::shared_ptr<Application::IModule> CreateRawInputServiceModule()
	{
		return std::make_shared<RawInputServiceModule>();
	}
}
