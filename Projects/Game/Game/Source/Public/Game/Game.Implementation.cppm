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

export module Game.Implementation;

import <functional>;
import <memory>;

import PonyEngine.Core;

import Game;

import :GameSystemFactory;

export namespace Game
{
	using GameUniquePtr = std::unique_ptr<IGameSystemFactory, std::function<void(IGameSystemFactory*)>>;

	/// @brief Creates a game system factory.
	/// @return Created game system factory.
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT GameUniquePtr CreateGameSystemFactory();
}

namespace Game
{
	/// @brief Destroys a game system factory.
	/// @param factory Game system factory.
	void DestroyGameSystemFactory(IGameSystemFactory* factory) noexcept;

	GameUniquePtr CreateGameSystemFactory()
	{
		return std::unique_ptr<IGameSystemFactory, std::function<void(IGameSystemFactory*)>>(new GameSystemFactory(), DestroyGameSystemFactory);
	}

	void DestroyGameSystemFactory(IGameSystemFactory* const factory) noexcept
	{
		assert((dynamic_cast<GameSystemFactory*>(factory) && "Tried to destroy a factory of the wrong type."));
		delete static_cast<GameSystemFactory*>(factory);
	}
}
