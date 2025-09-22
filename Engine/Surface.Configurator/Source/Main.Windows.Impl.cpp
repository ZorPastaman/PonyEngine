/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/Surface/Windows/SurfaceConfiguratorModule.h"

import PonyEngine.Application;
import PonyEngine.Surface.Configurator.Windows;

namespace PonyEngine::Surface::Windows
{
	SurfaceConfiguratorModule SurfaceConfiguratorModule; ///< Windows surface configurator module.

	Application::IModule* GetSurfaceConfiguratorModule()
	{
		return &SurfaceConfiguratorModule;
	}
}
