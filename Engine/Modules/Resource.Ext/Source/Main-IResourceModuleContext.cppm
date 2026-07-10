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

export module PonyEngine.Resource.Ext:IResourceModuleContext;

import std;

import :IResourceContext;
import :IResourceProvider;
import :ResourceProviderHandle;

export namespace PonyEngine::Resource
{
	/// @brief Resource module context.
	class IResourceModuleContext
	{
		PONY_INTERFACE_BODY(IResourceModuleContext)

		/// @brief Adds a resource provider provider.
		/// @param factory Resource provider factory.
		/// @return Resource provider handle. Must be used to remove a provider before a destruction of the resource service.
		/// @note The function must be called on a main thread.
		[[nodiscard("Must be used")]]
		virtual ResourceProviderHandle AddProvider(const std::function<std::shared_ptr<IResourceProvider>(IResourceContext&)>& factory) = 0;
		/// @brief Removes a resource provider.
		/// @param providerHandle Resource provider handle.
		/// @note The function must be called on a main thread.
		virtual void RemoveProvider(ResourceProviderHandle providerHandle) = 0;
	};
}
