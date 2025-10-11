/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/Surface/SurfaceModule.h"

import PonyEngine.Application.Extension;
import PonyEngine.Surface.Main;

namespace PonyEngine::Surface
{
#if PONY_WINDOWS
	Windows::SurfaceServiceModule SurfaceModule; ///< Windows surface module.
#else
#error "Unsupported platform!"
#endif

	Application::IModule* GetSurfaceModule()
	{
		return &SurfaceModule;
	}
}
