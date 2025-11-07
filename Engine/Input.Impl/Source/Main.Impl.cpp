/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/Input/InputServiceModule.h"

import PonyEngine.Application.Ext;
import PonyEngine.Input.Impl;

namespace PonyEngine::Input
{
	Application::IModule* GetInputServiceModule()
	{
		static InputServiceModule inputModule;
		return &inputModule;
	}
}
