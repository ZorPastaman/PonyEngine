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

import <memory>;

import PonyEngine.Log;

export import Game.Factory;

import :GameSystemFactory;

export namespace Game
{
	/// @brief Game system factory deleter.
	struct PONY_DLL_EXPORT GameSystemFactoryDeleter final
	{
		/// @brief Deletes the @p factory.
		/// @param factory Game system factory to delete.
		void operator ()(IGameSystemFactory* factory) const noexcept;
	};

	using GameUniquePtr = std::unique_ptr<IGameSystemFactory, GameSystemFactoryDeleter>; ///< Game system factory unique_ptr typedef.

	/// @brief Creates a game system factory.
	/// @param logger Logger to use.
	/// @return Game system factory.
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT GameUniquePtr CreateGameSystemFactory(PonyEngine::Log::ILogger& logger);
}

namespace Game
{
	void GameSystemFactoryDeleter::operator ()(IGameSystemFactory* const factory) const noexcept
	{
		assert((dynamic_cast<GameSystemFactory*>(factory) && "Tried to destroy a game system factory of the wrong type."));
		delete static_cast<GameSystemFactory*>(factory);
	}

	GameUniquePtr CreateGameSystemFactory(PonyEngine::Log::ILogger& logger)
	{
		return std::unique_ptr<IGameSystemFactory, GameSystemFactoryDeleter>(new GameSystemFactory(logger));
	}
}
