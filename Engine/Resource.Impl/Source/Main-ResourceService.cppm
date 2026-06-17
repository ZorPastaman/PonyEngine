/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Log/Log.h"

export module PonyEngine.Resource.Impl:ResourceService;

import std;

import PonyEngine.Application.Ext;
import PonyEngine.Hash;
import PonyEngine.Log;
import PonyEngine.Resource.Ext;

import :ResourceObject;
import :ResourceContainer;
import :ResourceProviderContainer;

export namespace PonyEngine::Resource
{
	class ResourceService final : public Application::IService, public IResourceModuleContext, private Application::ITickableService, 
		private IResourceContext, private IResourceService
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit ResourceService(Application::IApplicationContext& application) noexcept;
		ResourceService(const ResourceService&) = delete;
		ResourceService(ResourceService&&) = delete;

		~ResourceService() noexcept;

		virtual void Begin() override;
		virtual void End() override;

		virtual void AddTickableServices(Application::ITickableServiceAdder& adder) override;
		virtual void AddInterfaces(Application::IServiceInterfaceAdder& adder) override;

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
		virtual bool IsResourceAvailable(ResourceID resourceId) const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual bool IsResourceAvailable(ResourceID resourceId, std::span<const std::pair<ContextKey, ContextValue>> context) const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual struct ResourceType ResourceType(ResourceID resourceId) const override;
		[[nodiscard("Pure function")]] 
		virtual std::shared_ptr<IResource> GetResource(ResourceID resourceId, std::span<const std::pair<ContextKey, ContextValue>> context) const override;

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
			virtual ResourceHandle RegisterResource(const ResourceParams& params) override;
			virtual void UnregisterResource(ResourceHandle handle) override;

			ResourceRegistry& operator =(const ResourceRegistry& other) noexcept = default;
			ResourceRegistry& operator =(ResourceRegistry&& other) noexcept = default;

		private:
			ResourceService* service;
			IResourceProvider* provider;
		};

		/// @brief Begins the providers.
		/// @param count How many providers are begun.
		void Begin(std::size_t& count);
		/// @brief Ends the providers.
		/// @param count How many providers to end.
		void End(std::size_t count) noexcept;

		[[nodiscard("Must be used")]]
		ResourceHandle AddResource(const ResourceParams& params, IResourceProvider& provider);
		void RemoveResource(ResourceHandle handle);

		[[nodiscard("Pure function")]]
		std::shared_ptr<ResourceObject> GetResourceFromCache(ResourceHandle resourceHandle) const noexcept;
		[[nodiscard("Pure function")]]
		std::shared_ptr<ResourceObject> AddResourceToCache(const ResourceEntry& resourceEntry, const VariantEntry& variantEntry) const noexcept;
		[[nodiscard("Pure function")]]
		std::shared_ptr<ResourceObject> GetResourceFromCacheUnsafe(ResourceHandle resourceHandle) const noexcept;

		Application::IApplicationContext* application;

		ResourceProviderContainer providers;
		ResourceContainer resources;
		mutable std::unordered_map<ResourceHandle, std::weak_ptr<ResourceObject>> resourceCache;
		mutable std::shared_mutex resourceMutex;
		mutable std::shared_mutex resourceCacheMutex;

		std::unordered_map<ContextKey, std::string> keyMap;
		std::unordered_map<ContextValue, std::string> valueMap;
		std::unordered_map<ResourceID, std::string> resourceIdMap;
		std::unordered_map<struct ResourceType, std::string> resourceTypeMap;

		ResourceProviderHandle nextProviderHandle;
		ResourceHandle nextResourceHandle;
	};
}

namespace PonyEngine::Resource
{
	ResourceService::ResourceService(Application::IApplicationContext& application) noexcept :
		application{&application},
		nextProviderHandle{.id = 1u},
		nextResourceHandle{.id = 1ull}
	{
	}

	ResourceService::~ResourceService() noexcept
	{
		if (!resources.Empty()) [[unlikely]]
		{
			PONY_LOG(application->Logger(), Log::LogType::Error, "Resources weren't removed:");
			for (const auto [handle, id] : resources.Handles())
			{
				PONY_LOG(application->Logger(), Log::LogType::Error, "Resource handle: '0x{:X}'; Resource ID: '0x{:X}'.", handle.id, id.value);
			}
		}

		if (providers.Size() > 0uz) [[unlikely]]
		{
			PONY_LOG(application->Logger(), Log::LogType::Error, "Resource providers weren't removed:");
			for (std::size_t i = 0uz; i < providers.Size(); ++i)
			{
				PONY_LOG(application->Logger(), Log::LogType::Error, "Provider: '{}'.", typeid(providers.Provider(i)).name());
			}
		}
	}

	void ResourceService::Begin()
	{
		std::size_t count = 0uz;
		try
		{
			Begin(count);
		}
		catch (...)
		{
			End(count);
			throw;
		}
	}

	void ResourceService::End()
	{
		End(providers.Size());
	}

	void ResourceService::AddTickableServices(Application::ITickableServiceAdder& adder)
	{
		adder.Add(*this, PONY_ENGINE_RESOURCE_TICK_ORDER);
	}

	void ResourceService::AddInterfaces(Application::IServiceInterfaceAdder& adder)
	{
		adder.AddInterface<IResourceService>(*this);
	}

	ResourceProviderHandle ResourceService::AddProvider(const std::function<std::shared_ptr<IResourceProvider>(IResourceContext&)>& factory)
	{
#ifndef NDEBUG
		if (std::this_thread::get_id() != application->MainThreadID()) [[unlikely]]
		{
			throw std::logic_error("Must be called on main thread");
		}

		if (!nextProviderHandle.IsValid()) [[unlikely]]
		{
			throw std::overflow_error("No more resource provider handles available");
		}
		if (application->FlowState() != Application::FlowState::StartingUp) [[unlikely]]
		{
			throw std::logic_error("Resource providers can be added only on start-up");
		}
#endif

		const std::shared_ptr<IResourceProvider> provider = factory(*this);
#ifndef NDEBUG
		if (!provider) [[unlikely]]
		{
			throw std::invalid_argument("Resource provider is nullptr");
		}
		if (providers.IndexOf(*provider) < providers.Size()) [[unlikely]]
		{
			throw std::invalid_argument("Resource provider has already been added");
		}
#endif

		const ResourceProviderHandle currentHandle = nextProviderHandle;
		providers.Add(currentHandle, provider);
		++nextProviderHandle.id;

		PONY_LOG(application->Logger(), Log::LogType::Info, "'{}' provider added. Handle: '0x{:X}'.", typeid(*provider).name(), currentHandle.id);

		return currentHandle;
	}

	void ResourceService::RemoveProvider(const ResourceProviderHandle providerHandle)
	{
#ifndef NDEBUG
		if (std::this_thread::get_id() != application->MainThreadID()) [[unlikely]]
		{
			throw std::logic_error("Must be called on main thread");
		}

		if (application->FlowState() != Application::FlowState::StartingUp && application->FlowState() != Application::FlowState::ShuttingDown) [[unlikely]]
		{
			throw std::logic_error("Resource provider can be removed only on start-up or shut-down");
		}
#endif

		if (const std::size_t index = providers.IndexOf(providerHandle); index < providers.Size()) [[likely]]
		{
			const char* const providerName = typeid(providers.Provider(index)).name();
			providers.Remove(index);
			PONY_LOG(application->Logger(), Log::LogType::Info, "'{}' provider removed. Handle: '0x{:X}'.", providerName, providerHandle.id);
		}
		else [[unlikely]]
		{
			throw std::invalid_argument("Resource provider not found");
		}
	}

	void ResourceService::Tick()
	{
		PONY_LOG(application->Logger(), Log::LogType::Verbose, "Ticking resource providers.");
		const auto lock = std::unique_lock(resourceMutex);

		for (std::size_t i = 0uz; i < providers.Size(); ++i)
		{
			IResourceProvider& provider = providers.Provider(i);
			auto registry = ResourceRegistry(*this, provider);

			try
			{
				PONY_LOG(application->Logger(), Log::LogType::Verbose, "Ticking '{}' provider.", typeid(provider).name());
				provider.Tick(registry);
			}
			catch (...)
			{
				PONY_LOG_X(application->Logger(), std::current_exception(), "On ticking '{}' provider.", typeid(provider).name());
				throw;
			}
		}
	}

	Application::IApplicationContext& ResourceService::Application() noexcept
	{
		return *application;
	}

	const Application::IApplicationContext& ResourceService::Application() const noexcept
	{
		return *application;
	}

	Log::ILogger& ResourceService::Logger() noexcept
	{
		return application->Logger();
	}

	const Log::ILogger& ResourceService::Logger() const noexcept
	{
		return application->Logger();
	}

	bool ResourceService::IsResourceAvailable(const ResourceID resourceId) const noexcept
	{
		const auto lock = std::shared_lock(resourceMutex);
		return resources.HasResource(resourceId);
	}

	bool ResourceService::IsResourceAvailable(const ResourceID resourceId, const std::span<const std::pair<ContextKey, ContextValue>> context) const noexcept
	{
		const auto lock = std::shared_lock(resourceMutex);
		return resources.HasResource(resourceId, context);
	}

	struct ResourceType ResourceService::ResourceType(const ResourceID resourceId) const
	{
		const auto lock = std::shared_lock(resourceMutex);
		return resources.GetResource(resourceId)->type;
	}

	std::shared_ptr<IResource> ResourceService::GetResource(const ResourceID resourceId, const std::span<const std::pair<ContextKey, ContextValue>> context) const
	{
		const auto lock = std::shared_lock(resourceMutex);

		const auto [resourceEntry, variantIndex] = resources.GetResource(resourceId, context);
		const VariantEntry& variantEntry = resourceEntry->variants[variantIndex];

		if (const std::shared_ptr<ResourceObject> resource = GetResourceFromCache(variantEntry.handle))
		{
			return resource;
		}

		return AddResourceToCache(*resourceEntry, variantEntry);
	}

	ContextKey ResourceService::MakeContextKey(const std::string_view key)
	{
		const auto contextKey = ContextKey{.value = Hash::FNV1a64(key)};

		if (const auto position = keyMap.find(contextKey); position != keyMap.cend())
		{
			if (position->second != key) [[unlikely]]
			{
				throw std::overflow_error("Hash collision");
			}
		}
		else
		{
			PONY_LOG(application->Logger(), Log::LogType::Info, "Adding new context key. Key: '{}'; ContextKey: '{}'.", key, contextKey.value);
			keyMap.emplace(contextKey, key);
		}

		return contextKey;
	}

	bool ResourceService::IsContextKeyValid(const ContextKey key) const noexcept
	{
		return keyMap.contains(key);
	}

	std::string_view ResourceService::GetContextKeyString(const ContextKey key) const
	{
		if (const auto position = keyMap.find(key); position != keyMap.cend()) [[likely]]
		{
			return position->second;
		}

		throw std::invalid_argument("Invalid key");
	}

	ContextValue ResourceService::MakeContextValue(const std::string_view value)
	{
		const auto contextValue = ContextValue{.value = Hash::FNV1a64(value)};

		if (const auto position = valueMap.find(contextValue); position != valueMap.cend())
		{
			if (position->second != value) [[unlikely]]
			{
				throw std::overflow_error("Hash collision");
			}
		}
		else
		{
			PONY_LOG(application->Logger(), Log::LogType::Info, "Adding new context value. Value: '{}'; ContextValue: '{}'.", value, contextValue.value);
			valueMap.emplace(contextValue, value);
		}

		return contextValue;
	}

	bool ResourceService::IsContextValueValid(const ContextValue value) const noexcept
	{
		return valueMap.contains(value);
	}

	std::string_view ResourceService::GetContextValueString(const ContextValue value) const
	{
		if (const auto position = valueMap.find(value); position != valueMap.cend()) [[likely]]
		{
			return position->second;
		}

		throw std::invalid_argument("Invalid value");
	}

	ResourceID ResourceService::MakeResourceID(const std::string_view resourceId)
	{
		const auto resourceIdHash = ResourceID{.value = Hash::FNV1a64(resourceId)};

		if (const auto position = resourceIdMap.find(resourceIdHash); position != resourceIdMap.cend())
		{
			if (position->second != resourceId) [[unlikely]]
			{
				throw std::overflow_error("Hash collision");
			}
		}
		else
		{
			PONY_LOG(application->Logger(), Log::LogType::Info, "Adding new resource ID. ID: '{}'; ResourceID: '{}'.", resourceId, resourceIdHash.value);
			resourceIdMap.emplace(resourceIdHash, resourceId);
		}

		return resourceIdHash;
	}

	bool ResourceService::IsResourceIDValid(const ResourceID resourceId) const noexcept
	{
		return resourceIdMap.contains(resourceId);
	}

	std::string_view ResourceService::GetResourceIDString(const ResourceID resourceId) const
	{
		if (const auto position = resourceIdMap.find(resourceId); position != resourceIdMap.cend()) [[likely]]
		{
			return position->second;
		}

		throw std::invalid_argument("Invalid resource ID");
	}

	struct ResourceType ResourceService::MakeResourceType(const std::string_view type)
	{
		const auto resourceType = Resource::ResourceType{.value = Hash::FNV1a64(type)};

		if (const auto position = resourceTypeMap.find(resourceType); position != resourceTypeMap.cend())
		{
			if (position->second != type) [[unlikely]]
			{
				throw std::overflow_error("Hash collision");
			}
		}
		else
		{
			PONY_LOG(application->Logger(), Log::LogType::Info, "Adding new resource type. type: '{}'; ResourceType: '{}'.", type, resourceType.value);
			resourceTypeMap.emplace(resourceType, type);
		}

		return resourceType;
	}

	bool ResourceService::IsResourceTypeValid(const struct ResourceType type) const noexcept
	{
		return resourceTypeMap.contains(type);
	}

	std::string_view ResourceService::GetResourceTypeString(const struct ResourceType type) const
	{
		if (const auto position = resourceTypeMap.find(type); position != resourceTypeMap.cend()) [[likely]]
		{
			return position->second;
		}

		throw std::invalid_argument("Invalid resource type");
	}

	ResourceService::ResourceRegistry::ResourceRegistry(ResourceService& service, IResourceProvider& provider) noexcept :
		service{&service},
		provider{&provider}
	{
	}

	ResourceHandle ResourceService::ResourceRegistry::RegisterResource(const ResourceParams& params)
	{
		return service->AddResource(params, *provider);
	}

	void ResourceService::ResourceRegistry::UnregisterResource(const ResourceHandle handle)
	{
		service->RemoveResource(handle);
	}

	void ResourceService::Begin(std::size_t& count)
	{
		PONY_LOG(application->Logger(), Log::LogType::Info, "Beginning resource providers...");
		for (std::size_t i = 0uz; i < providers.Size(); ++i)
		{
			IResourceProvider& provider = providers.Provider(i);
			auto registry = ResourceRegistry(*this, provider);

			try
			{
				PONY_LOG(application->Logger(), Log::LogType::Info, "Beginning '{}' resource provider...", typeid(provider).name());
				provider.Begin(registry);
				PONY_LOG(application->Logger(), Log::LogType::Info, "Beginning '{}' resource provider done.", typeid(provider).name());
				++count;
			}
			catch (...)
			{
				PONY_LOG_X(application->Logger(), std::current_exception(), "On beginning '{}' resource provider.", typeid(provider).name());
				throw;
			}
		}
		PONY_LOG(application->Logger(), Log::LogType::Info, "Beginning resource providers done.");
	}

	void ResourceService::End(const std::size_t count) noexcept
	{
		PONY_LOG(application->Logger(), Log::LogType::Info, "Ending resource providers...");
		for (std::size_t i = count; i-- > 0uz; )
		{
			IResourceProvider& provider = providers.Provider(i);
			auto registry = ResourceRegistry(*this, provider);

			try
			{
				PONY_LOG(application->Logger(), Log::LogType::Info, "Ending '{}' resource provider...", typeid(provider).name());
				provider.End(registry);
				PONY_LOG(application->Logger(), Log::LogType::Info, "Ending '{}' resource provider done.", typeid(provider).name());
			}
			catch (...)
			{
				PONY_LOG_X(application->Logger(), std::current_exception(), "On ending '{}' resource provider.", typeid(provider).name());
			}
		}
		PONY_LOG(application->Logger(), Log::LogType::Info, "Ending resource providers done.");
	}

	ResourceHandle ResourceService::AddResource(const ResourceParams& params, IResourceProvider& provider)
	{
#ifndef NDEBUG
		if (std::this_thread::get_id() != application->MainThreadID()) [[unlikely]]
		{
			throw std::logic_error("Must be called on main thread");
		}

		if (!nextResourceHandle.IsValid()) [[unlikely]]
		{
			throw std::overflow_error("No more resource handles available");
		}
		if (application->FlowState() != Application::FlowState::StartingUp) [[unlikely]]
		{
			throw std::logic_error("Resources can be added only on start-up");
		}
#endif

		const ResourceHandle currentHandle = nextResourceHandle;
		resources.AddResource(params, provider, currentHandle);
		PONY_LOG(application->Logger(), Log::LogType::Info, "Resource added. Handle: '0x{:X}'; ID: '{}'.", currentHandle.id, params.resourceId.value);
		++nextResourceHandle.id;

		return currentHandle;
	}

	void ResourceService::RemoveResource(const ResourceHandle handle)
	{
		resources.RemoveResource(handle);
		PONY_LOG(application->Logger(), Log::LogType::Info, "Resource removed. Handle: '0x{:X}'.", handle.id);
	}

	std::shared_ptr<ResourceObject> ResourceService::GetResourceFromCache(const ResourceHandle resourceHandle) const noexcept
	{
		const auto lock = std::shared_lock(resourceCacheMutex);
		return GetResourceFromCacheUnsafe(resourceHandle);
	}

	std::shared_ptr<ResourceObject> ResourceService::AddResourceToCache(const ResourceEntry& resourceEntry, const VariantEntry& variantEntry) const noexcept
	{
		const std::shared_ptr<IResourceData> data = variantEntry.provider->GetResource(variantEntry.index);
		const auto resource = std::make_shared<ResourceObject>(resourceEntry.id, resourceEntry.type, variantEntry.requiredContext, data);

		const auto lock = std::unique_lock(resourceCacheMutex);
		if (const std::shared_ptr<ResourceObject> cacheResource = GetResourceFromCacheUnsafe(variantEntry.handle)) [[unlikely]]
		{
			return cacheResource;
		}
		resourceCache[variantEntry.handle] = resource;

		return resource;
	}

	std::shared_ptr<ResourceObject> ResourceService::GetResourceFromCacheUnsafe(const ResourceHandle resourceHandle) const noexcept
	{
		if (const auto position = resourceCache.find(resourceHandle); position != resourceCache.cend())
		{
			return std::shared_ptr(position->second);
		}

		return nullptr;
	}
}
