/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#pragma once

#include "PonyEngine/Utility/Compiler.h"

import PonyEngine.Application;

namespace PonyEngine::Surface::Windows
{
	/// @brief Gets the Windows surface configurator module.
	/// @return Surface configurator module.
	PONY_DLL_EXPORT Application::IModule* GetSurfaceConfiguratorModule();
}
