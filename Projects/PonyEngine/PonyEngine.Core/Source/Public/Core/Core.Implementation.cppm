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

export import PonyEngine.Core.Factory;

import :Engine;

export namespace PonyEngine::Core
{
	/// @brief Engine deleter.
	struct PONY_DLL_EXPORT EngineDeleter final
	{
		/// @brief Deletes the @p engine.
		/// @param engine Engine to delete.
		void operator ()(IAdvancedEngine* engine) const noexcept;
	};

	using EngineUniquePtr = std::unique_ptr<IAdvancedEngine, EngineDeleter>; ///< Engine unique_ptr typedef.

	/// @brief Creates a new @p Engine instance with the @p params.
	/// @param params Engine parameters.
	/// @return Created @p Engine.
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT EngineUniquePtr CreateEngine(const EngineParams& params);
}

namespace PonyEngine::Core
{
	void EngineDeleter::operator ()(IAdvancedEngine* const engine) const noexcept
	{
		assert((dynamic_cast<Engine*>(engine) && "Tried to destroy an engine of the wrong type."));
		delete static_cast<Engine*>(engine);
	}

	EngineUniquePtr CreateEngine(const EngineParams& params)
	{
		return std::unique_ptr<IAdvancedEngine, EngineDeleter>(new Engine(params));
	}
}
