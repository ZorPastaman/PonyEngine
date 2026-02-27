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

export module PonyEngine.Application.Ext:IServiceModuleContext;

import std;

import :IApplicationContext;
import :IService;
import :ServiceHandle;

export namespace PonyEngine::Application
{
	/// @brief Service module context.
	class IServiceModuleContext
	{
		PONY_INTERFACE_BODY(IServiceModuleContext)

		/// @brief Adds a service.
		/// @param factory Service factory.
		/// @return Service handle. Must be used to remove a service before a destruction of the application.
		/// @note The function must be called on a main thread.
		[[nodiscard("Must be used to remove")]]
		virtual ServiceHandle AddService(const std::function<std::shared_ptr<IService>(IApplicationContext&)>& factory) = 0;
		/// @brief Removes a service.
		/// @param handle Service handle.
		/// @note The function must be called on a main thread.
		virtual void RemoveService(ServiceHandle handle) = 0;
	};
}
