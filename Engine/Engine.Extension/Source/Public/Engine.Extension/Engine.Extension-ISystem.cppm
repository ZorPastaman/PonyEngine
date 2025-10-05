/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Object/Body.h"

export module PonyEngine.Engine.Extension:ISystem;

import :IEngineContext;

export namespace PonyEngine::Engine
{
	/// @brief System.
	class ISystem
	{
		INTERFACE_BODY(ISystem)

		/// @brief Begins the system.
		/// @details It's called once before a first engine tick.
		virtual void Begin() = 0;
		/// @brief Ends the system.
		/// @details It's called once after a last engine tick.
		virtual void End() = 0;
	};
}
