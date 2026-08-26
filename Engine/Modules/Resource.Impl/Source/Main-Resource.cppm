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

export module PonyEngine.Resource.Impl:Resource;

import std;

import PonyEngine.Resource.Ext;

export namespace PonyEngine::Resource
{
	/// @brief Resource.
	class Resource final
	{
	public:
		/// @brief Creates a resource.
		/// @param id Resource ID.
		/// @param type Resource type.
		/// @param collection Resource collection.
		/// @param collectionResourceIndex Collection resource index.
		/// @param dataAccessType Data access type.
		/// @param loadData Load data.
		/// @param interfaceTypes Interface types.
		[[nodiscard("Pure constructor")]]
		Resource(ResourceID id, ResourceType type, ResourceCollectionID collection, std::size_t collectionResourceIndex, std::type_index dataAccessType,
			std::vector<std::pair<std::shared_ptr<const void>, std::type_index>>&& loadData, std::vector<std::type_index>&& interfaceTypes);
		Resource(const Resource&) = delete;
		Resource(Resource&&) = delete;

		~Resource() noexcept = default;

		/// @brief Gets the resource ID.
		/// @return Resource ID.
		[[nodiscard("Pure function")]]
		ResourceID ID() const noexcept;
		/// @brief Gets the resource type.
		/// @return Resource type.
		[[nodiscard("Pure function")]]
		ResourceType Type() const noexcept;

		/// @brief Gets the resource collection.
		/// @return Resource collection.
		[[nodiscard("Pure function")]]
		ResourceCollectionID Collection() const noexcept;
		/// @brief Gets the collection resource index.
		/// @return Collection resource index.
		[[nodiscard("Pure function")]]
		std::size_t CollectionResourceIndex() const noexcept;
		/// @brief Gets the data access type.
		/// @return Data access type.
		[[nodiscard("Pure function")]]
		std::type_index DataAccessType() const noexcept;

		/// @brief Gets the load data.
		/// @return Load data.
		[[nodiscard("Pure function")]]
		std::span<const std::pair<std::shared_ptr<const void>, std::type_index>> LoadData() const noexcept;

		/// @brief Gets the interface types.
		/// @return Interface types.
		[[nodiscard("Pure function")]]
		std::span<const std::type_index> InterfaceTypes() const noexcept;

		/// @brief Gets the main resource.
		/// @return Main resource. May be nullptr.
		[[nodiscard("Pure function")]]
		std::shared_ptr<const void> MainResource() const noexcept;
		/// @brief Gets the resource interfaces.
		/// @return Resource interfaces. Invalid if the @p MainResource is nullptr. Synced with the @p InterfaceTypes() by index.
		[[nodiscard("Pure function")]]
		std::span<const void* const> ResourceInterfaces() const noexcept;
		/// @brief Sets the resource data.
		/// @param mainResource Main resource. Mustn't be nullptr.
		/// @param resourceInterfaces Resource interfaces. Must be valid and synced with the @p InterfaceTypes() by index.
		void SetResourceData(const std::shared_ptr<const void>& mainResource, std::span<const void* const> resourceInterfaces) noexcept;

		/// @brief Locks the resource.
		/// @return Resource lock.
		[[nodiscard("Pure function")]]
		std::lock_guard<std::mutex> Lock() noexcept;

		Resource& operator =(const Resource&) = delete;
		Resource& operator =(Resource&&) = delete;

	private:
		ResourceID id; ///< Resource ID.
		ResourceType type; ///< Resource type.

		ResourceCollectionID collection; ///< Collection ID that uses this resource.
		std::size_t collectionResourceIndex; ///< Collection resource index.
		std::type_index dataAccessType; ///< Data access type.

		std::vector<std::pair<std::shared_ptr<const void>, std::type_index>> loadData; ///< Load data.

		std::vector<std::type_index> interfaceTypes; ///< Interface types.

		std::weak_ptr<const void> mainResource; ///< Main resource.
		std::vector<const void*> resourceInterfaces; ///< Resource interfaces.

		std::mutex mutex; ///< Resource mutex.
	};
}

namespace PonyEngine::Resource
{
	Resource::Resource(const ResourceID id, const ResourceType type, const ResourceCollectionID collection, const std::size_t collectionResourceIndex, 
		const std::type_index dataAccessType, std::vector<std::pair<std::shared_ptr<const void>, std::type_index>>&& loadData, std::vector<std::type_index>&& interfaceTypes) :
		id(id),
		type(type),
		collection(collection),
		collectionResourceIndex{collectionResourceIndex},
		dataAccessType(dataAccessType),
		loadData(std::move(loadData)),
		interfaceTypes(std::move(interfaceTypes)),
		resourceInterfaces(this->interfaceTypes.size())
	{
	}

	ResourceID Resource::ID() const noexcept
	{
		return id;
	}

	ResourceType Resource::Type() const noexcept
	{
		return type;
	}

	ResourceCollectionID Resource::Collection() const noexcept
	{
		return collection;
	}

	std::size_t Resource::CollectionResourceIndex() const noexcept
	{
		return collectionResourceIndex;
	}

	std::type_index Resource::DataAccessType() const noexcept
	{
		return dataAccessType;
	}

	std::span<const std::pair<std::shared_ptr<const void>, std::type_index>> Resource::LoadData() const noexcept
	{
		return loadData;
	}

	std::span<const std::type_index> Resource::InterfaceTypes() const noexcept
	{
		return interfaceTypes;
	}

	std::shared_ptr<const void> Resource::MainResource() const noexcept
	{
		return mainResource.lock();
	}

	std::span<const void* const> Resource::ResourceInterfaces() const noexcept
	{
		return resourceInterfaces;
	}

	void Resource::SetResourceData(const std::shared_ptr<const void>& mainResource, const std::span<const void* const> resourceInterfaces) noexcept
	{
		assert(mainResource && "Main resource is nullptr.");
		assert(this->resourceInterfaces.size() == resourceInterfaces.size() && "Invalid resource interface count.");

		this->mainResource = mainResource;
		this->resourceInterfaces.assign_range(resourceInterfaces);
	}

	std::lock_guard<std::mutex> Resource::Lock() noexcept
	{
		return std::lock_guard(mutex);
	}
}
