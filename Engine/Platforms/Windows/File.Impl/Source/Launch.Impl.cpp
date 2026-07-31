/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/File/Windows/FileServiceModule.h"

import PonyEngine.File.Impl.Windows;

namespace PonyEngine::File
{
	Application::IModule* GetFileServiceModule()
	{
		static FileServiceModule fileModule;
		return &fileModule;
	}
}
