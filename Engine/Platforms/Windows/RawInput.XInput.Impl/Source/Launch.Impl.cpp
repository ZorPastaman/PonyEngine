/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/RawInput/Windows/XInputProviderModule.h"

import PonyEngine.RawInput.XInput.Impl.Windows;

namespace PonyEngine::RawInput::XInput
{
	std::shared_ptr<Application::IModule> CreateXInputProviderModule()
	{
		return std::make_shared<XInputProviderModule>();
	}
}
