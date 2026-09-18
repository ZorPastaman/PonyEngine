/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/File/WinAPI/FileServiceModule.h"

import PonyEngine.File.Impl.WinAPI;

namespace PonyEngine::File
{
	std::shared_ptr<Application::IModule> CreateFileServiceModule()
	{
		return std::make_shared<FileServiceModule>();
	}
}
