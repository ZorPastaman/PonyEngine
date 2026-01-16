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

namespace PonyEngine::RawInput
{
	/// @brief Gets the raw input service module.
	/// @return Raw input service module.
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT Application::IModule* GetRawInputServiceModule();
}
