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

export module PonyEngine.Resource.Impl:ResourceCache;

import std;

export namespace PonyEngine::Resource
{
	class ResourceCache final
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit ResourceCache(std::span<const std::type_index> outputTypes);
		ResourceCache(const ResourceCache&) = delete;
		ResourceCache(ResourceCache&&) = delete;

		~ResourceCache() noexcept = default;

		[[nodiscard("Pure function")]]
		std::span<const std::type_index> OutputTypes() const noexcept;

		[[nodiscard("Pure function")]]
		std::shared_ptr<const void> MainResource() const;
		[[nodiscard("Pure function")]]
		std::shared_ptr<const void> Resource(std::type_index type) const;

		void Set(const std::shared_ptr<const void>& mainResource, std::span<const std::pair<const void*, std::type_index>> resources);

		ResourceCache& operator =(const ResourceCache&) = delete;
		ResourceCache& operator =(ResourceCache&&) = delete;

	private:
		std::vector<std::type_index> outputTypes; ///< Resource output types.

		std::weak_ptr<const void> mainResource;
		std::vector<const void*> resources;
	};
}

namespace PonyEngine::Resource
{
	ResourceCache::ResourceCache(const std::span<const std::type_index> outputTypes) :
		outputTypes(outputTypes.cbegin(), outputTypes.cend()),
		resources(this->outputTypes.size())
	{
	}

	std::span<const std::type_index> ResourceCache::OutputTypes() const noexcept
	{
		return outputTypes;
	}

	std::shared_ptr<const void> ResourceCache::MainResource() const
	{
		return mainResource.lock();
	}

	std::shared_ptr<const void> ResourceCache::Resource(const std::type_index type) const
	{
		for (std::size_t i = 0uz; i < outputTypes.size(); ++i)
		{
			if (outputTypes[i] == type)
			{
				std::shared_ptr<const void> lockedMainResource = mainResource.lock();
				return lockedMainResource ? std::shared_ptr<const void>(std::move(lockedMainResource), resources[i]) : nullptr;
			}
		}

		throw std::invalid_argument("Invalid type");
	}

	void ResourceCache::Set(const std::shared_ptr<const void>& mainResource, const std::span<const std::pair<const void*, std::type_index>> resources)
	{
		assert(this->mainResource.expired() && "Double resource cache set.");

		assert(resources.size() == outputTypes.size() && "Invalid resource list.");
		for (std::size_t i = 1uz; i < resources.size(); ++i)
		{
			for (std::size_t j = 0uz; j < i; ++j)
			{
				assert(resources[i].second != resources[j].second && "Resource type duplicate.");
			}
		}

		for (const auto [resource, type] : resources)
		{
			assert(resource && "Resource is nullptr.");
			const std::size_t index = std::ranges::find(outputTypes, type) - outputTypes.cbegin();
			assert(index < outputTypes.size() && "Invalid type.");
			this->resources[index] = resource;
		}

		assert(mainResource && "Main resource is nullptr.");
		this->mainResource = mainResource;
	}
}
