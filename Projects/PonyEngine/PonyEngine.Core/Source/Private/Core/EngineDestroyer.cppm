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

export module PonyEngine.Core.Implementation:EngineDestroyer;

import PonyEngine.Core.Factory;

import :Engine;

export namespace PonyEngine::Core
{
	/// @brief Engine destroyer.
	struct EngineDestroyer final : IEngineDestroyer
	{
		/// @brief Destroys the @p engine.
		/// @param engine Engine to destroy.
		virtual void Destroy(IEngine* engine) noexcept override;
	};
}

namespace PonyEngine::Core
{
	void EngineDestroyer::Destroy(IEngine* const engine) noexcept
	{
		assert((dynamic_cast<Engine*>(engine) && "Tried to destroy an engine of the wrong type."));
		delete static_cast<Engine*>(engine);
	}
}
