/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/Log/FileSubLoggerModule.h"

import PonyEngine.Application.Ext;
import PonyEngine.Log.File.Impl;

namespace PonyEngine::Log::File
{
	Application::IModule* GetFileSubLoggerModule()
	{
		static FileSubLoggerModule fileSubLoggerModule;
		return &fileSubLoggerModule;
	}
}
