/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/Input/MouseProviderModule.h"

import PonyEngine.Application.Ext;
import PonyEngine.RawInput.Mouse.Impl;

namespace PonyEngine::Input
{
	Application::IModule* GetMouseProviderModule()
	{
#if PONY_WINDOWS
		static Windows::MouseProviderModule mouseProviderModule;
#else
#error "Unsupported platform!"
#endif

		return &mouseProviderModule;
	}
}
