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

export import Game.Factory;

import <utility>;

import PonyBase.Memory;

import PonyEngine.Core;

import :GameSystemFactory;

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
		auto factory = PonyBase::Memory::UniquePointer<GameSystemFactory>::Create(application, factoryParams, systemParams);

		return GameSystemFactoryData{.systemFactory = PonyBase::Memory::UniquePointer<IGameSystemFactory>(std::move(factory))};
	}
}
