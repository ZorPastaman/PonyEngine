/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Resource.Impl:CollectionContainer;

import std;

import PonyEngine.Resource.Ext;

export namespace PonyEngine::Resource
{
	class CollectionContainer final
	{
	public:
		[[nodiscard("Pure constructor")]]
		CollectionContainer() noexcept = default;
		CollectionContainer(const CollectionContainer&) = delete;
		CollectionContainer(CollectionContainer&&) = delete;

		~CollectionContainer() noexcept = default;

		[[nodiscard("Pure function")]]
		std::size_t Size() const noexcept;

		[[nodiscard("Pure function")]]
		std::size_t IndexOf(ResourceCollectionID collection) const noexcept;

		[[nodiscard("Pure function")]]
		ResourceCollectionID Collection(std::size_t index) const noexcept;
		[[nodiscard("Pure function")]]
		IResourceProvider& Provider(std::size_t index) const noexcept;
		[[nodiscard("Pure function")]]
		std::span<const ResourceID> Resources(std::size_t index) const noexcept;

		void Add(ResourceCollectionID collection, IResourceProvider& provider, std::vector<ResourceID>&& resources);
		void Remove(std::size_t index) noexcept;
		void Clear() noexcept;

		CollectionContainer& operator =(const CollectionContainer&) = delete;
		CollectionContainer& operator =(CollectionContainer&&) = delete;

	private:
		std::vector<ResourceCollectionID> collections;
		std::vector<IResourceProvider*> providers;
		std::vector<std::vector<ResourceID>> resources;
	};
}

namespace PonyEngine::Resource
{
	std::size_t CollectionContainer::Size() const noexcept
	{
		return collections.size();
	}

	std::size_t CollectionContainer::IndexOf(const ResourceCollectionID collection) const noexcept
	{
		auto position = std::ranges::lower_bound(collections, collection);
		if (position != collections.cend() && *position != collection)
		{
			position = collections.cend();
		}

		return position - collections.cbegin();
	}

	ResourceCollectionID CollectionContainer::Collection(const std::size_t index) const noexcept
	{
		return collections[index];
	}

	IResourceProvider& CollectionContainer::Provider(const std::size_t index) const noexcept
	{
		return *providers[index];
	}

	std::span<const ResourceID> CollectionContainer::Resources(const std::size_t index) const noexcept
	{
		return resources[index];
	}

	void CollectionContainer::Add(const ResourceCollectionID collection, IResourceProvider& provider, std::vector<ResourceID>&& resources)
	{
		const std::size_t initialSize = Size();
		const std::size_t index = std::ranges::lower_bound(collections, collection) - collections.cbegin();

		try
		{
			collections.insert(collections.cbegin() + index, collection);
			providers.insert(providers.cbegin() + index, &provider);
			this->resources.insert(this->resources.cbegin() + index, std::move(resources));
		}
		catch (...)
		{
			if (this->resources.size() != initialSize)
			{
				this->resources.erase(this->resources.cbegin() + index);
			}
			if (providers.size() != initialSize)
			{
				providers.erase(providers.cbegin() + index);
			}
			if (collections.size() != initialSize)
			{
				collections.erase(collections.cbegin() + index);
			}

			throw;
		}
	}

	void CollectionContainer::Remove(const std::size_t index) noexcept
	{
		resources.erase(resources.cbegin() + index);
		providers.erase(providers.cbegin() + index);
		collections.erase(collections.cbegin() + index);
	}

	void CollectionContainer::Clear() noexcept
	{
		resources.clear();
		providers.clear();
		collections.clear();
	}
}
