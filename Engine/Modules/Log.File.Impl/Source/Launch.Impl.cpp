/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/Log/FileLoggerModule.h"

import PonyEngine.Log.File.Impl;

namespace PonyEngine::Log::File
{
	std::shared_ptr<Application::IModule> CreateFileLoggerModule()
	{
		return std::make_shared<FileLoggerModule>();
	}
}
