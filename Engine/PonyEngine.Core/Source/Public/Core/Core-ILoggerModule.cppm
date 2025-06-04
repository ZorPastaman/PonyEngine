/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: cybercode.smith@pm.me                    *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <memory>

#include "PonyEngine/Utility/ObjectBody.h"

export module PonyEngine.Core:ILoggerModule;

import PonyEngine.Log;

import :IApplicationContext;
import :IModule;
import :IModuleContext;

export namespace PonyEngine::Core
{
	/// @brief Logger module.
	class ILoggerModule : public IModule
	{
		INTERFACE_BODY(ILoggerModule)

		/// @brief Creates a logger.
		/// @param moduleContext Module context.
		/// @param applicationContext Application context.
		/// @return Logger.
		[[nodiscard("Pure function")]]
		virtual std::shared_ptr<Log::ILogger> CreateLogger(IModuleContext& moduleContext, IApplicationContext& applicationContext) = 0;
	};
}
