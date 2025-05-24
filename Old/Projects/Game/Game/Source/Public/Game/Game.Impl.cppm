/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Core/Linking.h"

export module Game.Impl;

export import Game;

import <memory>;

import PonyEngine.Core;

import Game.Detail;

export namespace Game
{
	/// @brief Creates a game system factory.
	/// @param application Application context.
	/// @param factoryParams Game system factory parameters.
	/// @param systemParams Game system parameters.
	/// @return Game system factory.
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT GameSystemFactoryData CreateGameSystemFactory(PonyEngine::Core::IApplicationContext& application, const GameSystemFactoryParams& factoryParams, const GameSystemParams& systemParams);
}

namespace Game
{
	GameSystemFactoryData CreateGameSystemFactory(PonyEngine::Core::IApplicationContext& application, const GameSystemFactoryParams& factoryParams, const GameSystemParams& systemParams)
	{
		return GameSystemFactoryData{.systemFactory = std::make_shared<GameSystemFactoryImpl>(application, factoryParams, systemParams)};
	}
}
