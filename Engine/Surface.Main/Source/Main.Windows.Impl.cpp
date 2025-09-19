/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/Surface/Windows/SurfaceModule.h"

import PonyEngine.Application;
import PonyEngine.Surface.Main.Windows;

namespace PonyEngine::Surface::Windows
{
	SurfaceServiceModule SurfaceModule; ///< Windows surface module.

	Application::IModule* GetSurfaceModule()
	{
		return &SurfaceModule;
	}
}
