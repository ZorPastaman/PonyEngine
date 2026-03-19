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

export module PonyEngine.Application.Ext:ILoggerModuleContext;

import std;

import PonyEngine.Log;

import :ILoggerContext;
import :LoggerHandle;

export namespace PonyEngine::Application
{
	/// @brief Logger module context.
	class ILoggerModuleContext
	{
		PONY_INTERFACE_BODY(ILoggerModuleContext)

		/// @brief Sets the logger.
		/// @param factory Logger factory.
		/// @return Logger handle. Must be used to unset a logger before a destruction of the application.
		/// @note The function must be called on a main thread.
		[[nodiscard("Must be used to unset")]]
		virtual LoggerHandle SetLogger(const std::function<std::shared_ptr<Log::ILogger>(ILoggerContext&)>& factory) = 0;
		/// @brief Unsets the logger.
		/// @param handle Logger handle.
		/// @note The function must be called on a main thread.
		virtual void UnsetLogger(LoggerHandle handle) = 0;
	};
}
