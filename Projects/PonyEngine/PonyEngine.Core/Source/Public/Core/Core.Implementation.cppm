/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <cassert>

#include "PonyEngine/Compiler/Linking.h"

export module PonyEngine.Core.Implementation;

export import PonyEngine.Core.Factory;

import :Engine;
import :EngineDestroyer;

export namespace PonyEngine::Core
{
	/// @brief Creates a new @p Engine instance with the @p params.
	/// @param params Engine parameters.
	/// @return Created @p Engine.
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT EngineData CreateEngine(const EngineParams& params);
}

namespace PonyEngine::Core
{
	auto DefaultEngineDestroyer = EngineDestroyer(); ///< Default engine destroyer.

	EngineData CreateEngine(const EngineParams& params)
	{
		const auto engine = new Engine(params.logger, params.systemFactories);
		const auto engineDeleter = EngineDeleter(DefaultEngineDestroyer);

		return EngineData{.engine = EngineUniquePtr(engine, engineDeleter), .tickableEngine = engine};
	}
}
