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

namespace PonyEngine::MessagePump::Windows
{
	/// @brief Gets the pump service module.
	/// @return Pump service module.
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT Application::IModule* GetPumpServiceModule();
}
