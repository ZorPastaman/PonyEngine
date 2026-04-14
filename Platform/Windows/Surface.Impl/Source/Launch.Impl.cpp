/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/Surface/Windows/SurfaceServiceModule.h"

import PonyEngine.Application.Ext;
import PonyEngine.Surface.Impl.Windows;

namespace PonyEngine::Surface::Windows
{
	Application::IModule* GetSurfaceServiceModule()
	{
		static SurfaceServiceModule surfaceModule;
		return &surfaceModule;
	}
}
