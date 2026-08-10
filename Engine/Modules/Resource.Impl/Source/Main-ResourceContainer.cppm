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
	class ResourceContainer final
	{
	public:
		[[nodiscard("Pure constructor")]]
		ResourceContainer() noexcept = default;
		ResourceContainer(const ResourceContainer&) = delete;
		ResourceContainer(ResourceContainer&&) = delete;

		~ResourceContainer() noexcept = default;

		[[nodiscard("Pure function")]]
		bool Contains(ResourceID resourceId) const noexcept;
		[[nodiscard("Pure function")]]
		const Resource* FindResource(ResourceID resourceId) const noexcept;
		[[nodiscard("Pure function")]]
		std::size_t TypeCount(ResourceType type) const noexcept;

		void Add(ResourceID id, Resource&& resource);
		void Remove(ResourceID id) noexcept;
		void Clear() noexcept;

		ResourceContainer& operator =(const ResourceContainer&) = delete;
		ResourceContainer& operator =(ResourceContainer&&) = delete;

	private:
		std::unordered_map<ResourceID, Resource> resources;
		std::unordered_map<ResourceType, std::size_t> typeCounts;
	};
}

namespace PonyEngine::Resource
{
	bool ResourceContainer::Contains(const ResourceID resourceId) const noexcept
	{
		return resources.contains(resourceId);
	}

	const Resource* ResourceContainer::FindResource(const ResourceID resourceId) const noexcept
	{
		if (const auto position = resources.find(resourceId); position != resources.cend())
		{
			return &position->second;
		}

		return nullptr;
	}

	std::size_t ResourceContainer::TypeCount(const ResourceType type) const noexcept
	{
		if (const auto position = typeCounts.find(type); position != typeCounts.cend())
		{
			return position->second;
		}

		return 0uz;
	}

	void ResourceContainer::Add(const ResourceID id, Resource&& resource)
	{
		if (!typeCounts.contains(resource.type))
		{
			typeCounts[resource.type] = 0uz;
		}
		++typeCounts[resource.type];

		try
		{
			const auto [_, added] = resources.try_emplace(id, std::move(resource));
			assert(added && "The resource not added.");
		}
		catch (...)
		{
			--typeCounts[resource.type];
			throw;
		}
	}

	void ResourceContainer::Remove(const ResourceID id) noexcept
	{
		if (const auto position = resources.find(id); position != resources.cend())
		{
			--typeCounts[position->second.type];
			resources.erase(position);
		}
	}

	void ResourceContainer::Clear() noexcept
	{
		typeCounts.clear();
		resources.clear();
	}
}
