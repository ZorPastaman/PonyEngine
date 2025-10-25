/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/Time/TimeServiceModule.h"

import PonyEngine.Application.Extension;
import PonyEngine.Time.Main;

namespace PonyEngine::Time
{
	Application::IModule* GetTimeServiceModule()
	{
		static TimeServiceModule timeModule;
		return &timeModule;
	}
}
