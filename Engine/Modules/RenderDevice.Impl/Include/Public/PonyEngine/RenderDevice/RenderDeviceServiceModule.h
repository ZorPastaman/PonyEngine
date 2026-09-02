/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#pragma once

#include "PonyCompiler.h"

import PonyEngine.Application;

namespace PonyEngine::RenderDevice
{
	/// @brief Gets the render device service module.
	/// @return Render device service module.
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT Application::IModule* GetRenderDeviceServiceModule();
}
