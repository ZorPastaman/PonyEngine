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

namespace PonyEngine::Path::Windows
{
	/// @brief Gets the Windows path service module.
	/// @return Path service module.
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT Application::IModule* GetPathModule();
}
