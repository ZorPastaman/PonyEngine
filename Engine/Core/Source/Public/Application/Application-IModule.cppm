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

export module PonyEngine.Application:IModule;

import std;

import :IModuleContext;

export namespace PonyEngine::Application
{
	/// @brief Module.
	class IModule
	{
		INTERFACE_BODY(IModule)

		/// @brief Invoked on an application start up.
		/// @param context Module context.
		virtual void StartUp(IModuleContext& context) = 0;
		/// @brief Invoked on an application shut down.
		/// @param context Module context.
		virtual void ShutDown(const IModuleContext& context) = 0;
	};
}
