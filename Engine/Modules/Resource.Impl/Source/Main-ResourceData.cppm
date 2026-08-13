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

export module PonyEngine.Resource.Impl:ResourceData;

import std;

import :ResourceInfo;

export namespace PonyEngine::Resource
{
	class ResourceData final
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit ResourceData(std::size_t outputTypeCount);
		ResourceData(const ResourceData&) = delete;
		ResourceData(ResourceData&&) = delete;

		~ResourceData() noexcept = default;

		[[nodiscard("Pure function")]]
		std::shared_ptr<const void> MainResource() const noexcept;
		[[nodiscard("Pure function")]]
		std::span<const void* const> Resources() const noexcept;

		void SetResource(const std::shared_ptr<const void>& mainResource, std::span<const void* const> resources) noexcept;

		ResourceData& operator =(const ResourceData&) = delete;
		ResourceData& operator =(ResourceData&&) = delete;

	private:
		std::weak_ptr<const void> mainResource;
		std::vector<const void*> resources;
	};
}

namespace PonyEngine::Resource
{
	ResourceData::ResourceData(const std::size_t outputTypeCount) :
		resources(outputTypeCount, nullptr)
	{
	}

	std::shared_ptr<const void> ResourceData::MainResource() const noexcept
	{
		return mainResource.lock();
	}

	std::span<const void* const> ResourceData::Resources() const noexcept
	{
		return resources;
	}

	void ResourceData::SetResource(const std::shared_ptr<const void>& mainResource, const std::span<const void* const> resources) noexcept
	{
		assert(mainResource && "Main resource is nullptr.");
		assert(std::ranges::contains(resources, nullptr) && "Resource is nullptr.");
		assert(this->resources.size() == resources.size() && "Incorrect resource count.");

		this->mainResource = mainResource;
		this->resources.assign_range(resources);
	}
}
