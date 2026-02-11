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

export module PonyEngine.Log.Ext:ILoggerModuleContext;

import std;

import :ILoggerContext;
import :ISubLogger;
import :SubLoggerHandle;

export namespace PonyEngine::Log
{
	/// @brief Logger module context.
	/// @note All the functions here must be called on a main thread.
	class ILoggerModuleContext
	{
		PONY_INTERFACE_BODY(ILoggerModuleContext)

		/// @brief Adds a sub-logger.
		/// @param factory Sub-logger factory.
		/// @return Sub-logger handle. Must be used to remove a sub-logger before a destruction of the logger.
		[[nodiscard("Must be used to remove")]]
		virtual SubLoggerHandle AddSubLogger(const std::function<std::shared_ptr<ISubLogger>(ILoggerContext&)>& factory) = 0;
		/// @brief Removes a sub-logger.
		/// @param handle Sub-logger handle.
		virtual void RemoveSubLogger(SubLoggerHandle handle) = 0;
	};
}
