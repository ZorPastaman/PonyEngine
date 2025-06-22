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

export module PonyEngine.Core:IEngineFactory;

import std;

import :IModuleContext;

export namespace PonyEngine::Core
{
	/// @brief Engine factory.
	class IEngineFactory
	{
		INTERFACE_BODY(IEngineFactory)

		/// @brief Creates an engine.
		/// @param context Module context.
		/// @return Created engine.
		[[nodiscard("Redundant call")]]
		virtual std::shared_ptr<IEngine> Create(const IModuleContext& context) = 0;
	};
}
