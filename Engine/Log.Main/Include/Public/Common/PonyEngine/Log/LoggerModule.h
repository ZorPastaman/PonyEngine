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

import PonyEngine.Application.Extension;

namespace PonyEngine::Log
{
	/// @brief Gets the logger module.
	/// @return Logger module.
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT Application::IModule* GetLoggerModule();
}
