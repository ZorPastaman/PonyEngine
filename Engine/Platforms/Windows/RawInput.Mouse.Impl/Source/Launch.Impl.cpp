/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/RawInput/Windows/MouseProviderModule.h"

import PonyEngine.Application;
import PonyEngine.RawInput.Mouse.Impl.Windows;

namespace PonyEngine::RawInput::Mouse
{
	Application::IModule* GetMouseProviderModule()
	{
		static MouseProviderModule mouseProviderModule;
		return &mouseProviderModule;
	}
}
