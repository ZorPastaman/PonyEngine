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

import PonyEngine.Core;

import :ILoggerContext;
import :ISubLogger;

export namespace PonyEngine::Log
{
	class ISubLoggerFactory
	{
		INTERFACE_BODY(ISubLoggerFactory)

		/// @brief Creates a sub-logger.
		/// @param logger Logger context.
		/// @return Created sub-logger.
		[[nodiscard("Redundant call")]]
		virtual std::shared_ptr<ISubLogger> CreateSubLogger(ILoggerContext& logger) = 0;

		/// @brief Gets the sub-logger order.
		/// @note The order must remain the same for the whole engine lifetime.
		/// @return Sub-logger order.
		[[nodiscard("Pure function")]]
		virtual std::int32_t Order() const noexcept = 0;
	};
}
