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

export module PonyEngine.Core.Implementation;

import PonyEngine.Core;
import PonyEngine.Core.Factories;

import :Engine;

namespace PonyEngine::Core
{
	/// @brief Creates a new @p Engine instance with the @p params.
	/// @param params Engine parameters.
	/// @return Created @p Engine.
	export [[nodiscard("Pure function")]]
	__declspec(dllexport) inline IEngine* CreateEngine(const EngineParams& params);

	/// @brief Destroy the @p engine instance.
	/// @param engine Engine to destroy.
	export __declspec(dllexport) inline void DestroyEngine(IEngine* engine) noexcept;

	inline IEngine* CreateEngine(const EngineParams& params)
	{
		return new Engine(params);
	}

	inline void DestroyEngine(IEngine* const engine) noexcept
	{
		assert((dynamic_cast<Engine*>(engine) != nullptr));
		delete static_cast<Engine*>(engine);
	}
}
