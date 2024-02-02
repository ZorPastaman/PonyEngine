/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Core.EngineFactory;

import "PonyAPIMacro.h";

import PonyEngine.Core.Engine;
import PonyEngine.Core.EngineParams;
import PonyEngine.Core.IEngine;

namespace PonyEngine::Core
{
	/// @brief Creates a new @p Engine instance with default parameters.
	/// @return Created @p Engine.
	export extern "C" [[nodiscard("Pure function")]]
	PONY_API IEngine* CreateEngine();

	/// @brief Creates a new @p Engine instance with the @p params.
	/// @param params Engine parameters.
	/// @return Created @p Engine.
	export extern "C" [[nodiscard("Pure function")]]
	PONY_API IEngine* CreateEngineWithParams(const EngineParams& params);
}

module : private;

namespace PonyEngine::Core
{
	IEngine* CreateEngine()
	{
		EngineParams params;
		return CreateEngineWithParams(params);
	}

	IEngine* CreateEngineWithParams(const EngineParams& params)
	{
		return new Engine(params);
	}
}
