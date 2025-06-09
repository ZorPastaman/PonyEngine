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

export module PonyEngine.Log.Ext:ISubLoggerFactory;

import :ISubLogger;

export namespace PonyEngine::Log::Ext
{
	class ISubLoggerFactory
	{
		INTERFACE_BODY(ISubLoggerFactory)

		/// @brief Creates a sub-logger.
		/// @return Created sub-logger.
		[[nodiscard("Redundant call")]]
		virtual std::shared_ptr<ISubLogger> CreateSubLogger() = 0;
	};
}
