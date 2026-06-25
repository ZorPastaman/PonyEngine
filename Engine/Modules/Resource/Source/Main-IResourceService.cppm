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

export module PonyEngine.Resource:IResourceService;

import std;

import :IFileResource;
import :ILoadableResource;
import :IMemoryResource;
import :ResourceAvailability;
import :ResourceID;
import :ResourceType;

export namespace PonyEngine::Resource
{
	class IResourceService
	{
		PONY_INTERFACE_BODY(IResourceService)

		[[nodiscard("Pure function")]]
		virtual ResourceAvailability IsResourceAvailable(ResourceID resourceId) const noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual struct ResourceType ResourceType(ResourceID resourceId) const = 0;
		[[nodiscard("Pure function")]]
		virtual std::shared_ptr<ILoadableResource> GetLoadableResource(ResourceID resourceId) const = 0;
		[[nodiscard("Pure function")]]
		virtual std::shared_ptr<IFileResource> GetFileResource(ResourceID resourceId) const = 0;
		[[nodiscard("Pure function")]]
		virtual std::shared_ptr<IMemoryResource> GetMemoryResource(ResourceID resourceId) const = 0;

		[[nodiscard("Pure function")]]
		virtual ResourceID MakeResourceID(std::string_view resourceId) = 0;
		[[nodiscard("Pure function")]]
		virtual bool IsResourceIDValid(ResourceID resourceId) const noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual std::string_view GetResourceIDString(ResourceID resourceId) const = 0;

		[[nodiscard("Pure function")]]
		virtual struct ResourceType MakeResourceType(std::string_view type) = 0;
		[[nodiscard("Pure function")]]
		virtual bool IsResourceTypeValid(struct ResourceType type) const noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual std::string_view GetResourceTypeString(struct ResourceType type) const = 0;
	};
}
