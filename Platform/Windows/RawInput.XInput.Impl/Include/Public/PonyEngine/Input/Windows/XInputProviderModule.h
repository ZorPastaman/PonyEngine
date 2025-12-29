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

namespace PonyEngine::Input::Windows
{
	/// @brief Gets the XInput provider module.
	/// @return XInput provider module.
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT Application::IModule* GetXInputProviderModule();
}
