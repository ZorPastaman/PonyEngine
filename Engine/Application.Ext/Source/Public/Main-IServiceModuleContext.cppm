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
	/// @note All the functions here must be called on a main thread.
	class IServiceModuleContext
	{
		PONY_INTERFACE_BODY(IServiceModuleContext)

		/// @brief Adds a service.
		/// @param factory Service factory.
		/// @return Service handle. Must be used to remove a service before a destruction of the application.
		[[nodiscard("Must be used to remove")]]
		virtual ServiceHandle AddService(const std::function<std::shared_ptr<IService>(IApplicationContext&)>& factory) = 0;
		/// @brief Removes a service.
		/// @param handle Service handle.
		virtual void RemoveService(ServiceHandle handle) = 0;
	};
}
