/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/RawInput/Keyboard/WinAPI/KeyboardProviderModule.h"

import PonyEngine.RawInput.Keyboard.Impl.WinAPI;

namespace PonyEngine::RawInput::Keyboard
{
	std::shared_ptr<Application::IModule> CreateKeyboardProviderModule()
	{
		return std::make_shared<KeyboardProviderModule>();
	}
}
