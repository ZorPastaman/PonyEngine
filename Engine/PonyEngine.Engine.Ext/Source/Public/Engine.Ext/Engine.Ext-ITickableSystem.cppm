/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Utility/ObjectBody.h"

export module PonyEngine.Engine.Ext:ITickableSystem;

import :IEngineContext;
import :ISystem;

export namespace PonyEngine::Engine
{
	/// @brief Tickable system.
	class ITickableSystem : public ISystem
	{
		INTERFACE_BODY(ITickableSystem)

		/// @brief Ticks the system.
		virtual void Tick() = 0;
	};
}
