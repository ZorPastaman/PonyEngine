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

export module PonyEngine.Resource.Ext:IResourceProvider;

import std;

import PonyEngine.Resource;

export namespace PonyEngine::Resource
{
	class IResourceProvider
	{
		PONY_INTERFACE_BODY(IResourceProvider)

		[[nodiscard("Pure function")]]
		virtual std::shared_ptr<IResource> LoadResourceVariant(std::size_t index) const = 0;
	};
}
