/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/RawInput/Windows/MouseProviderModule.h"

import PonyEngine.RawInput.Mouse.Impl.Windows;

namespace PonyEngine::RawInput::Mouse
{
	std::shared_ptr<Application::IModule> CreateMouseProviderModule()
	{
		return std::make_shared<MouseProviderModule>();
	}
}
