/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Core.Factory:SystemData;

import PonyEngine.Core;

import :SystemUniquePtr;
import :ObjectInterfaces;

export namespace PonyEngine::Core
{
	/// @brief System data.
	struct SystemData final
	{
		SystemUniquePtr system; ///< System.

		ITickableSystem* tickableSystem = nullptr; ///< Tickable system. Optional.

		ObjectInterfaces publicInterfaces; ///< System public interfaces.
	};
}
