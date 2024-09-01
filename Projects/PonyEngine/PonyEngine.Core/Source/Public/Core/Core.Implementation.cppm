/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Compiler/Linking.h"

export module PonyEngine.Core.Implementation;

export import PonyEngine.Core.Factory;

import :Engine;
import :EngineDestroyer;

export namespace PonyEngine::Core
{
	/// @brief Creates an engine.
	/// @param application Application.
	/// @param params Engine parameters.
	/// @return Created engine.
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT EngineData CreateEngine(IApplication& application, const EngineParams& params);
}

namespace PonyEngine::Core
{
	auto DefaultEngineDestroyer = EngineDestroyer(); ///< Default engine destroyer.

	EngineData CreateEngine(IApplication& application, const EngineParams& params)
	{
		const auto engine = new Engine(application, params.systemFactories);
		const auto engineDeleter = EngineDeleter(DefaultEngineDestroyer);

		return EngineData{.engine = EngineUniquePtr(engine, engineDeleter), .tickableEngine = engine};
	}
}
