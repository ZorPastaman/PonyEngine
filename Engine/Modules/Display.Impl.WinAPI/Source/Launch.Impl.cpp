/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/Display/WinAPI/DisplayServiceModule.h"

import PonyEngine.Display.Impl.WinAPI;

namespace PonyEngine::Display
{
	std::shared_ptr<Application::IModule> CreateDisplayServiceModule()
	{
		return std::make_shared<DisplayServiceModule>();
	}
}
