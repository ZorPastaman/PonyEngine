/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Compiler/Linking.h"

export module Game.Implementation;

export import Game.Factory;

import PonyEngine.Core;

import :GameSystemFactory;
import :GameSystemFactoryDestroyer;

export namespace Game
{
	/// @brief Creates a game system factory.
	/// @param application Application
	/// @param params Game system factory parameters.
	/// @return Game system factory.
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT GameSystemFactoryData CreateGameSystemFactory(PonyEngine::Core::IApplication& application, const GameSystemFactoryParams& params);
}

namespace Game
{
	auto DefaultGameSystemFactoryDestroyer = GameSystemFactoryDestroyer(); ///< Default game system factory destroyer.

	GameSystemFactoryData CreateGameSystemFactory(PonyEngine::Core::IApplication&, const GameSystemFactoryParams&)
	{
		const auto factory = new GameSystemFactory();
		const auto factoryDeleter = PonyEngine::Core::SystemFactoryDeleter(DefaultGameSystemFactoryDestroyer);

		return GameSystemFactoryData
		{
			.systemFactory = PonyEngine::Core::SystemFactoryUniquePtr(factory, factoryDeleter)
		};
	}
}
