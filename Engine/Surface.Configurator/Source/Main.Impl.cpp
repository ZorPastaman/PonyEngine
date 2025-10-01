/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/Surface/SurfaceConfiguratorModule.h"

import PonyEngine.Application;
import PonyEngine.Surface.Configurator;

namespace PonyEngine::Surface
{
	SurfaceConfiguratorModule SurfaceConfiguratorModule; ///< Surface configurator module.

	Application::IModule* GetSurfaceConfiguratorModule()
	{
		return &SurfaceConfiguratorModule;
	}
}
