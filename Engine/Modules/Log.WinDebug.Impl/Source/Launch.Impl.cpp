/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/Log/WinDebug/WinDebugLoggerModule.h"

import PonyEngine.Log.WinDebug.Impl;

namespace PonyEngine::Log::WinDebug
{
	std::shared_ptr<Application::IModule> CreateWinDebugLoggerModule()
	{
		return std::make_shared<WinDebugLoggerModule>();
	}
}
