/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <memory>

#include "PonyEngine/Utility/ObjectBody.h"

export module PonyEngine.Core:ILoggerFactory;

import PonyEngine.Log;

import :IModuleContext;

export namespace PonyEngine::Core
{
	/// @brief Logger factory.
	class ILoggerFactory
	{
		INTERFACE_BODY(ILoggerFactory)

		/// @brief Creates a logger.
		/// @param context Module context.
		/// @return Created logger.
		[[nodiscard("Redundant call")]]
		virtual std::shared_ptr<Log::ILogger> Create(const IModuleContext& context) = 0;
	};
}
