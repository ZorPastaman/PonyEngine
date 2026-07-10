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

export module PonyEngine.Resource.Ext:IResourceRegistry;

import std;

import :ResourceHandle;
import :ResourceParams;

export namespace PonyEngine::Resource
{
	/// @brief Resource registry.
	class IResourceRegistry
	{
		PONY_INTERFACE_BODY(IResourceRegistry)

		/// @brief Registers a resource.
		/// @param params Resource parameters.
		/// @return Resource handle. Must be used to unregister it.
		/// @note Must be called on a main thread.
		[[nodiscard("Must be used")]]
		virtual ResourceHandle RegisterResource(const ResourceParams& params) = 0;
		/// @brief Unregisters a resource.
		/// @param handle Resource handle.
		virtual void UnregisterResource(ResourceHandle handle) = 0;
	};
}
