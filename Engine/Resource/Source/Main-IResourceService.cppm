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
import :FileReference;
import :IContextObserver;
import :IResource;
import :MemoryReference;
import :ResourceAvailability;
import :ResourceID;
import :ResourceType;

export namespace PonyEngine::Resource
{
	class IResourceService
	{
		PONY_INTERFACE_BODY(IResourceService)

		[[nodiscard("Pure function")]]
		virtual bool HasContextKey(ContextKey key) const noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual std::size_t ContextSize() const noexcept = 0;
		[[nodiscard("Pure function")]]
		virtual std::optional<ContextValue> GetContextValue(ContextKey key) const noexcept = 0;
		virtual void SetContextValue(ContextKey key, ContextValue value) = 0;
		virtual std::size_t GetContext(std::span<std::pair<ContextKey, ContextValue>> context) const noexcept = 0;
		virtual void SetContext(std::span<const std::pair<ContextKey, ContextValue>> context) = 0;

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
		virtual std::shared_ptr<IResource> LoadResource(ResourceID resourceId) const = 0;
		[[nodiscard("Pure function")]]
		virtual bool IsFileReferenceAvailable(ResourceID resourceId) const = 0;
		[[nodiscard("Pure function")]]
		virtual const FileReference& GetFileReference(ResourceID resourceId) const = 0;
		[[nodiscard("Pure function")]]
		virtual bool IsMemoryReferenceAvailable(ResourceID resourceId) const = 0;
		[[nodiscard("Pure function")]]
		virtual const MemoryReference& GetMemoryReference(ResourceID resourceId) const = 0;

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

		virtual void AddContextObserver(IContextObserver& observer) = 0;
		virtual void RemoveContextObserver(IContextObserver& observer) noexcept = 0;
	};
}
