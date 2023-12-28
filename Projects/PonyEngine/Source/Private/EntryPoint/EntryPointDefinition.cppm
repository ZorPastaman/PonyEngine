/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.EntryPoint.Definition;

import PonyEngine.EntryPoint;
import PonyEngine.IEngine;
import PonyEngine.Engine;
import PonyEngine.EngineParams;

namespace PonyEngine
{
	IEngine* CreateEngine()
	{
		EngineParams params{};
		return CreateEngineWithParams(params);
	}

	IEngine* CreateEngineWithParams(const EngineParams& params)
	{
		return new PonyEngine::Engine(params);
	}
}
