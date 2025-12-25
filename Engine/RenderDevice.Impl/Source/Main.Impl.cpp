/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/Render/RenderDeviceServiceModule.h"

import PonyEngine.Application.Ext;
import PonyEngine.RenderDevice.Impl;

namespace PonyEngine::Render
{
	Application::IModule* GetRenderDeviceServiceModule()
	{
		static RenderDeviceServiceModule renderModule;
		return &renderModule;
	}
}
