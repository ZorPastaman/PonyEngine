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

export namespace PonyEngine::Resource
{
	/// @brief Resource data.
	class ResourceData final
	{
	public:
		/// @brief Creates a resource data.
		/// @param outputTypeCount Output type count.
		[[nodiscard("Pure constructor")]]
		explicit ResourceData(std::size_t outputTypeCount);
		ResourceData(const ResourceData&) = delete;
		ResourceData(ResourceData&&) = delete;

		~ResourceData() noexcept = default;

		/// @brief Locks the main resource.
		/// @return Main resource. May be nullptr.
		[[nodiscard("Pure function")]]
		std::shared_ptr<const void> MainResource() const noexcept;
		/// @brief Gets the output resources.
		/// @return Output resources.
		[[nodiscard("Pure function")]]
		std::span<const void* const> Resources() const noexcept;

		/// @brief Sets the resource.
		/// @param mainResource Main resource.
		/// @param resources Output resources. Must follow the same type order as the resource info output types.
		void SetResource(const std::shared_ptr<const void>& mainResource, std::span<const void* const> resources) noexcept;

		ResourceData& operator =(const ResourceData&) = delete;
		ResourceData& operator =(ResourceData&&) = delete;

	private:
		std::weak_ptr<const void> mainResource; ///< Main resource.
		std::vector<const void*> resources; ///< Output resources.
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
