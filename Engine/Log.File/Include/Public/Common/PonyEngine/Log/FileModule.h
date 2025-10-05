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

namespace PonyEngine::Log
{
	/// @brief Gets the file sub-logger module.
	/// @return File sub-logger module.
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT Application::IModule* GetFileModule();
}
