/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module Game.Factory:GameSystemFactoryData;

import PonyEngine.Core.Factory;

import :IGameSystemFactory;

export namespace Game
{
	/// @brief Game system factory data.
	struct GameSystemFactoryData final
	{
		PonyEngine::Core::SystemFactoryUniquePtr<IGameSystemFactory> systemFactory; ///< Game system factory.
	};
}
