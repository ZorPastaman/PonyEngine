/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/Input/Windows/KeyboardProviderModule.h"

import PonyEngine.Application.Ext;
import PonyEngine.RawInput.Keyboard.Impl.Windows;

namespace PonyEngine::Input::Windows
{
	Application::IModule* GetKeyboardProviderModule()
	{
		static KeyboardProviderModule keyboardProviderModule;
		return &keyboardProviderModule;
	}
}
