/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Utility/Base.h"

export module Game:GameSystemFactory;

import PonyEngine.Core;

export namespace Game
{
	/// @brief Game system factory.
	class GameSystemFactory : public PonyEngine::Core::ISystemFactory
	{
		BASE_BODY(GameSystemFactory)
	};
}
