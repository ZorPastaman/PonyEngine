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

import PonyEngine.Log;

import :GameSystemFactory;

export namespace Game
{
	using GameUniquePtr = std::unique_ptr<IGameSystemFactory, std::function<void(IGameSystemFactory*)>>; ///< Game system factory unique_ptr typedef.

	/// @brief Creates a game system factory.
	/// @param logger Logger to use.
	/// @return Game system factory.
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT GameUniquePtr CreateGameSystemFactory(PonyEngine::Log::ILogger& logger);
}

namespace Game
{
	/// @brief Destroys the game system factory.
	/// @param factory Game system factory to destroy.
	void DestroyGameSystemFactory(IGameSystemFactory* factory) noexcept;

	GameUniquePtr CreateGameSystemFactory(PonyEngine::Log::ILogger& logger)
	{
		return std::unique_ptr<IGameSystemFactory, std::function<void(IGameSystemFactory*)>>(new GameSystemFactory(logger), DestroyGameSystemFactory);
	}

	void DestroyGameSystemFactory(IGameSystemFactory* const factory) noexcept
	{
		assert((dynamic_cast<GameSystemFactory*>(factory) && "Tried to destroy a factory of the wrong type."));
		delete static_cast<GameSystemFactory*>(factory);
	}
}
