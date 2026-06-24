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

import :IFileResourceData;
import :ILoadableResourceData;
import :IMemoryResourceData;
import :IResourceRegistry;

export namespace PonyEngine::Resource
{
	class IResourceProvider
	{
		PONY_INTERFACE_BODY(IResourceProvider)

		virtual void Begin(IResourceRegistry& registry) = 0;
		virtual void End(IResourceRegistry& registry) = 0;
		virtual void Tick(IResourceRegistry& registry) = 0;

		[[nodiscard("Pure function")]]
		virtual std::shared_ptr<ILoadableResourceData> GetLoadableResource(std::size_t index) const = 0;
		[[nodiscard("Pure function")]]
		virtual std::shared_ptr<IFileResourceData> GetFileResource(std::size_t index) const = 0;
		[[nodiscard("Pure function")]]
		virtual std::shared_ptr<IMemoryResourceData> GetMemoryResource(std::size_t index) const = 0;
	};
}
