/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#pragma once

#include "PonyEngine/Macro/Compiler.h"

import PonyEngine.Application;

namespace PonyEngine::Resource::Pack
{
	/// @brief Gets the pack resource provider module.
	/// @return Pack resource provider module.
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT Application::IModule* GetPackResourceProviderModule();
}
