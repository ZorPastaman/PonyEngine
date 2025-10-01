/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/Path/Windows/PathConfiguratorModule.h"

import PonyEngine.Application;
import PonyEngine.Path.Configurator.Windows;

namespace PonyEngine::Path::Windows
{
	PathConfiguratorModule PathConfiguratorModule; ///< Windows path configurator module.

	Application::IModule* GetPathConfiguratorModule()
	{
		return &PathConfiguratorModule;
	}
}
