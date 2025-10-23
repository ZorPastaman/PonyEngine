/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/Surface/SurfaceServiceModule.h"

import PonyEngine.Application.Extension;
import PonyEngine.Surface.Main;

namespace PonyEngine::Surface
{
	Application::IModule* GetSurfaceServiceModule()
	{
#if PONY_WINDOWS
		static Windows::SurfaceServiceModule surfaceModule;
#else
#error "Unsupported platform!"
#endif

		return &surfaceModule;
	}
}
