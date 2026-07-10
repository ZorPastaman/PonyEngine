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

import PonyEngine.Application.Ext;

namespace PonyEngine::Resource::File
{
	/// @brief Gets the file resource provider module.
	/// @return File resource provider module.
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT Application::IModule* GetFileResourceProviderModule();
}
