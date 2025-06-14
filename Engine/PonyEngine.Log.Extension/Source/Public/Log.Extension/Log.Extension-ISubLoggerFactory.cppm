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

import :ISubLogger;

export namespace PonyEngine::Log::Extension
{
	class ISubLoggerFactory
	{
		INTERFACE_BODY(ISubLoggerFactory)

		/// @brief Creates a sub-logger.
		/// @param context Module context.
		/// @return Created sub-logger.
		[[nodiscard("Redundant call")]]
		virtual std::shared_ptr<ISubLogger> CreateSubLogger(const Core::IModuleContext& context) = 0;
	};
}
