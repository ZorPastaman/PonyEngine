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

import :ContextKey;
import :ContextValue;
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
		virtual bool IsResourceAvailable(ResourceID resourceId) const noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual ResourceAvailability IsResourceAvailable(ResourceID resourceId, std::span<const std::pair<ContextKey, ContextValue>> context) const noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual struct ResourceType ResourceType(ResourceID resourceId) const = 0;
		[[nodiscard("Pure function")]]
		virtual std::shared_ptr<ILoadableResource> GetLoadableResource(ResourceID resourceId, std::span<const std::pair<ContextKey, ContextValue>> context =
			std::span<const std::pair<ContextKey, ContextValue>>()) const = 0;
		[[nodiscard("Pure function")]]
		virtual std::shared_ptr<IFileResource> GetFileResource(ResourceID resourceId, std::span<const std::pair<ContextKey, ContextValue>> context =
			std::span<const std::pair<ContextKey, ContextValue>>()) const = 0;
		[[nodiscard("Pure function")]]
		virtual std::shared_ptr<IMemoryResource> GetMemoryResource(ResourceID resourceId, std::span<const std::pair<ContextKey, ContextValue>> context =
			std::span<const std::pair<ContextKey, ContextValue>>()) const = 0;

		[[nodiscard("Pure function")]]
		virtual ContextKey MakeContextKey(std::string_view key) = 0;
		[[nodiscard("Pure function")]]
		virtual bool IsContextKeyValid(ContextKey key) const noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual std::string_view GetContextKeyString(ContextKey key) const = 0;
		[[nodiscard("Pure function")]]
		virtual ContextValue MakeContextValue(std::string_view value) = 0;
		[[nodiscard("Pure function")]]
		virtual bool IsContextValueValid(ContextValue value) const noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual std::string_view GetContextValueString(ContextValue value) const = 0;

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
