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

export module PonyEngine.Engine.Extension:ISystemFactory;

import :IEngineContext;
import :SystemData;

export namespace PonyEngine::Engine
{
	/// @brief System factory.
	class ISystemFactory
	{
		INTERFACE_BODY(ISystemFactory)

		/// @brief Creates a system.
		/// @param engine Engine context.
		/// @return Created system data.
		[[nodiscard("Redundant call")]]
		virtual SystemData Create(IEngineContext& engine) = 0;
	};
}
