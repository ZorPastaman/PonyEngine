/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Resource.Impl:Resource;

import std;

import PonyEngine.Resource.Ext;

export namespace PonyEngine::Resource
{
	class Resource final
	{
	public:
		[[nodiscard("Pure constructor")]]
		Resource(struct ResourceID id, ResourceType type, std::span<const struct ResourceID> dependencies, ResourceCollectionID collection, std::size_t collectionResourceIndex,
			std::type_index dataAccessType, std::span<const std::pair<std::shared_ptr<const void>, std::type_index>> loadData, std::span<const std::type_index> outputTypes);
		Resource(const Resource&) = delete;
		Resource(Resource&&) = delete;

		~Resource() noexcept = default;

		[[nodiscard("Pure function")]]
		ResourceID ResourceID() const noexcept;
		[[nodiscard("Pure function")]]
		ResourceType Type() const noexcept;

		[[nodiscard("Pure function")]]
		std::span<const std::type_index> OutputTypes() const noexcept;

		[[nodiscard("Pure function")]]
		std::shared_ptr<const void> MainResource() const noexcept;
		[[nodiscard("Pure function")]]
		std::span<const void* const> Resources() const noexcept;

		[[nodiscard("Pure function")]]
		std::lock_guard<std::mutex> Lock() const noexcept;

		Resource& operator =(const Resource&) = delete;
		Resource& operator =(Resource&&) = delete;

	private:
		struct ResourceID id;
		ResourceType type;

		std::vector<struct ResourceID> dependencies;

		ResourceCollectionID collection;
		std::size_t collectionResourceIndex;
		std::type_index dataAccessType;

		std::vector<std::pair<std::shared_ptr<const void>, std::type_index>> loadData;

		std::vector<std::type_index> outputTypes;
		
		std::weak_ptr<const void> mainResource;
		std::vector<const void*> resources;

		mutable std::mutex mutex;
	};
}

namespace PonyEngine::Resource
{
	Resource::Resource(const struct ResourceID id, const ResourceType type, const std::span<const struct ResourceID> dependencies, const ResourceCollectionID collection,
		const std::size_t collectionResourceIndex, const std::type_index dataAccessType, 
		const std::span<const std::pair<std::shared_ptr<const void>, std::type_index>> loadData, const std::span<const std::type_index> outputTypes) :
		id(id),
		type(type),
		dependencies(dependencies.cbegin(), dependencies.cend()),
		collection{collection},
		collectionResourceIndex{collectionResourceIndex},
		dataAccessType(dataAccessType),
		loadData(loadData.cbegin(), loadData.cend()),
		outputTypes(outputTypes.cbegin(), outputTypes.cend()),
		resources(this->outputTypes.size(), nullptr)
	{
	}

	ResourceID Resource::ResourceID() const noexcept
	{
		return id;
	}

	ResourceType Resource::Type() const noexcept
	{
		return type;
	}

	std::span<const std::type_index> Resource::OutputTypes() const noexcept
	{
		return outputTypes;
	}

	std::shared_ptr<const void> Resource::MainResource() const noexcept
	{
		return mainResource.lock();
	}

	std::span<const void* const> Resource::Resources() const noexcept
	{
		return resources;
	}

	std::lock_guard<std::mutex> Resource::Lock() const noexcept
	{
		return std::lock_guard(mutex);
	}
}
