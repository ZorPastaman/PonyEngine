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

import PonyEngine.Application;
import PonyEngine.Hash;
import PonyEngine.Log;
import PonyEngine.Resource.Ext;

import :FileResource;
import :LoadableResource;
import :MemoryResource;
import :ResourceContainer;
import :ResourceEntry;
import :ResourceProviderContainer;

export namespace PonyEngine::Resource
{
	/// @brief Resource service.
	class ResourceService final : public Application::IService, public IResourceModuleContext, private Application::ITickableService, 
		private IResourceContext, private IResourceService
	{
	public:
		/// @brief Creates a resource service.
		/// @param application Application.
		[[nodiscard("Pure constructor")]]
		explicit ResourceService(Application::IApplication& application);
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
		virtual Application::IApplication& Application() noexcept override;
		[[nodiscard("Pure function")]] 
		virtual const Application::IApplication& Application() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual Log::ILogger& Logger() noexcept override;
		[[nodiscard("Pure function")]] 
		virtual const Log::ILogger& Logger() const noexcept override;

		[[nodiscard("Pure function")]] 
		virtual ResourceAvailability IsResourceAvailable(ResourceID resourceId) const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual struct ResourceType ResourceType(ResourceID resourceId) const override;
		[[nodiscard("Pure function")]] 
		virtual std::shared_ptr<ILoadableResource> GetLoadableResource(ResourceID resourceId) const override;
		[[nodiscard("Pure function")]] 
		virtual std::shared_ptr<IFileResource> GetFileResource(ResourceID resourceId) const override;
		[[nodiscard("Pure function")]] 
		virtual std::shared_ptr<IMemoryResource> GetMemoryResource(ResourceID resourceId) const override;

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

		/// @brief Resource registry.
		class ResourceRegistry final : public IResourceRegistry
		{
		public:
			/// @brief Creates a resource registry.
			/// @param service Resource service.
			/// @param provider Current handled resource provider.
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
			ResourceService* service; ///< Resource service.
			IResourceProvider* provider; ///< Resource provider.
		};

		/// @brief Begins the providers.
		/// @param count How many providers are begun.
		void Begin(std::size_t& count);
		/// @brief Ends the providers.
		/// @param count How many providers to end.
		void End(std::size_t count) noexcept;

		/// @brief Gets a resource.
		/// @tparam ResourceT Resource type.
		/// @tparam ResourceD Resource data type.
		/// @param resourceId Resource ID.
		/// @param map Resource cache.
		/// @param mapMutex Resource cache mutex.
		/// @param dataGetter Resource data getter.
		/// @return Resource.
		template<std::derived_from<IResource> ResourceT, typename ResourceD> [[nodiscard("Pure function")]]
		std::shared_ptr<ResourceT> GetResource(ResourceID resourceId, std::unordered_map<ResourceID, std::weak_ptr<ResourceT>>& map, std::shared_mutex& mapMutex,
			const std::function<std::shared_ptr<ResourceD>(const ResourceEntry&)>& dataGetter) const;
		/// @brief Adds a resource.
		/// @param params Resource parameters.
		/// @param provider Resource provider.
		/// @return Resource handle.
		[[nodiscard("Must be used")]]
		ResourceHandle AddResource(const ResourceParams& params, IResourceProvider& provider);
		/// @brief Removes a resource.
		/// @param handle Resource handle.
		void RemoveResource(ResourceHandle handle);

		/// @brief Gets a resource from the cache.
		/// @tparam ResourceT Resource type.
		/// @param resourceId Resource ID.
		/// @param map Resource cache.
		/// @param mutex Resource cache mutex.
		/// @return Resource from cache or @a nullptr if not found.
		template<std::derived_from<IResource> ResourceT> [[nodiscard("Pure function")]]
		static std::shared_ptr<ResourceT> GetResourceFromCache(ResourceID resourceId, 
			const std::unordered_map<ResourceID, std::weak_ptr<ResourceT>>& map, std::shared_mutex& mutex) noexcept;
		/// @brief Adds the resource to the cache.
		/// @tparam ResourceT Resource type.
		/// @tparam ResourceD Resource data.
		/// @param resourceEntry Resource entry.
		/// @param data Resource data.
		/// @param map Resource cache.
		/// @param mutex Resource cache mutex.
		/// @return Added resource or gotten from the cache if it has such a resource.
		template<std::derived_from<IResource> ResourceT, typename ResourceD> [[nodiscard("Pure function")]]
		std::shared_ptr<ResourceT> AddResourceToCache(const ResourceEntry& resourceEntry, std::shared_ptr<ResourceD>&& data,
			std::unordered_map<ResourceID, std::weak_ptr<ResourceT>>& map, std::shared_mutex& mutex) const;
		/// @brief Gets a resource from the cache.
		/// @tparam ResourceT Resource type.
		/// @param resourceId Resource ID.
		/// @param map Resource cache.
		/// @return Resource from the cache or @a nullptr if not found.
		/// @note This function doesn't use mutexes.
		template<std::derived_from<IResource> ResourceT> [[nodiscard("Pure function")]]
		static std::shared_ptr<ResourceT> GetResourceFromCacheUnsafe(ResourceID resourceId, 
			const std::unordered_map<ResourceID, std::weak_ptr<ResourceT>>& map) noexcept;

		Application::IApplication* application; ///< Application.

		ResourceProviderContainer providers; ///< Resource provider container.

		ResourceContainer resources; ///< Resource container.
		mutable std::shared_mutex resourceMutex; ///< Resource container mutex.

		mutable std::unordered_map<ResourceID, std::weak_ptr<LoadableResource>> loadableResourceCache; ///< Loadable resource cache.
		mutable std::shared_mutex loadableResourceCacheMutex; ///< Loadable resource cache mutex.

		mutable std::unordered_map<ResourceID, std::weak_ptr<FileResource>> fileResourceCache; ///< File resource cache.
		mutable std::shared_mutex fileResourceCacheMutex; ///< File resource cache mutex.

		mutable std::unordered_map<ResourceID, std::weak_ptr<MemoryResource>> memoryResourceCache; ///< Memory resource cache.
		mutable std::shared_mutex memoryResourceCacheMutex; ///< Memory resource cache mutex.

		std::unordered_map<ResourceID, std::string> resourceIdMap; ///< Resource ID to resource ID string map.
		mutable std::shared_mutex resourceIdMapMutex; ///< Resource ID map mutex.
		std::unordered_map<struct ResourceType, std::string> resourceTypeMap; ///< Resource type to resource type string map.
		mutable std::shared_mutex resourceTypeMapMutex; ///< Resource type map mutex.

		ResourceProviderHandle nextProviderHandle; ///< Next provider handle.
		ResourceHandle nextResourceHandle; ///< Next resource handle.
	};
}

namespace PonyEngine::Resource
{
	ResourceService::ResourceService(Application::IApplication& application) :
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
				PONY_LOG(application->Logger(), Log::LogType::Error, std::current_exception(), "On ticking '{}' provider.", typeid(provider).name());
				throw;
			}
		}
	}

	Application::IApplication& ResourceService::Application() noexcept
	{
		return *application;
	}

	const Application::IApplication& ResourceService::Application() const noexcept
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

	ResourceAvailability ResourceService::IsResourceAvailable(const ResourceID resourceId) const noexcept
	{
#ifndef NDEBUG
		PONY_LOG_IF(!IsResourceIDValid(resourceId), application->Logger(), Log::LogType::Warning, "Invalid resource ID: '{}'.", resourceId.value);
#endif

		const auto lock = std::shared_lock(resourceMutex);
		const ResourceEntry* const resource = resources.GetResource(resourceId);

		return resource ? resource->availability : ResourceAvailability::None;
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

	std::shared_ptr<ILoadableResource> ResourceService::GetLoadableResource(const ResourceID resourceId) const
	{
		return GetResource<LoadableResource, ILoadableResourceData>(resourceId, loadableResourceCache, loadableResourceCacheMutex, [](const ResourceEntry& entry)
		{
			return entry.provider->GetLoadableResource(entry.index);
		});
	}

	std::shared_ptr<IFileResource> ResourceService::GetFileResource(const ResourceID resourceId) const
	{
		return GetResource<FileResource, IFileResourceData>(resourceId, fileResourceCache, fileResourceCacheMutex, [](const ResourceEntry& entry)
		{
			return entry.provider->GetFileResource(entry.index);
		});
	}

	std::shared_ptr<IMemoryResource> ResourceService::GetMemoryResource(const ResourceID resourceId) const
	{
		return GetResource<MemoryResource, IMemoryResourceData>(resourceId, memoryResourceCache, memoryResourceCacheMutex, [](const ResourceEntry& entry)
		{
			return entry.provider->GetMemoryResource(entry.index);
		});
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
				PONY_LOG(application->Logger(), Log::LogType::Error, std::current_exception(), "On beginning '{}' resource provider.", typeid(provider).name());
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
				PONY_LOG(application->Logger(), Log::LogType::Error, std::current_exception(), "On ending '{}' resource provider.", typeid(provider).name());
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
		if (params.availability == ResourceAvailability::None) [[unlikely]]
		{
			throw std::invalid_argument("No availability flag set");
		}

		const ResourceHandle currentHandle = nextResourceHandle;
		auto lock = std::unique_lock(resourceMutex);
		resources.AddResource(params, provider, currentHandle);
		lock.unlock();
		PONY_LOG(application->Logger(), Log::LogType::Info, "Resource added. Handle: '0x{:X}'; ID: '{}'; Type: '0x{:X}'; Availability: '{}'.", 
			currentHandle.id, params.id.value, params.type.value, params.availability);
		++nextResourceHandle.id;

		return currentHandle;
	}

	void ResourceService::RemoveResource(const ResourceHandle handle)
	{
#ifndef NDEBUG
		if (std::this_thread::get_id() != application->MainThreadID()) [[unlikely]]
		{
			throw std::logic_error("Must be called on main thread");
		}
#endif

		auto lock = std::unique_lock(resourceMutex);
		resources.RemoveResource(handle);
		lock.unlock();
		PONY_LOG(application->Logger(), Log::LogType::Info, "Resource removed. Handle: '0x{:X}'.", handle.id);
	}

	template<std::derived_from<IResource> ResourceT, typename ResourceD>
	std::shared_ptr<ResourceT> ResourceService::GetResource(const ResourceID resourceId,
		std::unordered_map<ResourceID, std::weak_ptr<ResourceT>>& map, std::shared_mutex& mapMutex,
		const std::function<std::shared_ptr<ResourceD>(const ResourceEntry&)>& dataGetter) const
	{
		const auto lock = std::shared_lock(resourceMutex);
		const ResourceEntry* const resourceEntry = resources.GetResource(resourceId);
		if (!resourceEntry) [[unlikely]]
		{
			throw std::invalid_argument("Invalid resource ID");
		}

		PONY_LOG(application->Logger(), Log::LogType::Debug, "Getting resource... ResourceID: '0x{:X}'.", resourceId.value);

		if (const std::shared_ptr<ResourceT> resource = GetResourceFromCache(resourceId, map, mapMutex))
		{
			PONY_LOG(application->Logger(), Log::LogType::Debug, "Getting resource done. Gotten from cache. ResourceID: '0x{:X}'.", resourceId.value);
			return resource;
		}

		std::shared_ptr<ResourceD> data = dataGetter(*resourceEntry);
		if (!data) [[unlikely]]
		{
			throw std::logic_error("Failed to create resource data");
		}

		return AddResourceToCache(*resourceEntry, std::move(data), map, mapMutex);
	}

	template<std::derived_from<IResource> ResourceT>
	std::shared_ptr<ResourceT> ResourceService::GetResourceFromCache(const ResourceID resourceId,
		const std::unordered_map<ResourceID, std::weak_ptr<ResourceT>>& map, std::shared_mutex& mutex) noexcept
	{
		const auto lock = std::shared_lock(mutex);
		return GetResourceFromCacheUnsafe<ResourceT>(resourceId, map);
	}

	template<std::derived_from<IResource> ResourceT, typename ResourceD>
	std::shared_ptr<ResourceT> ResourceService::AddResourceToCache(const ResourceEntry& resourceEntry, std::shared_ptr<ResourceD>&& data, 
		std::unordered_map<ResourceID, std::weak_ptr<ResourceT>>& map, std::shared_mutex& mutex) const
	{
		const auto resource = std::make_shared<ResourceT>(resourceEntry.id, resourceEntry.type, std::move(data));

		const auto lock = std::unique_lock(mutex);
		if (const std::shared_ptr<ResourceT> cacheResource = GetResourceFromCacheUnsafe<ResourceT>(resourceEntry.id, map)) [[unlikely]]
		{
			PONY_LOG(application->Logger(), Log::LogType::Debug, "Getting resource done. Gotten from cache late. ResourceID: '0x{:X}'.", resourceEntry.id.value);
			return cacheResource;
		}
		map[resourceEntry.id] = resource;
		PONY_LOG(application->Logger(), Log::LogType::Debug, "Getting resource done. Added to cache. ResourceID: '0x{:X}'.", resourceEntry.id.value);

		return resource;
	}

	template<std::derived_from<IResource> ResourceT>
	std::shared_ptr<ResourceT> ResourceService::GetResourceFromCacheUnsafe(const ResourceID resourceId,
		const std::unordered_map<ResourceID, std::weak_ptr<ResourceT>>& map) noexcept
	{
		if (const auto position = map.find(resourceId); position != map.cend())
		{
			return position->second.lock();
		}

		return nullptr;
	}
}
