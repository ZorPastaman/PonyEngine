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
	class IResourceModuleContext
	{
		PONY_INTERFACE_BODY(IResourceModuleContext)

		[[nodiscard("Must be used")]]
		virtual ResourceProviderHandle AddProvider(const std::function<std::shared_ptr<IResourceProvider>(IResourceContext&)>& factory) = 0;
		virtual void RemoveProvider(ResourceProviderHandle providerHandle) = 0;
	};
}
