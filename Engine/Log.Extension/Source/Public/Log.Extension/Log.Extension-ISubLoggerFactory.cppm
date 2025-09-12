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

export module PonyEngine.Log.Extension:ISubLoggerFactory;

import std;

import :ILoggerContext;
import :SubLoggerData;

export namespace PonyEngine::Log
{
	class ISubLoggerFactory
	{
		INTERFACE_BODY(ISubLoggerFactory)

		/// @brief Creates a sub-logger.
		/// @param logger Logger context.
		/// @return Created sub-logger data.
		[[nodiscard("Redundant call")]]
		virtual SubLoggerData CreateSubLogger(ILoggerContext& logger) = 0;
	};
}
