/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/Engine/EngineModule.h"

import PonyEngine.Application;
import PonyEngine.Engine.Main;

namespace PonyEngine::Engine
{
	EngineModule EngineModule; ///< Engine module.

	Application::IModule* GetEngineModule()
	{
		return &EngineModule;
	}
}
