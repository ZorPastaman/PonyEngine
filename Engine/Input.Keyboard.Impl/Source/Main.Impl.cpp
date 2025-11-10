/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/Input/KeyboardProviderModule.h"

import PonyEngine.Application.Ext;
import PonyEngine.Input.Keyboard.Impl;

namespace PonyEngine::Input
{
	Application::IModule* GetKeyboardProviderModule()
	{
		static KeyboardProviderModule keyboardProviderModule;
		return &keyboardProviderModule;
	}
}
