/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/WinAPIInput/Windows/WinAPIInputModule.h"

import PonyEngine.WinAPIInput.Impl.Windows;

namespace PonyEngine::WinAPIInput
{
	std::shared_ptr<Application::IModule> CreateWinAPIInputModule()
	{
		return std::make_shared<InputDispatcherModule>();
	}
}
