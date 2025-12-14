/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/Input/ControllerProviderModule.h"

import PonyEngine.Application.Ext;
import PonyEngine.RawInput.XInput.Impl;

namespace PonyEngine::Input
{
	Application::IModule* GetControllerProviderModule()
	{
#if PONY_WINDOWS
		static Windows::XInputGamepadProviderModule controllerProviderModule;
#else
#error "Unsupported platform!"
#endif

		return &controllerProviderModule;
	}
}
