/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/RawInput/Windows/KeyboardProviderModule.h"

import PonyEngine.RawInput.Keyboard.Impl.Windows;

namespace PonyEngine::RawInput::Keyboard
{
	std::shared_ptr<Application::IModule> CreateKeyboardProviderModule()
	{
		return std::make_shared<KeyboardProviderModule>();
	}
}
