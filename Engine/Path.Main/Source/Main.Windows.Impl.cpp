/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/Path/Windows/PathModule.h"

import PonyEngine.Application;
import PonyEngine.Path.Main.Windows;

namespace PonyEngine::Path::Windows
{
	PathServiceModule PathServiceModule; ///< Windows path service module.

	Application::IModule* GetPathModule()
	{
		return &PathServiceModule;
	}
}
