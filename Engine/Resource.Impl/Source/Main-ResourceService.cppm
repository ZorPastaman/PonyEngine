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
import PonyEngine.Memory;
import PonyEngine.Resource.Ext;

import :FileResource;
import :LoadableResource;
import :MemoryResource;
import :ResourceContainer;
import :ResourceProviderContainer;

export namespace PonyEngine::Resource
{
	class ResourceService final : public Application::IService, public IResourceModuleContext, private Application::ITickableService, 
		private IResourceContext, private IResourceService
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit ResourceService(Application::IApplicationContext& application);
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
		virtual ResourceAvailability IsResourceAvailable(ResourceID resourceId, std::span<const std::pair<ContextKey, ContextValue>> context) const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual struct ResourceType ResourceType(ResourceID resourceId) const override;
		[[nodiscard("Pure function")]] 
		virtual std::shared_ptr<ILoadableResource> GetLoadableResource(ResourceID resourceId, std::span<const std::pair<ContextKey, ContextValue>> context) const override;
		[[nodiscard("Pure function")]] 
		virtual std::shared_ptr<IFileResource> GetFileResource(ResourceID resourceId, std::span<const std::pair<ContextKey, ContextValue>> context) const override;
		[[nodiscard("Pure function")]] 
		virtual std::shared_ptr<IMemoryResource> GetMemoryResource(ResourceID resourceId, std::span<const std::pair<ContextKey, ContextValue>> context) const override;

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

		template<std::derived_from<IResource> ResourceT, typename ResourceD> [[nodiscard("Pure function")]]
		std::shared_ptr<ResourceT> GetResource(ResourceID resourceId, std::span<const std::pair<ContextKey, ContextValue>> context, 
			std::unordered_map<ResourceHandle, std::weak_ptr<ResourceT>>& map, std::shared_mutex& mapMutex,
			const std::function<std::shared_ptr<ResourceD>(const VariantEntry&)>& dataGetter) const;
		[[nodiscard("Pure function")]]
		std::pair<const ResourceEntry&, const VariantEntry&> GetResource(ResourceID resourceId, std::span<const std::pair<ContextKey, ContextValue>> context) const;
		[[nodiscard("Must be used")]]
		ResourceHandle AddResource(const ResourceParams& params, IResourceProvider& provider);
		void RemoveResource(ResourceHandle handle);

		template<std::derived_from<IResource> ResourceT> [[nodiscard("Pure function")]]
		static std::shared_ptr<ResourceT> GetResourceFromCache(ResourceHandle resourceHandle, 
			const std::unordered_map<ResourceHandle, std::weak_ptr<ResourceT>>& map, std::shared_mutex& mutex) noexcept;
		template<std::derived_from<IResource> ResourceT, typename ResourceD> [[nodiscard("Pure function")]]
		static std::shared_ptr<ResourceT> AddResourceToCache(const ResourceEntry& resourceEntry, const VariantEntry& variantEntry, const std::shared_ptr<ResourceD>& data,
			std::unordered_map<ResourceHandle, std::weak_ptr<ResourceT>>& map, std::shared_mutex& mutex);
		template<std::derived_from<IResource> ResourceT> [[nodiscard("Pure function")]]
		static std::shared_ptr<ResourceT> GetResourceFromCacheUnsafe(ResourceHandle resourceHandle, 
			const std::unordered_map<ResourceHandle, std::weak_ptr<ResourceT>>& map) noexcept;

		[[nodiscard("Pure function")]]
		static Memory::Arena& Arena();

		Application::IApplicationContext* application;

		ResourceProviderContainer providers;

		ResourceContainer resources;
		mutable std::shared_mutex resourceMutex;

		mutable std::unordered_map<ResourceHandle, std::weak_ptr<LoadableResource>> loadableResourceCache;
		mutable std::shared_mutex loadableResourceCacheMutex;

		mutable std::unordered_map<ResourceHandle, std::weak_ptr<FileResource>> fileResourceCache;
		mutable std::shared_mutex fileResourceCacheMutex;

		mutable std::unordered_map<ResourceHandle, std::weak_ptr<MemoryResource>> memoryResourceCache;
		mutable std::shared_mutex memoryResourceCacheMutex;

		std::unordered_map<ContextKey, std::string> keyMap;
		mutable std::shared_mutex keyMapMutex;
		std::unordered_map<ContextValue, std::string> valueMap;
		mutable std::shared_mutex valueMapMutex;
		std::unordered_map<ResourceID, std::string> resourceIdMap;
		mutable std::shared_mutex resourceIdMapMutex;
		std::unordered_map<struct ResourceType, std::string> resourceTypeMap;
		mutable std::shared_mutex resourceTypeMapMutex;

		ResourceProviderHandle nextProviderHandle;
		ResourceHandle nextResourceHandle;
	};
}

namespace PonyEngine::Resource
{
	ResourceService::ResourceService(Application::IApplicationContext& application) :
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
#ifndef NDEBUG
		PONY_LOG_IF(!IsResourceIDValid(resourceId), application->Logger(), Log::LogType::Warning, "Invalid resource ID: '{}'.", resourceId.value);
#endif

		const auto lock = std::shared_lock(resourceMutex);
		return resources.GetResource(resourceId);
	}

	ResourceAvailability ResourceService::IsResourceAvailable(const ResourceID resourceId, const std::span<const std::pair<ContextKey, ContextValue>> context) const noexcept
	{
#ifndef NDEBUG
		PONY_LOG_IF(!IsResourceIDValid(resourceId), application->Logger(), Log::LogType::Warning, "Invalid resource ID: '{}'.", resourceId.value);
#endif

		Memory::Arena& arena = Arena();
		arena.Free();

		const Memory::Arena::Slice<std::pair<ContextKey, ContextValue>> sortedContextSlice = arena.Allocate<std::pair<ContextKey, ContextValue>>(context.size());
		const std::span<std::pair<ContextKey, ContextValue>> sortedContext = arena.Span(sortedContextSlice);
		std::memcpy(sortedContext.data(), context.data(), sortedContext.size_bytes());
		ResourceContainer::SortContext(sortedContext);

#ifndef NDEBUG
		for (const auto [key, value] : sortedContext)
		{
			PONY_LOG_IF(!IsContextKeyValid(key), application->Logger(), Log::LogType::Warning, "Invalid context key: '{}'.", key.value);
			PONY_LOG_IF(!IsContextValueValid(value), application->Logger(), Log::LogType::Warning, "Invalid context value: '{}'.", value.value);
		}
#endif

		const auto lock = std::shared_lock(resourceMutex);
		const auto [resource, variantIndex] = resources.GetResource(resourceId, context);

		return variantIndex.has_value() ? resource->variants[*variantIndex].availability : ResourceAvailability::None;
	}

	struct ResourceType ResourceService::ResourceType(const ResourceID resourceId) const
	{
		const auto lock = std::shared_lock(resourceMutex);

		if (const ResourceEntry* const resourceEntry = resources.GetResource(resourceId)) [[likely]]
		{
			return resourceEntry->type;
		}

		throw std::invalid_argument("Invalid ID");
	}

	std::shared_ptr<ILoadableResource> ResourceService::GetLoadableResource(const ResourceID resourceId, 
		const std::span<const std::pair<ContextKey, ContextValue>> context) const
	{
		return GetResource<LoadableResource, ILoadableResourceData>(resourceId, context, loadableResourceCache, loadableResourceCacheMutex, [](const VariantEntry& variant)
		{
			return variant.provider->GetLoadableResource(variant.index);
		});
	}

	std::shared_ptr<IFileResource> ResourceService::GetFileResource(const ResourceID resourceId, const std::span<const std::pair<ContextKey, ContextValue>> context) const
	{
		return GetResource<FileResource, IFileResourceData>(resourceId, context, fileResourceCache, fileResourceCacheMutex, [](const VariantEntry& variant)
		{
			return variant.provider->GetFileResource(variant.index);
		});
	}

	std::shared_ptr<IMemoryResource> ResourceService::GetMemoryResource(const ResourceID resourceId,
		const std::span<const std::pair<ContextKey, ContextValue>> context) const
	{
		return GetResource<MemoryResource, IMemoryResourceData>(resourceId, context, memoryResourceCache, memoryResourceCacheMutex, [](const VariantEntry& variant)
		{
			return variant.provider->GetMemoryResource(variant.index);
		});
	}

	ContextKey ResourceService::MakeContextKey(const std::string_view key)
	{
		const auto contextKey = ContextKey{.value = Hash::FNV1a64(key)};

		const auto lock = std::unique_lock(keyMapMutex);
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
		const auto lock = std::shared_lock(keyMapMutex);
		return keyMap.contains(key);
	}

	std::string_view ResourceService::GetContextKeyString(const ContextKey key) const
	{
		const auto lock = std::shared_lock(keyMapMutex);
		if (const auto position = keyMap.find(key); position != keyMap.cend()) [[likely]]
		{
			return position->second;
		}

		throw std::invalid_argument("Invalid key");
	}

	ContextValue ResourceService::MakeContextValue(const std::string_view value)
	{
		const auto contextValue = ContextValue{.value = Hash::FNV1a64(value)};

		const auto lock = std::unique_lock(valueMapMutex);
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
		const auto lock = std::shared_lock(valueMapMutex);
		return valueMap.contains(value);
	}

	std::string_view ResourceService::GetContextValueString(const ContextValue value) const
	{
		const auto lock = std::shared_lock(valueMapMutex);
		if (const auto position = valueMap.find(value); position != valueMap.cend()) [[likely]]
		{
			return position->second;
		}

		throw std::invalid_argument("Invalid value");
	}

	ResourceID ResourceService::MakeResourceID(const std::string_view resourceId)
	{
		const auto resourceIdHash = ResourceID{.value = Hash::FNV1a64(resourceId)};

		const auto lock = std::unique_lock(resourceIdMapMutex);
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
		const auto lock = std::shared_lock(resourceIdMapMutex);
		return resourceIdMap.contains(resourceId);
	}

	std::string_view ResourceService::GetResourceIDString(const ResourceID resourceId) const
	{
		const auto lock = std::shared_lock(resourceIdMapMutex);
		if (const auto position = resourceIdMap.find(resourceId); position != resourceIdMap.cend()) [[likely]]
		{
			return position->second;
		}

		throw std::invalid_argument("Invalid resource ID");
	}

	struct ResourceType ResourceService::MakeResourceType(const std::string_view type)
	{
		const auto resourceType = Resource::ResourceType{.value = Hash::FNV1a64(type)};

		const auto lock = std::unique_lock(resourceTypeMapMutex);
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
		const auto lock = std::shared_lock(resourceTypeMapMutex);
		return resourceTypeMap.contains(type);
	}

	std::string_view ResourceService::GetResourceTypeString(const struct ResourceType type) const
	{
		const auto lock = std::shared_lock(resourceTypeMapMutex);
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

	std::pair<const ResourceEntry&, const VariantEntry&> ResourceService::GetResource(const ResourceID resourceId,
		const std::span<const std::pair<ContextKey, ContextValue>> context) const
	{
		const auto [resourceEntry, variantIndex] = resources.GetResource(resourceId, context);
		if (!resourceEntry) [[unlikely]]
		{
			throw std::invalid_argument("Invalid ID");
		}
		if (!variantIndex) [[unlikely]]
		{
			throw std::invalid_argument("No resource satisfies context");
		}

		const VariantEntry& variantEntry = resourceEntry->variants[*variantIndex];

		return std::pair(*resourceEntry, variantEntry);
	}

	ResourceHandle ResourceService::AddResource(const ResourceParams& params, IResourceProvider& provider)
	{
#ifndef NDEBUG
		if (std::this_thread::get_id() != application->MainThreadID()) [[unlikely]]
		{
			throw std::logic_error("Must be called on main thread");
		}

		if (application->FlowState() != Application::FlowState::StartingUp) [[unlikely]]
		{
			throw std::logic_error("Resources can be added only on start-up");
		}
#endif

		if (!nextResourceHandle.IsValid()) [[unlikely]]
		{
			throw std::overflow_error("No more resource handles available");
		}

		if (!IsResourceIDValid(params.id)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid ID");
		}
		if (!IsResourceTypeValid(params.type)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid type");
		}
		for (const auto [key, value] : params.requiredContext)
		{
			if (!IsContextKeyValid(key)) [[unlikely]]
			{
				throw std::invalid_argument("Invalid context key");
			}
			if (!IsContextValueValid(value)) [[unlikely]]
			{
				throw std::invalid_argument("Invalid context value");
			}
		}

		const ResourceHandle currentHandle = nextResourceHandle;
		auto lock = std::unique_lock(resourceMutex);
		resources.AddResource(params, provider, currentHandle);
		lock.unlock();
		PONY_LOG(application->Logger(), Log::LogType::Info, "Resource added. Handle: '0x{:X}'; ID: '{}'.", currentHandle.id, params.id.value);
		++nextResourceHandle.id;

		return currentHandle;
	}

	void ResourceService::RemoveResource(const ResourceHandle handle)
	{
		auto lock = std::unique_lock(resourceMutex);
		resources.RemoveResource(handle);
		lock.unlock();
		PONY_LOG(application->Logger(), Log::LogType::Info, "Resource removed. Handle: '0x{:X}'.", handle.id);
	}

	Memory::Arena& ResourceService::Arena()
	{
		thread_local auto arena = Memory::Arena(0uz, 128uz);
		return arena;
	}

	template<std::derived_from<IResource> ResourceT, typename ResourceD>
	std::shared_ptr<ResourceT> ResourceService::GetResource(const ResourceID resourceId, const std::span<const std::pair<ContextKey, ContextValue>> context,
		std::unordered_map<ResourceHandle, std::weak_ptr<ResourceT>>& map, std::shared_mutex& mapMutex,
		const std::function<std::shared_ptr<ResourceD>(const VariantEntry&)>& dataGetter) const
	{
		Memory::Arena& arena = Arena();
		arena.Free();

		const Memory::Arena::Slice<std::pair<ContextKey, ContextValue>> sortedContextSlice = arena.Allocate<std::pair<ContextKey, ContextValue>>(context.size());
		const std::span<std::pair<ContextKey, ContextValue>> sortedContext = arena.Span(sortedContextSlice);
		std::memcpy(sortedContext.data(), context.data(), sortedContext.size_bytes());
		ResourceContainer::SortContext(sortedContext);

#ifndef NDEBUG
		for (const auto [key, value] : context)
		{
			if (!IsContextKeyValid(key)) [[unlikely]]
			{
				throw std::invalid_argument("Invalid context key");
			}
			if (!IsContextValueValid(value)) [[unlikely]]
			{
				throw std::invalid_argument("Invalid context value");
			}
		}
#endif

		const auto lock = std::shared_lock(resourceMutex);

		const auto [resourceEntry, variantEntry] = GetResource(resourceId, sortedContext);
		if (const std::shared_ptr<ResourceT> resource = GetResourceFromCache(variantEntry.handle, map, mapMutex))
		{
			return resource;
		}

		return AddResourceToCache(resourceEntry, variantEntry, dataGetter(variantEntry), map, mapMutex);
	}

	template<std::derived_from<IResource> ResourceT>
	std::shared_ptr<ResourceT> ResourceService::GetResourceFromCache(const ResourceHandle resourceHandle,
		const std::unordered_map<ResourceHandle, std::weak_ptr<ResourceT>>& map, std::shared_mutex& mutex) noexcept
	{
		const auto lock = std::shared_lock(mutex);
		return GetResourceFromCacheUnsafe<ResourceT>(resourceHandle, map);
	}

	template<std::derived_from<IResource> ResourceT, typename ResourceD>
	std::shared_ptr<ResourceT> ResourceService::AddResourceToCache(const ResourceEntry& resourceEntry, const VariantEntry& variantEntry, 
		const std::shared_ptr<ResourceD>& data, std::unordered_map<ResourceHandle, std::weak_ptr<ResourceT>>& map,
		std::shared_mutex& mutex)
	{
		const auto resource = std::make_shared<ResourceT>(resourceEntry.id, resourceEntry.type, variantEntry.requiredContext, data);

		const auto lock = std::unique_lock(mutex);
		if (const std::shared_ptr<ResourceT> cacheResource = GetResourceFromCacheUnsafe<ResourceT>(variantEntry.handle, map)) [[unlikely]]
		{
			return cacheResource;
		}
		map[variantEntry.handle] = resource;

		return resource;
	}

	template<std::derived_from<IResource> ResourceT>
	std::shared_ptr<ResourceT> ResourceService::GetResourceFromCacheUnsafe(const ResourceHandle resourceHandle,
		const std::unordered_map<ResourceHandle, std::weak_ptr<ResourceT>>& map) noexcept
	{
		if (const auto position = map.find(resourceHandle); position != map.cend())
		{
			return position->second.lock();
		}

		return nullptr;
	}
}
