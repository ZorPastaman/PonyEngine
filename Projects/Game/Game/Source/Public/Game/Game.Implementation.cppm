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

export module Game.Implementation;

export import Game.Factory;

import <utility>;

import PonyBase.Memory;

import PonyEngine.Core;

import :GameSystemFactory;

export namespace Game
{
	/// @brief Creates a game system factory.
	/// @param application Application context.
	/// @param params Game system factory parameters.
	/// @return Game system factory.
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT GameSystemFactoryData CreateGameSystemFactory(PonyEngine::Core::IApplicationContext& application, const GameSystemFactoryParams& params);
}

namespace Game
{
	GameSystemFactoryData CreateGameSystemFactory(PonyEngine::Core::IApplicationContext&, const GameSystemFactoryParams&)
	{
		auto factory = PonyBase::Memory::UniquePointer<GameSystemFactory>::Create();

		return GameSystemFactoryData{.systemFactory = PonyBase::Memory::UniquePointer<IGameSystemFactory>(std::move(factory))};
	}
}
