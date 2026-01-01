/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/Input/Windows/XInputProviderModule.h"

import PonyEngine.Application.Ext;
import PonyEngine.RawInput.XInput.Impl.Windows;

namespace PonyEngine::Input::Windows
{
	Application::IModule* GetXInputProviderModule()
	{
		static XInputProviderModule controllerProviderModule;
		return &controllerProviderModule;
	}
}
