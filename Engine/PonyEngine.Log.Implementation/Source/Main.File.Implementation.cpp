/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/Log/File/FileModule.h"

import PonyEngine.Core;
import PonyEngine.Log.File;

namespace PonyEngine::Log::File
{
	FileSubLoggerModule FileModule; ///< File sub-logger module.

	Core::IModule* GetFileModule()
	{
		return &FileModule;
	}
}
