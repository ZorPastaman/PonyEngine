/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/Engine/EngineModule.h"

import PonyEngine.Core;
import PonyEngine.Engine.Core;

namespace PonyEngine::Engine
{
	EngineModule EngineModule; ///< Engine module.

	Core::IModule* GetEngineModule()
	{
		return &EngineModule;
	}
}
