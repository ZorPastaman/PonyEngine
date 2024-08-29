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

export module Game.Implementation:GameSystemFactoryDestroyer;

import PonyEngine.Core.Factory;

import :GameSystemFactory;

export namespace Game
{
	/// @brief Game system factory destroyer.
	struct GameSystemFactoryDestroyer final : PonyEngine::Core::ISystemFactoryDestroyer
	{
		virtual void Destroy(PonyEngine::Core::ISystemFactory* factory) noexcept override;
	};
}

namespace Game
{
	void GameSystemFactoryDestroyer::Destroy(PonyEngine::Core::ISystemFactory* const factory) noexcept
	{
		assert(dynamic_cast<GameSystemFactory*>(factory) && "Tried to destroy a system factory of the wrong type.");
		delete static_cast<GameSystemFactory*>(factory);
	}
}
