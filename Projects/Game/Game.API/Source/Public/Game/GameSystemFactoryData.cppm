/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module Game:GameSystemFactoryData;

import PonyBase.Memory;

import PonyEngine.Core;

import :IGameSystemFactory;

export namespace Game
{
	/// @brief Game system factory data.
	struct GameSystemFactoryData final
	{
		PonyBase::Memory::UniquePointer<IGameSystemFactory> systemFactory; ///< Game system factory.
	};
}
