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

#include "PonyEngine/Core/Linking.h"

export module PonyEngine.Core.Implementation;

import PonyEngine.Core;
import PonyEngine.Core.Factories;

import :Engine;

export namespace PonyEngine::Core
{
	/// @brief Creates a new @p Engine instance with the @p params.
	/// @param params Engine parameters.
	/// @return Created @p Engine.
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT IEngine* CreateEngine(const EngineParams& params);

	/// @brief Destroy the @p engine instance.
	/// @param engine Engine to destroy.
	PONY_DLL_EXPORT void DestroyEngine(IEngine* engine) noexcept;
}

namespace PonyEngine::Core
{
	// TODO: return std::unique_ptr with custom deleter in functions like this.

	IEngine* CreateEngine(const EngineParams& params)
	{
		return new Engine(params);
	}

	void DestroyEngine(IEngine* const engine) noexcept
	{
		assert((dynamic_cast<Engine*>(engine) != nullptr));
		delete static_cast<Engine*>(engine);
	}
}
