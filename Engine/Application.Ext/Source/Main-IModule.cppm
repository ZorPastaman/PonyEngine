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

export module PonyEngine.Application.Ext:IModule;

import std;

import :IModuleContext;

export namespace PonyEngine::Application
{
	/// @brief Module.
	class IModule
	{
		PONY_INTERFACE_BODY(IModule)

		/// @brief Invoked on an application start-up.
		/// @param context Module context. The context is valid only during the start-up function.
		/// @note The function is always called on a main thread.
		virtual void StartUp(IModuleContext& context) = 0;
		/// @brief Invoked on an application shut-down.
		/// @param context Module context. The context is valid only during the shut-down function.
		/// @note The function is always called on a main thread.
		virtual void ShutDown(IModuleContext& context) = 0;
	};
}
