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
	class IResourceRegistry
	{
		PONY_INTERFACE_BODY(IResourceRegistry)

		[[nodiscard("Must be used")]]
		virtual ResourceHandle RegisterResource(const ResourceParams& params) = 0;
		virtual void UnregisterResource(ResourceHandle handle) = 0;
	};
}
