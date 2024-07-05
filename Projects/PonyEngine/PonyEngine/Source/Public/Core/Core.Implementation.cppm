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

import <functional>;
import <memory>;

import PonyEngine.Core;
import PonyEngine.Core.Factories;

import :Engine;

export namespace PonyEngine::Core
{
	using EngineUniquePtr = std::unique_ptr<IEngine, std::function<void(IEngine*)>>; ///< Pony Engine unique_ptr typedef.

	/// @brief Creates a new @p Engine instance with the @p params.
	/// @param params Engine parameters.
	/// @return Created @p Engine.
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT EngineUniquePtr CreateEngine(const EngineParams& params);
}

namespace PonyEngine::Core
{
	/// @brief Destroy the @p engine instance.
	/// @param engine Engine to destroy.
	void DestroyEngine(IEngine* engine) noexcept;

	EngineUniquePtr CreateEngine(const EngineParams& params)
	{
		return std::unique_ptr<IEngine, std::function<void(IEngine*)>>(new Engine(params), DestroyEngine);
	}

	void DestroyEngine(IEngine* const engine) noexcept
	{
		assert((dynamic_cast<Engine*>(engine) && "An engine of the wrong type is tried to be destroyed."));
		delete static_cast<Engine*>(engine);
	}
}
