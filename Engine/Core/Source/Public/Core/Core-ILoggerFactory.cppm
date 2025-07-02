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

export module PonyEngine.Core:ILoggerFactory;

import std;

import :ILogger;

export namespace PonyEngine::Core
{
	/// @brief Logger factory.
	class ILoggerFactory
	{
		INTERFACE_BODY(ILoggerFactory)

		/// @brief Creates a logger.
		/// @return Created logger.
		[[nodiscard("Redundant call")]]
		virtual std::shared_ptr<ILogger> Create() = 0;
	};
}
