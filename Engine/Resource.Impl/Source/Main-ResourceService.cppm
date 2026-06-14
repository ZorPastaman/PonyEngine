/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <cassert>

#include "PonyEngine/Log/Log.h"

export module PonyEngine.Resource.Impl:ResourceService;

import std;

import PonyEngine.Application.Ext;
import PonyEngine.Hash;
import PonyEngine.Log;
import PonyEngine.Memory;
import PonyEngine.Resource.Ext;

import :Context;

export namespace PonyEngine::Resource
{
	class ResourceService final : public Application::IService, public IResourceModuleContext, private Application::ITickableService, private IResourceContext, private IResourceService
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit ResourceService(const Application::IApplicationContext& application);
		ResourceService(const ResourceService&) = delete;
		ResourceService(ResourceService&&) = delete;

		~ResourceService() noexcept = default;

		virtual void Begin() override;
		virtual void End() override;

		[[nodiscard("Must be used")]] 
		virtual ResourceProviderHandle AddProvider(const std::function<std::shared_ptr<IResourceProvider>(IResourceContext&)>& factory) override;
		virtual void RemoveProvider(ResourceProviderHandle providerHandle) override;

		ResourceService& operator =(const ResourceService&) = delete;
		ResourceService& operator =(ResourceService&&) = delete;

	private:
		virtual void Tick() override;

		[[nodiscard("Pure function")]] 
		virtual Application::IApplicationContext& Application() noexcept override;
		[[nodiscard("Pure function")]] 
		virtual const Application::IApplicationContext& Application() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual Log::ILogger& Logger() noexcept override;
		[[nodiscard("Pure function")]] 
		virtual const Log::ILogger& Logger() const noexcept override;

		[[nodiscard("Pure function")]] 
		virtual bool HasContextKey(ContextKey key) const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::size_t ContextSize() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual std::optional<ContextValue> GetContextValue(ContextKey key) const noexcept override;
		virtual void SetContextValue(ContextKey key, ContextValue value) override;
		virtual std::size_t GetContext(std::span<std::pair<ContextKey, ContextValue>> context) const noexcept override;
		virtual void SetContext(std::span<const std::pair<ContextKey, ContextValue>> context) override;

		[[nodiscard("Pure function")]] 
		virtual ContextKey MakeContextKey(std::string_view key) override;
		[[nodiscard("Pure function")]] 
		virtual bool IsContextKeyValid(ContextKey key) const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual std::string_view GetContextKeyString(ContextKey key) const override;
		[[nodiscard("Pure function")]] 
		virtual ContextValue MakeContextValue(std::string_view value) override;
		[[nodiscard("Pure function")]] 
		virtual bool IsContextValueValid(ContextValue value) const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual std::string_view GetContextValueString(ContextValue value) const override;

		[[nodiscard("Pure function")]] 
		virtual ResourceAvailability IsResourceAvailable(ResourceID resourceId) const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual struct ResourceType ResourceType(ResourceID resourceId) const override;
		[[nodiscard("Pure function")]] 
		virtual std::shared_ptr<IResource>LoadResource(ResourceID resourceId) const override;
		[[nodiscard("Pure function")]] 
		virtual bool IsFileReferenceAvailable(ResourceID resourceId) const override;
		[[nodiscard("Pure function")]] 
		virtual const FileReference& GetFileReference(ResourceID resourceId) const override;
		[[nodiscard("Pure function")]] 
		virtual bool IsMemoryReferenceAvailable(ResourceID resourceId) const override;
		[[nodiscard("Pure function")]] 
		virtual const MemoryReference& GetMemoryReference(ResourceID resourceId) const override;

		[[nodiscard("Pure function")]] 
		virtual ResourceID MakeResourceID(std::string_view resourceId) override;
		[[nodiscard("Pure function")]] 
		virtual bool IsResourceIDValid(ResourceID resourceId) const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual std::string_view GetResourceIDString(ResourceID resourceId) const override;

		[[nodiscard("Pure function")]] 
		virtual struct ResourceType MakeResourceType(std::string_view type) override;
		[[nodiscard("Pure function")]] 
		virtual bool IsResourceTypeValid(struct ResourceType type) const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual std::string_view GetResourceTypeString(struct ResourceType type) const override;

		virtual void AddContextObserver(IContextObserver& observer) override;
		virtual void RemoveContextObserver(IContextObserver& observer) noexcept override;

		[[nodiscard("Must be used")]]
		std::size_t UpdateResourceVariantMap(std::span<const ContextKey> changedKeys, std::span<ResourceID> changedResources) noexcept;

		[[nodiscard("Pure function")]]
		std::shared_ptr<IResource> GetResourceFromCache(ResourceID resourceId) const noexcept;
		[[nodiscard("Pure function")]]
		std::shared_ptr<IResource> GetResourceFromCacheUnsafe(ResourceID resourceId) const noexcept;
		[[nodiscard("Pure function")]]
		std::shared_ptr<IResource> GetResourceFromProvider(ResourceID resourceId) const;
		[[nodiscard("Pure function")]]
		std::shared_ptr<IResource> GetResourceFromProviderUnsafe(ResourceID resourceId) const;

		void InvokeContextChangedObservers(std::span<const ContextKey> keys) noexcept;
		void InvokeResourceChangedObservers(std::span<const ResourceID> resourceIds) noexcept;

		struct ResourceVariant final
		{
			IResourceProvider* provider;
			std::size_t index;
		};

		class ResourceRegistry final : public IResourceRegistry
		{
		public:
			[[nodiscard("Pure constructor")]]
			ResourceRegistry(ResourceService& service, IResourceProvider& provider) noexcept;
			[[nodiscard("Pure constructor")]]
			ResourceRegistry(const ResourceRegistry& other) noexcept = default;
			[[nodiscard("Pure constructor")]]
			ResourceRegistry(ResourceRegistry&& other) noexcept = default;

			~ResourceRegistry() noexcept = default;

			[[nodiscard("Must be used")]] 
			virtual ResourceHandle RegisterResource(ResourceID resourceId, struct ResourceType type) override;
			virtual void UnregisterResource(ResourceHandle handle) override;

			[[nodiscard("Must be used")]] 
			virtual VariantHandle RegisterVariant(ResourceHandle resourceHandle, const VariantParams& params) override;
			virtual void UnregisterVariant(VariantHandle handle) override;

			ResourceRegistry& operator =(const ResourceRegistry& other) noexcept = default;
			ResourceRegistry& operator =(ResourceRegistry&& other) noexcept = default;

		private:
			ResourceService* service;
			IResourceProvider* provider;
		};

		const Application::IApplicationContext* application;

		Memory::Arena arena;

		std::vector<std::shared_ptr<IResourceProvider>> providers;

		Context context;
		std::unordered_map<ResourceID, ResourceVariant> resourceVariantMap;
		std::shared_mutex stateMutex;

		mutable std::unordered_map<ResourceID, std::weak_ptr<IResource>> resourceVariantCache;
		mutable std::shared_mutex resourceVariantCacheMutex;

		std::unordered_map<ContextKey, std::string> keyMap;
	};
}

namespace PonyEngine::Resource
{
	ResourceService::ResourceService(const Application::IApplicationContext& application) :
		application{&application},
		arena(0uz, 1024uz)
	{
	}

	bool ResourceService::HasContextKey(const ContextKey key) const noexcept
	{
		const auto lock = std::shared_lock(stateMutex);

		const std::size_t index = context.Index(key);
		return context.IsValid(key, index);
	}

	std::size_t ResourceService::ContextSize() const noexcept
	{
		const auto lock = std::shared_lock(stateMutex);
		return context.Size();
	}

	std::optional<ContextValue> ResourceService::GetContextValue(const ContextKey key) const noexcept
	{
		const auto lock = std::shared_lock(stateMutex);

		const std::size_t index = context.Index(key);
		return context.IsValid(key, index) ? std::optional(context.Value(index)) : std::nullopt;
	}

	void ResourceService::SetContextValue(const ContextKey key, const ContextValue value)
	{
		const auto pair = std::pair(key, value);
		SetContext(std::span(&pair, 1uz));
	}

	std::size_t ResourceService::GetContext(const std::span<std::pair<ContextKey, ContextValue>> context) const noexcept
	{
		const auto lock = std::shared_lock(stateMutex);

		const std::size_t count = std::min(context.size(), this->context.Size());
		for (std::size_t i = 0uz; i < count; ++i)
		{
			context[i] = std::pair(this->context.Key(i), this->context.Value(i));
		}

		return count;
	}

	void ResourceService::SetContext(const std::span<const std::pair<ContextKey, ContextValue>> context)
	{
#ifndef NDEBUG
		if (std::this_thread::get_id() != application->MainThreadID()) [[unlikely]]
		{
			throw std::logic_error("Must be called on main thread");
		}

		for (std::size_t i = 1uz; i < context.size(); ++i)
		{
			for (std::size_t j = 0uz; j < i; ++j)
			{
				if (context[i].first == context[j].first) [[unlikely]]
				{
					throw std::invalid_argument("Duplicate key");
				}
			}
		}
#endif

		auto lock = std::unique_lock(stateMutex);

#ifndef NDEBUG
		for (const ContextKey key : std::views::keys(context))
		{
			if (!keyMap.contains(key)) [[unlikely]]
			{
				throw std::invalid_argument("Invalid key");
			}
		}
#endif

		arena.Free();
		const Memory::Arena::Slice<std::pair<std::size_t, ContextValue>> pairsToUpdateSlice = arena.Allocate<std::pair<std::size_t, ContextValue>>(context.size());
		const Memory::Arena::Slice<std::pair<ContextKey, ContextValue>> pairsToAddSlice = arena.Allocate<std::pair<ContextKey, ContextValue>>(context.size());
		const Memory::Arena::Slice<ContextKey> changedKeysSlice = arena.Allocate<ContextKey>(context.size());
		const Memory::Arena::Slice<ResourceID> changedResourcesSlice = arena.Allocate<ResourceID>(resourceVariantMap.size());
		const std::span<std::pair<std::size_t, ContextValue>> pairsToUpdate = arena.Span(pairsToUpdateSlice);
		const std::span<std::pair<ContextKey, ContextValue>> pairsToAdd = arena.Span(pairsToAddSlice);
		const std::span<ContextKey> changedKeys = arena.Span(changedKeysSlice);
		const std::span<ResourceID> changedResources = arena.Span(changedResourcesSlice);
		std::size_t keysToUpdateCount = 0uz;
		std::size_t keysToAddCount = 0uz;
		std::size_t changedKeysCount = 0uz;

		for (const auto [key, value] : context)
		{
			const std::size_t index = this->context.Index(key);
			const bool isValid = this->context.IsValid(key, index);

			pairsToUpdate[keysToUpdateCount] = std::pair(index, value);
			pairsToAdd[keysToAddCount] = std::pair(key, value);
			changedKeys[changedKeysCount] = key;

			const bool shouldUpdate = isValid && this->context.Value(index) != value;
			const bool shouldAdd = !isValid;

			keysToUpdateCount += shouldUpdate;
			keysToAddCount += shouldAdd;
			changedKeysCount += shouldAdd || shouldUpdate;
		}

		this->context.Reserve(keysToAddCount);
		for (const auto [index, value] : pairsToUpdate.subspan(0uz, keysToUpdateCount))
		{
			this->context.Value(index) = value;
		}
		for (const auto [key, value] : pairsToAdd.subspan(0uz, keysToAddCount))
		{
			const std::size_t index = this->context.Add(key);
			this->context.Value(index) = value;
		}

		const std::span<const ContextKey> changedKeysFinal = changedKeys.subspan(0uz, changedKeysCount);
		const std::size_t changedResourceCount = UpdateResourceVariantMap(changedKeysFinal, changedResources);

		lock.unlock();

		InvokeContextChangedObservers(changedKeysFinal);
		InvokeResourceChangedObservers(changedResources.subspan(0uz, changedResourceCount));
	}

	ContextKey ResourceService::MakeContextKey(const std::string_view key)
	{
		const auto contextKey = ContextKey{.value = Hash::FNV1a64(key)};
		if (const auto position = keyMap.find(contextKey); position != keyMap.cend())
		{
			if (position->second != key) [[unlikely]]
			{
				throw std::invalid_argument("Hash collision");
			}
		}
		else
		{
			keyMap.emplace(contextKey, key);
		}

		return contextKey;
	}

	std::shared_ptr<IResource> ResourceService::LoadResource(const ResourceID resourceId) const
	{
		if (const std::shared_ptr<IResource> cachedResource = GetResourceFromCache(resourceId))
		{
			return cachedResource;
		}

		return GetResourceFromProvider(resourceId);
	}

	std::shared_ptr<IResource> ResourceService::GetResourceFromCache(const ResourceID resourceId) const noexcept
	{
		const auto lock = std::shared_lock(resourceVariantCacheMutex);
		return GetResourceFromCacheUnsafe(resourceId);
	}

	std::shared_ptr<IResource> ResourceService::GetResourceFromCacheUnsafe(const ResourceID resourceId) const noexcept
	{
		if (const auto position = resourceVariantCache.find(resourceId); position != resourceVariantCache.cend())
		{
			if (const auto resource = std::shared_ptr(position->second))
			{
				return resource;
			}
		}

		return nullptr;
	}

	std::shared_ptr<IResource> ResourceService::GetResourceFromProvider(const ResourceID resourceId) const
	{
		const auto variantMapLock = std::shared_lock(stateMutex);
		const std::shared_ptr<IResource> resource = GetResourceFromProviderUnsafe(resourceId);
		assert(resource && "The resource is nullptr");

		const auto cacheLock = std::unique_lock(resourceVariantCacheMutex);
		if (const auto cachedResource = GetResourceFromCacheUnsafe(resourceId)) [[unlikely]]
		{
			return cachedResource;
		}
		resourceVariantCache.emplace(resourceId, resource);

		return resource;
	}

	std::shared_ptr<IResource> ResourceService::GetResourceFromProviderUnsafe(const ResourceID resourceId) const
	{
		if (const auto position = resourceVariantMap.find(resourceId); position != resourceVariantMap.cend()) [[likely]]
		{
			const auto [provider, index] = position->second;
			return provider->LoadResourceVariant(index);
		}

		throw std::invalid_argument("Invalid resource ID");
	}
}
