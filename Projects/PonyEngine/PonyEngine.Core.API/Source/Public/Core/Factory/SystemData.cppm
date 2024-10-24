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
		SystemUniquePtr<IEngineSystem> system; ///< System.
		// TODO: Use variant for IEngineSystem and ITickableEngineSystem.
		ObjectInterfaces publicInterfaces; ///< System public interfaces.
		// TODO: Think about something that guarantees that the system actually inherits these interfaces. Maybe, it's enough to have an assert with dynamic_cast in the SystemManager
	};
}
