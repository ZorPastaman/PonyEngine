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
		[[nodiscard("Pure function")]]
		virtual bool IsCompatible(PonyEngine::Core::ISystemFactory* factory) const noexcept override;

		virtual void Destroy(PonyEngine::Core::ISystemFactory* factory) noexcept override;
	};
}

namespace Game
{
	bool GameSystemFactoryDestroyer::IsCompatible(PonyEngine::Core::ISystemFactory* const factory) const noexcept
	{
		return dynamic_cast<GameSystemFactory*>(factory);
	}

	void GameSystemFactoryDestroyer::Destroy(PonyEngine::Core::ISystemFactory* const factory) noexcept
	{
		assert(dynamic_cast<GameSystemFactory*>(factory) && "Tried to destroy a system factory of the wrong type.");
		delete static_cast<GameSystemFactory*>(factory);
	}
}
