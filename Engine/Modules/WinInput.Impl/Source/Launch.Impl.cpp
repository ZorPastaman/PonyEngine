/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/WinInput/WinInputModule.h"

import PonyEngine.WinInput.Impl;

namespace PonyEngine::WinInput
{
	std::shared_ptr<Application::IModule> CreateWinInputModule()
	{
		return std::make_shared<InputDispatcherModule>();
	}
}
