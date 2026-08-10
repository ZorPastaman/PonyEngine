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
import :LoaderContainer;
import :Resource;
import :ResourceContainer;
import :ResourceRequest;

export namespace PonyEngine::Resource
{
	/// @brief Resource service.
	class ResourceService final : public IResourceService, public IResourceHub
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit ResourceService(Application::IApplication& application);
		ResourceService(const ResourceService&) = delete;
		ResourceService(ResourceService&&) = delete;

		~ResourceService() noexcept;

		[[nodiscard("Pure function")]] 
		virtual bool HasResource(ResourceID resourceId) const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual bool IsResourceTypeOf(ResourceID resourceId, std::span<const std::type_index> types) const override;

		[[nodiscard("Pure function")]] 
		virtual std::shared_ptr<IResourceRequest> LoadResource(ResourceID resourceId) const override;
		[[nodiscard("Pure function")]] 
		virtual std::shared_ptr<IResourceRequest> LoadResource(ResourceID resourceId,std::span<const std::type_index> types) const override;

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
		[[nodiscard("Pure function")]]
		bool IsValid(ResourceCollection collection) const noexcept;
		[[nodiscard("Must be used")]]
		ResourceCollection CreateCollection();
		[[nodiscard("Must be used")]]
		ResourceCollection MakeCollection();
		[[nodiscard("Must be used")]]
		ResourceCollection ResurrectCollection() noexcept;
		void KillCollection(ResourceCollection collection) noexcept;

		[[nodiscard("Pure function")]]
		IResourceLoader* FindLoader(ResourceType type) const noexcept;

		[[nodiscard("Pure function")]]
		bool CheckResourceType(ResourceID resourceId, std::span<const std::type_index> types) const;
		[[nodiscard("Pure function")]]
		std::shared_ptr<IResourceRequest> MakeResourceRequest(ResourceID resourceId) const;

		Application::IApplication* application;
		Log::ILogService* logService;

		std::vector<ResourceCollectionVersion> resourceCollectionVersions;
		std::vector<ResourceCollectionID> deadResourceCollectionIds;

		CollectionContainer collectionContainer;
		ResourceContainer resourceContainer;
		LoaderContainer loaderContainer;
		mutable std::shared_mutex stateMutex;

		std::unordered_map<ResourceID, std::string> resourceIdToStringMap;
		mutable std::shared_mutex resourceIdToStringMapMutex;
		std::unordered_map<ResourceType, std::string> resourceTypeToStringMap;
		mutable std::shared_mutex resourceTypeToStringMapMutex;
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

	bool ResourceService::HasResource(const ResourceID resourceId) const noexcept
	{
		const auto lock = std::shared_lock(stateMutex);
		return resourceContainer.Contains(resourceId);
	}

	bool ResourceService::IsResourceTypeOf(const ResourceID resourceId, const std::span<const std::type_index> types) const
	{
		const auto lock = std::shared_lock(stateMutex);
		return CheckResourceType(resourceId, types);
	}

	std::shared_ptr<IResourceRequest> ResourceService::LoadResource(const ResourceID resourceId) const
	{
		const auto lock = std::shared_lock(stateMutex);
		return MakeResourceRequest(resourceId);
	}

	std::shared_ptr<IResourceRequest> ResourceService::LoadResource(const ResourceID resourceId, const std::span<const std::type_index> types) const
	{
		const auto lock = std::shared_lock(stateMutex);

		if (!CheckResourceType(resourceId, types)) [[unlikely]]
		{
			throw std::invalid_argument("Invalid type");
		}

		return MakeResourceRequest(resourceId);
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
				for (const ResourceID dependencyId : resource.dependencies)
				{
					if (!IsResourceIDValid(dependencyId)) [[unlikely]]
					{
						throw std::invalid_argument(std::format("Resource ID of dependency is invalid: ID = '0x{:X}'", dependencyId.value));
					}
				}
				for (std::size_t i = 1uz; i < resource.dependencies.size(); ++i)
				{
					for (std::size_t j = 0uz; j < i; ++j)
					{
						if (resource.dependencies[i] == resource.dependencies[j]) [[unlikely]]
						{
							throw std::invalid_argument(std::format("Same resource ID is used in dependencies twice: ID = '0x{:X}'", resource.dependencies[i].value));
						}
					}
				}

				IResourceLoader* const loader = FindLoader(resource.type);
				if (!loader) [[unlikely]]
				{
					throw std::logic_error(std::format("No resource loader found for type '0x{:X}'", resource.type.value));
				}

				ResourceLoadData loadData;
				loader->PrepareResource(ResourceLoadInfo
				{
					.type = resource.type,
					.dataMeta = resource.dataMeta,
					.loadMeta = resource.loadMeta,
					.dataAccessTypes = dataAccessTypes
				}, loadData);

				if (loadData.dataAccessTypeIndex >= dataAccessTypes.size()) [[unlikely]]
				{
					throw std::logic_error("Loader set invalid access type");
				}
				for (std::size_t i = 1uz; i < loadData.outputTypes.size(); ++i)
				{
					for (std::size_t j = 0uz; j < i; ++j)
					{
						if (loadData.outputTypes[i] == loadData.outputTypes[j]) [[unlikely]]
						{
							throw std::logic_error("Loader set duplicate output types");
						}
					}
				}
				for (std::size_t i = 1uz; i < loadData.loadData.size(); ++i)
				{
					for (std::size_t j = 0uz; j < i; ++j)
					{
						if (loadData.loadData[i].second == loadData.loadData[j].second) [[unlikely]]
						{
							throw std::logic_error("Loader set duplicate load data types");
						}
					}
				}

				resourceContainer.Add(resource.id, Resource
				{
					.id = resource.id,
					.type = resource.type,
					.dependencies = std::vector(resource.dependencies.cbegin(), resource.dependencies.cend()),
					.loadData = std::move(loadData.loadData),
					.outputTypes = std::move(loadData.outputTypes),
					.collection = collection.id,
					.index = resource.dataIndex,
					.dataAccessType = dataAccessTypes[loadData.dataAccessTypeIndex]
				});

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

		return collection;
	}

	void ResourceService::UnregisterCollection(IResourceProvider& provider, const ResourceCollection collection)
	{
		const auto lock = std::unique_lock(stateMutex);

		assert(resourceCollectionVersions[collection.id] == collection.version && "Invalid collection");

		const std::size_t index = collectionContainer.IndexOf(collection.id);
		assert(index < collectionContainer.Size() && &collectionContainer.Provider(index) == &provider && "invalid collection");

		for (const ResourceID resourceId : collectionContainer.Resources(index))
		{
			resourceContainer.Remove(resourceId);
		}

		collectionContainer.Remove(index);
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
				throw std::logic_error("One of resource loader types is still in use");
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

	bool ResourceService::CheckResourceType(const ResourceID resourceId, const std::span<const std::type_index> types) const
	{
		if (const Resource* const resource = resourceContainer.FindResource(resourceId)) [[likely]]
		{
			for (const std::type_index type : types)
			{
				if (!std::ranges::contains(resource->outputTypes, type))
				{
					return false;
				}
			}

			return true;
		}

		throw std::invalid_argument("Resource not found");
	}

	std::shared_ptr<IResourceRequest> ResourceService::MakeResourceRequest(const ResourceID resourceId) const
	{
		const Resource* const resource = resourceContainer.FindResource(resourceId);
		if (!resource) [[unlikely]]
		{
			throw std::invalid_argument("Resource not found");
		}

		// TODO: Add caching here

		std::vector<std::shared_ptr<const IResourceRequest>> dependencies;
		dependencies.reserve(resource->dependencies.size());
		for (const ResourceID dependency : resource->dependencies)
		{
			dependencies.push_back(MakeResourceRequest(dependency));
		}

		IResourceProvider& provider = collectionContainer.Provider(collectionContainer.IndexOf(resource->collection));
		const auto collection = ResourceCollection{.id = resource->collection, .version = resourceCollectionVersions[resource->collection]};
		std::shared_ptr<void> dataAccess = provider.GetResourceData(collection, resource->index, resource->dataAccessType);

		IResourceLoader* const loader = FindLoader(resource->type);
		assert(loader && "Loader not found.");

		const auto request = std::make_shared<ResourceRequest>(*resource, std::move(dataAccess), std::move(dependencies), *loader);

		return request;
	}
}
