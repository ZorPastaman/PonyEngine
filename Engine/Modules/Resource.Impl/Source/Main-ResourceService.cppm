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

import PonyEngine.Application;
import PonyEngine.Hash;
import PonyEngine.Log;
import PonyEngine.Math;
import PonyEngine.Resource.Ext;

import :CollectionContainer;
import :CompletedResourceRequest;
import :LoadableResource;
import :LoaderContainer;
import :Resource;
import :ResourceContainer;
import :ResourceLoadProcess;
import :Utility;

export namespace PonyEngine::Resource
{
	/// @brief Resource service.
	class ResourceService final : public IResourceService, public IResourceHub
	{
	public:
		/// @brief Creates a resource service.
		/// @param application Application.
		[[nodiscard("Pure constructor")]]
		explicit ResourceService(Application::IApplication& application);
		ResourceService(const ResourceService&) = delete;
		ResourceService(ResourceService&&) = delete;

		~ResourceService() noexcept;

		[[nodiscard("Pure function")]] 
		virtual bool HasResource(ResourceID resourceId) const override;
		[[nodiscard("Pure function")]] 
		virtual bool HasInterfaces(ResourceID resourceId, std::span<const std::type_index> types) const override;

		[[nodiscard("Pure function")]] 
		virtual std::shared_ptr<IResourceRequest> LoadResource(ResourceID resourceId, std::span<const std::type_index> interfaceTypes,
			std::move_only_function<void(const IResourceRequest&) noexcept> callback) const override;

		[[nodiscard("Must be used to unregister")]] 
		virtual ResourceCollection RegisterCollection(IResourceProvider& provider, std::span<const CollectionResource> resources,
			std::span<const std::type_index> dataAccessTypes) override;
		virtual void UnregisterCollection(IResourceProvider& provider, ResourceCollection collection) override;

		virtual void RegisterLoader(IResourceLoader& loader, std::span<const ResourceType> types) override;
		virtual void UnregisterLoader(IResourceLoader& loader) override;

		[[nodiscard("Pure function")]]
		virtual ResourceID MakeResourceID(std::string_view resourceId) override;
		[[nodiscard("Pure function")]]
		virtual bool IsResourceIDValid(ResourceID resourceId) const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::string_view GetResourceIDString(ResourceID resourceId) const override;

		[[nodiscard("Pure function")]] 
		virtual ResourceType MakeResourceType(std::string_view resourceType) override;
		[[nodiscard("Pure function")]] 
		virtual bool IsResourceTypeValid(ResourceType resourceType) const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual std::string_view GetResourceTypeString(ResourceType resourceType) const override;

		ResourceService& operator =(const ResourceService&) = delete;
		ResourceService& operator =(ResourceService&&) = delete;

	private:
		/// @brief Checks if the resource collection is valid.
		/// @param collection Resource collection.
		/// @return @a True if it's valid; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsValid(ResourceCollection collection) const noexcept;
		/// @brief Creates a new collection.
		/// @return Collection.
		[[nodiscard("Must be used")]]
		ResourceCollection CreateCollection();
		/// @brief Makes a completely new collection.
		/// @return Collection.
		[[nodiscard("Must be used")]]
		ResourceCollection MakeCollection();
		/// @brief Resurrects a collection.
		/// @return Collection.
		[[nodiscard("Must be used")]]
		ResourceCollection ResurrectCollection() noexcept;
		/// @brief Kills the collection.
		/// @param collection Collection to kill.
		void KillCollection(ResourceCollection collection) noexcept;

		/// @brief Finds a loader by the resource type.
		/// @param type Resource type.
		/// @return Loader; nullptr if not found.
		[[nodiscard("Pure function")]]
		IResourceLoader* FindLoader(ResourceType type) const noexcept;

		/// @brief Tries to find an ongoing load process.
		/// @param resource Resource.
		/// @return Load process or nullptr if not found.
		[[nodiscard("Pure function")]]
		std::shared_ptr<ResourceLoadProcess> FindLoadProcess(const Resource* resource) const noexcept;
		/// @brief Adds the load process.
		/// @param loadProcess Load process to add.
		void AddLoadProcess(std::shared_ptr<ResourceLoadProcess> loadProcess) const;
		/// @brief Removes the load process.
		/// @param loadProcess Load process to remove.
		void RemoveLoadProcess(const ResourceLoadProcess* loadProcess) const noexcept;

		Application::IApplication* application; ///< Application.
		Log::ILogService* logService; ///< Log service.

		std::vector<ResourceCollectionVersion> resourceCollectionVersions; ///< Resource collection versions.
		std::vector<ResourceCollectionID> deadResourceCollectionIds; ///< Dead resource collection IDs.

		CollectionContainer collectionContainer; ///< Resource collection container.
		ResourceContainer resourceContainer; ///< Resource container.
		LoaderContainer loaderContainer; ///< Loader container.
		mutable std::shared_mutex stateMutex; ///< State mutex.

		mutable std::unordered_map<const Resource*, std::vector<std::shared_ptr<ResourceLoadProcess>>> loadProcesses; ///< Load process.
		mutable std::mutex loadProcessMutex; ///< Load process mutex.

		std::unordered_map<ResourceID, std::string> resourceIdToStringMap; ///< Resource ID to resource ID string map.
		mutable std::shared_mutex resourceIdToStringMapMutex; ///< Resource ID map mutex.
		std::unordered_map<ResourceType, std::string> resourceTypeToStringMap; ///< Resource type to resource type string map.
		mutable std::shared_mutex resourceTypeToStringMapMutex; ///< Resource type map mutex.
	};
}

namespace PonyEngine::Resource
{
	ResourceService::ResourceService(Application::IApplication& application) :
		application{&application},
		logService{this->application->FindInterface<Log::ILogService>()}
	{
	}

	ResourceService::~ResourceService() noexcept
	{
		assert(collectionContainer.Size() == 0uz && "Collections weren't removed.");
		assert(loaderContainer.Size() == 0uz && "Loaders weren't removed.");
	}

	bool ResourceService::HasResource(const ResourceID resourceId) const
	{
		if (!IsResourceIDValid(resourceId)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid resource ID");
		}

		const auto lock = std::shared_lock(stateMutex);
		return resourceContainer.Contains(resourceId);
	}

	bool ResourceService::HasInterfaces(const ResourceID resourceId, const std::span<const std::type_index> types) const
	{
		if (!IsResourceIDValid(resourceId)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid resource ID");
		}

		const auto lock = std::shared_lock(stateMutex);

		if (!resourceContainer.Contains(resourceId)) [[unlikely]]
		{
			throw std::invalid_argument("Resource not found");
		}

		return CheckTypes(types, resourceContainer.GetResource(resourceId)->InterfaceTypes());
	}

	std::shared_ptr<IResourceRequest> ResourceService::LoadResource(const ResourceID resourceId, const std::span<const std::type_index> interfaceTypes,
		std::move_only_function<void(const IResourceRequest&) noexcept> callback) const
	{
		if (!IsResourceIDValid(resourceId)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid resource ID");
		}

		const auto stateLock = std::shared_lock(stateMutex);

		if (!resourceContainer.Contains(resourceId)) [[unlikely]]
		{
			throw std::invalid_argument("Resource not found");
		}

		const std::shared_ptr<Resource>& resource = resourceContainer.GetResource(resourceId);
		if (!CheckTypes(interfaceTypes, resource->InterfaceTypes())) [[unlikely]]
		{
			throw std::invalid_argument("Invalid type");
		}

		const std::lock_guard<std::mutex> resourceLock = resource->Lock();

		if (std::shared_ptr<const void> mainResource = resource->MainResource())
		{
			const auto request = std::make_shared<CompletedResourceRequest>(resource, std::move(mainResource));

			if (callback)
			{
				callback(*request);
			}

			return request;
		}

		if (std::shared_ptr<ResourceLoadProcess> loadProcess = FindLoadProcess(resource.get()))
		{
			if (loadProcess->IncrementCancelCount())
			{
				return std::make_shared<OngoingResourceRequest>(std::move(loadProcess), std::move(callback));
			}
		}

		IResourceProvider& provider = collectionContainer.Provider(collectionContainer.IndexOf(resource->Collection()));
		std::shared_ptr<void> dataAccess = provider.GetResourceData(resource->CollectionResourceIndex(), resource->DataAccessType());
		assert(dataAccess && "Data access is nullptr.");

		IResourceLoader* const loader = FindLoader(resource->Type());
		assert(loader && "Loader not found.");

		auto loadProcess = std::make_shared<ResourceLoadProcess>(resource, dataAccess);
		AddLoadProcess(loadProcess);

		try
		{
			loadProcess->SetLoadRequest(loader->Load(*loadProcess, [this, process = loadProcess.get()](const IResourceLoadRequest& request) noexcept
			{
				if (process->IncrementCancelCount())
				{
					switch (request.Status())
					{
					case ResourceLoadRequestStatus::Success:
						process->SetSuccess(request.MainResource(), request.ResourceInterfaces());
						break;
					case ResourceLoadRequestStatus::Failure:
						process->SetFailure(request.Exception());
						break;
					case ResourceLoadRequestStatus::Canceled:
						process->SetCanceled();
						break;
					default: [[unlikely]]
						assert(false && "Unexpected status.");
						break;
					}
				}
				else
				{
					process->SetCanceled();
				}

				RemoveLoadProcess(process);
			}));
		}
		catch (...)
		{
			RemoveLoadProcess(loadProcess.get());
			throw;
		}

		return std::make_shared<OngoingResourceRequest>(std::move(loadProcess), std::move(callback));
	}

	ResourceCollection ResourceService::RegisterCollection(IResourceProvider& provider,
		const std::span<const CollectionResource> resources, const std::span<const std::type_index> dataAccessTypes)
	{
		assert(!dataAccessTypes.empty() && "Empty data access types");

		std::vector<ResourceID> resourceIds;
		resourceIds.reserve(resources.size());
		for (const CollectionResource& resource : resources)
		{
			resourceIds.push_back(resource.id);
		}

		const auto lock = std::unique_lock(stateMutex);

		const ResourceCollection collection = CreateCollection();
		try
		{
			collectionContainer.Add(collection.id, provider, std::move(resourceIds));

			std::size_t addedResourceCount = 0uz;
			try
			{
				for (const CollectionResource& resource : resources)
				{
					if (resourceContainer.Contains(resource.id)) [[unlikely]]
					{
						throw std::invalid_argument(std::format("Resource with the same ID '0x{:X}' is already added", resource.id.value));
					}
					if (!IsResourceIDValid(resource.id)) [[unlikely]]
					{
						throw std::invalid_argument(std::format("Resource ID is invalid: ID = '0x{:X}'", resource.id.value));
					}
					if (!IsResourceTypeValid(resource.type)) [[unlikely]]
					{
						throw std::invalid_argument(std::format("Resource type is invalid: Type = '0x{:X}'", resource.type.value));
					}

					IResourceLoader* const loader = FindLoader(resource.type);
					if (!loader) [[unlikely]]
					{
						throw std::logic_error(std::format("No resource loader found for type '0x{:X}'", resource.type.value));
					}

					auto loadableResource = LoadableResource(resource.type, resource.dataMeta, resource.loadMeta, dataAccessTypes);
					loader->PrepareResource(loadableResource);
					if (!loadableResource.DataAccessType()) [[unlikely]]
					{
						throw std::logic_error("Loader didn't set data access type");
					}
					if (loadableResource.InterfaceTypes().empty()) [[unlikely]]
					{
						throw std::logic_error("Loader didn't set output types");
					}

					resourceContainer.Add(std::make_shared<Resource>(resource.id, resource.type, collection.id, resource.dataIndex,
						*loadableResource.DataAccessType(), std::move(loadableResource.LoadData()), std::move(loadableResource.InterfaceTypes())));

					++addedResourceCount;
				}
			}
			catch (...)
			{
				for (std::size_t i = addedResourceCount; i-- > 0uz; )
				{
					resourceContainer.Remove(resources[i].id);
				}
				collectionContainer.Remove(collectionContainer.IndexOf(collection.id));

				throw;
			}
		}
		catch (...)
		{
			KillCollection(collection);
			throw;
		}

		return collection;
	}

	void ResourceService::UnregisterCollection(IResourceProvider& provider, const ResourceCollection collection)
	{
		const auto lock = std::unique_lock(stateMutex);

		if (!IsValid(collection))
		{
			throw std::invalid_argument("Invalid collection");
		}

		const std::size_t index = collectionContainer.IndexOf(collection.id);
		assert(index < collectionContainer.Size() && &collectionContainer.Provider(index) == &provider && "invalid collection");

		for (const ResourceID resourceId : collectionContainer.Resources(index))
		{
			resourceContainer.Remove(resourceId);
		}
		collectionContainer.Remove(index);

		KillCollection(collection);
	}

	void ResourceService::RegisterLoader(IResourceLoader& loader, const std::span<const ResourceType> types)
	{
		assert(std::this_thread::get_id() == application->MainThreadID() && "Must be called on main thread");

		const auto lock = std::unique_lock(stateMutex);

		for (const ResourceType type : types)
		{
			assert(loaderContainer.IndexOf(type) >= loaderContainer.Size() && "Resource type is already added.");
		}
		assert(loaderContainer.IndexOf(loader) >= loaderContainer.Size() && "Resource loader is already added.");

		loaderContainer.Add(loader, types);
	}

	void ResourceService::UnregisterLoader(IResourceLoader& loader)
	{
		assert(std::this_thread::get_id() == application->MainThreadID() && "Must be called on main thread");

		const auto lock = std::unique_lock(stateMutex);

		const std::size_t index = loaderContainer.IndexOf(loader);
		assert(index < loaderContainer.Size() && "Invalid loader.");

		for (const ResourceType resourceType : loaderContainer.Types(index))
		{
			if (resourceContainer.TypeCount(resourceType) > 0uz) [[unlikely]]
			{
				throw std::logic_error("Some resource loader types are still in use");
			}
		}

		loaderContainer.Remove(index);
	}

	ResourceID ResourceService::MakeResourceID(const std::string_view resourceId)
	{
		const auto id = ResourceID{.value = Hash::FNV1a64(resourceId)};

		const auto lock = std::unique_lock(resourceIdToStringMapMutex);

		if (const auto position = resourceIdToStringMap.find(id); position != resourceIdToStringMap.cend())
		{
			if (position->second != resourceId) [[unlikely]]
			{
				throw std::overflow_error("Hash collision");
			}
		}
		else
		{
			PONY_LOG(logService, Log::LogType::Info, "Adding new resource ID. ID: '{}'; ID hash: '{}'.", resourceId, id.value);
			resourceIdToStringMap.emplace(id, resourceId);
		}

		return id;
	}

	bool ResourceService::IsResourceIDValid(const ResourceID resourceId) const noexcept
	{
		const auto lock = std::shared_lock(resourceIdToStringMapMutex);
		return resourceIdToStringMap.contains(resourceId);
	}

	std::string_view ResourceService::GetResourceIDString(const ResourceID resourceId) const
	{
		const auto lock = std::shared_lock(resourceIdToStringMapMutex);
		
		const auto position = resourceIdToStringMap.find(resourceId);
		if (position == resourceIdToStringMap.cend()) [[unlikely]]
		{
			throw std::invalid_argument("Invalid resource ID");
		}

		return position->second;
	}

	ResourceType ResourceService::MakeResourceType(const std::string_view resourceType)
	{
		const auto type = ResourceType{.value = Hash::FNV1a64(resourceType)};

		const auto lock = std::unique_lock(resourceTypeToStringMapMutex);

		if (const auto position = resourceTypeToStringMap.find(type); position != resourceTypeToStringMap.cend())
		{
			if (position->second != resourceType) [[unlikely]]
			{
				throw std::overflow_error("Hash collision");
			}
		}
		else
		{
			PONY_LOG(logService, Log::LogType::Info, "Adding new resource type. Type: '{}'; Type hash: '{}'.", resourceType, type.value);
			resourceTypeToStringMap.emplace(type, resourceType);
		}

		return type;
	}

	bool ResourceService::IsResourceTypeValid(const ResourceType resourceType) const noexcept
	{
		const auto lock = std::shared_lock(resourceTypeToStringMapMutex);
		return resourceTypeToStringMap.contains(resourceType);
	}

	std::string_view ResourceService::GetResourceTypeString(const ResourceType resourceType) const
	{
		const auto lock = std::shared_lock(resourceTypeToStringMapMutex);

		const auto position = resourceTypeToStringMap.find(resourceType);
		if (position == resourceTypeToStringMap.cend()) [[unlikely]]
		{
			throw std::invalid_argument("Invalid resource type");
		}

		return position->second;
	}

	bool ResourceService::IsValid(const ResourceCollection collection) const noexcept
	{
		return Math::IsOdd(collection.id) && collection.id < resourceCollectionVersions.size() && collection.version == resourceCollectionVersions[collection.id];
	}

	ResourceCollection ResourceService::CreateCollection()
	{
		return deadResourceCollectionIds.empty() ? MakeCollection() : ResurrectCollection();
	}

	ResourceCollection ResourceService::MakeCollection()
	{
		if (resourceCollectionVersions.size() >= std::numeric_limits<ResourceCollectionID>::max()) [[unlikely]]
		{
			throw std::overflow_error("No more resource collection ID available");
		}

		const ResourceCollectionID collectionID = static_cast<ResourceCollectionID>(resourceCollectionVersions.size());

		constexpr ResourceCollectionVersion collectionVersion = 1u;
		resourceCollectionVersions.push_back(collectionVersion);

		return ResourceCollection{.id = collectionID, .version = collectionVersion};
	}

	ResourceCollection ResourceService::ResurrectCollection() noexcept
	{
		const ResourceCollectionID collectionId = deadResourceCollectionIds.back();
		deadResourceCollectionIds.pop_back();

		const ResourceCollectionVersion collectionVersion = ++resourceCollectionVersions[collectionId];

		return ResourceCollection{.id = collectionId, .version = collectionVersion};
	}

	void ResourceService::KillCollection(const ResourceCollection collection) noexcept
	{
		try
		{
			++resourceCollectionVersions[collection.id];
			deadResourceCollectionIds.push_back(collection.id);
		}
		catch (...)
		{
			PONY_LOG(logService, Log::LogType::Error, std::current_exception(), "On killing resource collection. ID: '0x{:X}'.", collection.id);
			// Just forget about this collection.
		}
	}

	IResourceLoader* ResourceService::FindLoader(const ResourceType type) const noexcept
	{
		const std::size_t index = loaderContainer.IndexOf(type);
		return index < loaderContainer.Size() ? &loaderContainer.Loader(index) : nullptr;
	}

	std::shared_ptr<ResourceLoadProcess> ResourceService::FindLoadProcess(const Resource* const resource) const noexcept
	{
		const auto lock = std::lock_guard(loadProcessMutex);

		if (const auto position = loadProcesses.find(resource); position != loadProcesses.cend())
		{
			return position->second.back();
		}

		return nullptr;
	}

	void ResourceService::AddLoadProcess(std::shared_ptr<ResourceLoadProcess> loadProcess) const
	{
		const auto lock = std::lock_guard(loadProcessMutex);

		std::vector<std::shared_ptr<ResourceLoadProcess>>& processes = loadProcesses[loadProcess->Resource()];
		assert(!std::ranges::contains(processes, loadProcess) && "Load process was already added.");
		processes.push_back(std::move(loadProcess));
	}

	void ResourceService::RemoveLoadProcess(const ResourceLoadProcess* const loadProcess) const noexcept
	{
		const auto lock = std::lock_guard(loadProcessMutex);

		const auto resourcePosition = loadProcesses.find(loadProcess->Resource());
		assert(resourcePosition != loadProcesses.cend() && "Load process resource not found.");
		const auto processPosition = std::ranges::find_if(resourcePosition->second, [&](const std::shared_ptr<ResourceLoadProcess>& p) { return p.get() == loadProcess; });
		assert(processPosition != resourcePosition->second.cend() && "Load process not found.");

		if (resourcePosition->second.size() == 1uz) [[likely]]
		{
			loadProcesses.erase(resourcePosition);
		}
		else [[unlikely]]
		{
			resourcePosition->second.erase(processPosition);
		}
	}
}
