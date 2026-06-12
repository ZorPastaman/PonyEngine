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

export module PonyEngine.Resource.Ext:IResourceContext;

import std;

import PonyEngine.Resource;

import :ResourceHandle;
import :ResourceReference;
import :VariantHandle;

export namespace PonyEngine::Resource
{
	class IResourceContext
	{
		PONY_INTERFACE_BODY(IResourceContext)

		[[nodiscard("Pure function")]]
		virtual bool HasContextKey(ContextKey key) const noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual std::optional<ContextValue> GetContextValue(ContextKey key) const noexcept = 0;
		virtual void GetContext(std::span<std::pair<ContextKey, ContextValue>> context) const noexcept = 0;

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
		virtual ResourceAvailability IsResourceAvailable(ResourceID resourceId) const noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual struct ResourceType ResourceType(ResourceID resourceId) const = 0;

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

		[[nodiscard("Must be used")]]
		virtual ResourceHandle RegisterResource(ResourceID resourceId, struct ResourceType type) = 0;
		virtual void UnregisterResource(ResourceHandle handle) = 0;
		[[nodiscard("Must be used")]]
		virtual VariantHandle RegisterVariant(ResourceHandle resourceHandle, std::span<const std::pair<ContextKey, ContextValue>> requiredContext, 
			std::size_t index, const ResourceReference& resourceReference = ResourceReference{}) = 0;
		virtual void UnregisterVariant(VariantHandle handle) = 0;
	};
}
