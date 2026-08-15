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

export module PonyEngine.Resource.Impl:ResourceContainer;

import std;

import PonyEngine.Resource.Ext;

import :Resource;

export namespace PonyEngine::Resource
{
	/// @brief Resource container.
	class ResourceContainer final
	{
	public:
		[[nodiscard("Pure constructor")]]
		ResourceContainer() noexcept = default;
		ResourceContainer(const ResourceContainer&) = delete;
		ResourceContainer(ResourceContainer&&) = delete;

		~ResourceContainer() noexcept = default;

		/// @brief Checks if the container has the @p resourceId.
		/// @param resourceId Resource ID to find.
		/// @return @a True if it contains; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool Contains(ResourceID resourceId) const noexcept;
		/// @brief Gets a resource.
		/// @param resourceId Resource ID. It must be contained by the container.
		/// @return Resource.
		[[nodiscard("Pure function")]]
		const std::shared_ptr<Resource>& GetResource(ResourceID resourceId) const noexcept;
		/// @brief Gets how many resources are of type @p type.
		/// @param type Resource type.
		/// @return Type count.
		[[nodiscard("Pure function")]]
		std::size_t TypeCount(ResourceType type) const noexcept;

		/// @brief Adds the resource.
		/// @param resource Resource to add.
		void Add(std::shared_ptr<Resource>&& resource);
		/// @brief Removes a resource.
		/// @param id Resource ID to remove.
		void Remove(ResourceID id) noexcept;
		/// @brief Clears the container.
		void Clear() noexcept;

		ResourceContainer& operator =(const ResourceContainer&) = delete;
		ResourceContainer& operator =(ResourceContainer&&) = delete;

	private:
		std::unordered_map<ResourceID, std::shared_ptr<Resource>> resources; ///< Resources.
		std::unordered_map<ResourceType, std::size_t> typeCounts; ///< Type counts.
	};
}

namespace PonyEngine::Resource
{
	bool ResourceContainer::Contains(const ResourceID resourceId) const noexcept
	{
		return resources.contains(resourceId);
	}

	const std::shared_ptr<Resource>& ResourceContainer::GetResource(const ResourceID resourceId) const noexcept
	{
		const auto position = resources.find(resourceId);
		assert(position != resources.cend());
		return position->second;
	}

	std::size_t ResourceContainer::TypeCount(const ResourceType type) const noexcept
	{
		if (const auto position = typeCounts.find(type); position != typeCounts.cend())
		{
			return position->second;
		}

		return 0uz;
	}

	void ResourceContainer::Add(std::shared_ptr<Resource>&& resource)
	{
		const ResourceID id = resource->info->id;
		const ResourceType type = resource->info->type;

		if (!typeCounts.contains(type))
		{
			typeCounts[type] = 0uz;
		}
		++typeCounts[type];

		try
		{
			const auto [_, added] = resources.try_emplace(id, std::move(resource));
			assert(added && "The resource not added.");
		}
		catch (...)
		{
			--typeCounts[type];
			throw;
		}
	}

	void ResourceContainer::Remove(const ResourceID id) noexcept
	{
		if (const auto position = resources.find(id); position != resources.cend())
		{
			--typeCounts[position->second->info->type];
			resources.erase(position);
		}
	}

	void ResourceContainer::Clear() noexcept
	{
		typeCounts.clear();
		resources.clear();
	}
}
