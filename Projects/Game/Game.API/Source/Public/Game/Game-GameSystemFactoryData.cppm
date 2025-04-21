/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module Game:GameSystemFactoryData;

import <memory>;

import :GameSystemFactory;

export namespace Game
{
	/// @brief Game system factory data.
	struct GameSystemFactoryData final
	{
		std::shared_ptr<GameSystemFactory> systemFactory; ///< Game system factory.
	};
}
