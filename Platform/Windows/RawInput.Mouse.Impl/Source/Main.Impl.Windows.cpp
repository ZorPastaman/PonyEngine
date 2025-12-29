/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/Input/Windows/MouseProviderModule.h"

import PonyEngine.Application.Ext;
import PonyEngine.RawInput.Mouse.Impl.Windows;

namespace PonyEngine::Input::Windows
{
	Application::IModule* GetMouseProviderModule()
	{
		static MouseProviderModule mouseProviderModule;
		return &mouseProviderModule;
	}
}
