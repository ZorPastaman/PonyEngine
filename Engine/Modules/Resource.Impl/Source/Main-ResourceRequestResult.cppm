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

export module PonyEngine.Resource.Impl:ResourceRequestResult;

import std;

import PonyEngine.Resource;

import :ResourceInfo;
import :ResourceData;
import :Utility;

export namespace PonyEngine::Resource
{
	/// @brief Resource request result.
	class ResourceRequestResult final : public IResourceRequestResult
	{
	public:
		/// @brief Creates a resource request result.
		/// @param info Resource info.
		/// @param data Resource data.
		/// @param mainResource Main resource.
		[[nodiscard("Pure function")]]
		ResourceRequestResult(const std::shared_ptr<const ResourceInfo>& info, const std::shared_ptr<const ResourceData>& data,
			const std::shared_ptr<const void>& mainResource) noexcept;
		ResourceRequestResult(const ResourceRequestResult&) = delete;
		ResourceRequestResult(ResourceRequestResult&&) = delete;

		~ResourceRequestResult() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual bool IsTypeOf(std::span<const std::type_index> types) const noexcept override;

		[[nodiscard("Pure function")]] 
		virtual std::shared_ptr<const void> Resource(std::type_index type) const override;

		ResourceRequestResult& operator =(const ResourceRequestResult&) = delete;
		ResourceRequestResult& operator =(ResourceRequestResult&&) = delete;

	private:
		std::shared_ptr<const ResourceInfo> info; ///< Resource info.
		std::shared_ptr<const ResourceData> data; ///< Resource data.
		std::shared_ptr<const void> mainResource; ///< Main resource.
	};
}

namespace PonyEngine::Resource
{
	ResourceRequestResult::ResourceRequestResult(const std::shared_ptr<const ResourceInfo>& info, const std::shared_ptr<const ResourceData>& data, 
		const std::shared_ptr<const void>& mainResource) noexcept :
		info(info),
		data(data),
		mainResource(mainResource)
	{
		assert(this->info && "Info is nullptr.");
		assert(this->data && "Data is nullptr.");
		assert(this->mainResource && "Main resource is nullptr.");
		assert(data->MainResource() == this->mainResource && "Main resource mismatch.");
	}

	bool ResourceRequestResult::IsTypeOf(const std::span<const std::type_index> types) const noexcept
	{
		return CheckTypes(types, info->outputTypes);
	}

	std::shared_ptr<const void> ResourceRequestResult::Resource(const std::type_index type) const
	{
		if (!mainResource) [[unlikely]]
		{
			throw std::logic_error("Invalid state");
		}

		for (std::size_t i = 0uz; i < info->outputTypes.size(); ++i)
		{
			if (info->outputTypes[i] == type)
			{
				return std::shared_ptr<const void>(mainResource, data->Resources()[i]);
			}
		}

		throw std::invalid_argument("Invalid type");
	}
}
