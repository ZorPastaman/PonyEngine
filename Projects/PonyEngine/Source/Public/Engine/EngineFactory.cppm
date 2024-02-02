/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.EngineFactory;

import "PonyAPIMacro.h";

import PonyEngine.Engine;
import PonyEngine.IEngine;
import PonyEngine.EngineParams;

namespace PonyEngine
{
	/// @brief Creates a new @p Engine instance with default parameters.
	/// @return Created @p Engine.
	export extern "C" PONY_API IEngine* CreateEngine();

	/// @brief Creates a new @p Engine instance with the @p params.
	/// @param params Engine parameters.
	/// @return Created @p Engine.
	export extern "C" PONY_API IEngine* CreateEngineWithParams(const EngineParams& params);
}

module : private;

namespace PonyEngine
{
	IEngine* CreateEngine()
	{
		EngineParams params;
		return CreateEngineWithParams(params);
	}

	IEngine* CreateEngineWithParams(const EngineParams& params)
	{
		return new PonyEngine::Engine(params);
	}
}
