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

import :ResourceEntry;

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
		const ResourceEntry* GetResource(ResourceID resourceId) const noexcept;
		[[nodiscard("Pure function")]]
		bool Empty() const noexcept;

		void AddResource(const ResourceParams& params, IResourceProvider& provider, ResourceHandle handle);
		void RemoveResource(ResourceHandle handle);
		void Clear() noexcept;

		[[nodiscard("Pure function")]]
		const std::unordered_map<ResourceHandle, ResourceID>& Handles() const noexcept;

		ResourceContainer& operator =(const ResourceContainer&) = delete;
		ResourceContainer& operator =(ResourceContainer&&) = delete;

	private:
		std::unordered_map<ResourceID, ResourceEntry> resources;
		std::unordered_map<ResourceHandle, ResourceID> handleToIdMap;
	};
}

namespace PonyEngine::Resource
{
	const ResourceEntry* ResourceContainer::GetResource(const ResourceID resourceId) const noexcept
	{
		if (const auto position = resources.find(resourceId); position != resources.cend())
		{
			return &position->second;
		}

		return nullptr;
	}

	bool ResourceContainer::Empty() const noexcept
	{
		return handleToIdMap.empty();
	}

	void ResourceContainer::AddResource(const ResourceParams& params, IResourceProvider& provider, const ResourceHandle handle)
	{
		assert(!handleToIdMap.contains(handle) && "The handle has already been added.");

		if (resources.contains(params.id)) [[unlikely]]
		{
			throw std::invalid_argument("Resource ID was already added");
		}

		handleToIdMap.emplace(handle, params.id);
		try
		{
			resources[params.id] = ResourceEntry
			{
				.id = params.id,
				.type = params.type,
				.availability = params.availability,
				.index = params.index,
				.provider = &provider
			};
		}
		catch (...)
		{
			handleToIdMap.erase(handle);
			throw;
		}
	}

	void ResourceContainer::RemoveResource(const ResourceHandle handle)
	{
		if (const auto position = handleToIdMap.find(handle); position != handleToIdMap.cend())
		{
			resources.erase(position->second);
			handleToIdMap.erase(position);
		}
		else
		{
			throw std::invalid_argument("Resource handle not found");
		}
	}

	void ResourceContainer::Clear() noexcept
	{
		resources.clear();
		handleToIdMap.clear();
	}

	const std::unordered_map<ResourceHandle, ResourceID>& ResourceContainer::Handles() const noexcept
	{
		return handleToIdMap;
	}
}
