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
import PonyEngine.Utility;

export namespace PonyEngine::Resource
{
	/// @brief Resource collection container.
	class CollectionContainer final
	{
	public:
		[[nodiscard("Pure constructor")]]
		CollectionContainer() noexcept = default;
		CollectionContainer(const CollectionContainer&) = delete;
		CollectionContainer(CollectionContainer&&) = delete;

		~CollectionContainer() noexcept = default;

		/// @brief Gets the size.
		/// @return Size.
		[[nodiscard("Pure function")]]
		std::size_t Size() const noexcept;

		/// @brief Tries to find an index of the collection.
		/// @param collection Collection to find.
		/// @return Index or size if not found.
		[[nodiscard("Pure function")]]
		std::size_t IndexOf(ResourceCollectionID collection) const noexcept;

		/// @brief Gets a collection.
		/// @param index Collection index.
		/// @return Collection.
		[[nodiscard("Pure function")]]
		ResourceCollectionID Collection(std::size_t index) const noexcept;
		/// @brief Gets a collection provider.
		/// @param index Collection index.
		/// @return Provider.
		[[nodiscard("Pure function")]]
		IResourceProvider& Provider(std::size_t index) const noexcept;
		/// @brief Gets resource IDs.
		/// @param index Collection index.
		/// @return Resource IDs.
		[[nodiscard("Pure function")]]
		std::span<const ResourceID> Resources(std::size_t index) const noexcept;

		/// @brief Adds the collection.
		/// @param collection Collection to add.
		/// @param provider Provider.
		/// @param resources Resources.
		void Add(ResourceCollectionID collection, IResourceProvider& provider, std::vector<ResourceID>&& resources);
		/// @brief Removes a collection.
		/// @param index Collection index.
		void Remove(std::size_t index) noexcept;
		/// @brief Clears the container.
		void Clear() noexcept;

		CollectionContainer& operator =(const CollectionContainer&) = delete;
		CollectionContainer& operator =(CollectionContainer&&) = delete;

	private:
		std::vector<ResourceCollectionID> collections; ///< Resource collections.
		std::vector<IResourceProvider*> providers; ///< Providers.
		std::vector<std::vector<ResourceID>> resources; ///< Resource IDs.
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
		auto scopeGuardFlag = Utility::ScopeGuardFlag();

		const std::size_t index = std::ranges::lower_bound(collections, collection) - collections.cbegin();
		collections.insert(collections.cbegin() + index, collection);
		const auto collectionsScopeGuard = Utility::ScopeGuard([&]() noexcept { collections.erase(collections.cbegin() + index); }, scopeGuardFlag);
		providers.insert(providers.cbegin() + index, &provider);
		const auto providersScopeGuard = Utility::ScopeGuard([&]() noexcept { providers.erase(providers.cbegin() + index); }, scopeGuardFlag);
		this->resources.insert(this->resources.cbegin() + index, std::move(resources));

		scopeGuardFlag.Release();
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
