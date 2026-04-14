/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/RawInput/RawInputServiceModule.h"

import PonyEngine.Application.Ext;
import PonyEngine.RawInput.Impl;

namespace PonyEngine::RawInput
{
	Application::IModule* GetRawInputServiceModule()
	{
		static RawInputServiceModule inputModule;
		return &inputModule;
	}
}
