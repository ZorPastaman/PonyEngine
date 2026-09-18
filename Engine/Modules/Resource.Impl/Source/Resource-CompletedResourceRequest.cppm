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

export module PonyEngine.Resource.Impl:CompletedResourceRequest;

import std;

import PonyEngine.Async;
import PonyEngine.Resource.Ext;

import :Resource;
import :Utility;

export namespace PonyEngine::Resource
{
	/// @brief Resource request that is used when a resource was already loaded and still alive.
	class CompletedResourceRequest final : public IResourceRequest
	{
	public:
		/// @brief Creates a completed resource request.
		/// @param resource Resource. Must be alive.
		/// @param mainResource Main resource. Must be alive.
		[[nodiscard("Pure constructor")]]
		CompletedResourceRequest(std::shared_ptr<const class Resource> resource, std::shared_ptr<const void> mainResource) noexcept;
		CompletedResourceRequest(const CompletedResourceRequest&) = delete;
		CompletedResourceRequest(CompletedResourceRequest&&) = delete;

		~CompletedResourceRequest() noexcept = default;

		[[nodiscard("Pure function")]] 
		virtual struct ResourceID ResourceID() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual bool HasInterfaces(std::span<const std::type_index> types) const noexcept override;

		[[nodiscard("Pure function")]] 
		virtual Async::RequestStatus Status() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual std::shared_ptr<const void> Resource(std::type_index type) const override;
		[[nodiscard("Pure function")]] 
		virtual const std::exception_ptr& Exception() const override;

		virtual void Cancel() override;

		virtual void Wait() const noexcept override;

		CompletedResourceRequest& operator =(const CompletedResourceRequest&) = delete;
		CompletedResourceRequest& operator =(CompletedResourceRequest&&) = delete;

	private:
		std::shared_ptr<const class Resource> resource; ///< Resource.
		std::shared_ptr<const void> mainResource; ///< Main resource.
	};
}

namespace PonyEngine::Resource
{
	struct ResourceID CompletedResourceRequest::ResourceID() const noexcept
	{
		return resource->ID();
	}

	CompletedResourceRequest::CompletedResourceRequest(std::shared_ptr<const class Resource> resource, std::shared_ptr<const void> mainResource) noexcept :
		resource(std::move(resource)),
		mainResource(std::move(mainResource))
	{
		assert(this->resource && "Resource is nullptr.");
		assert(this->mainResource && "Main resource is nullptr.");
	}

	bool CompletedResourceRequest::HasInterfaces(const std::span<const std::type_index> types) const noexcept
	{
		return CheckTypes(types, resource->InterfaceTypes());
	}

	Async::RequestStatus CompletedResourceRequest::Status() const noexcept
	{
		return Async::RequestStatus::Success;
	}

	std::shared_ptr<const void> CompletedResourceRequest::Resource(const std::type_index type) const
	{
		return MakeResource(type, resource->InterfaceTypes(), resource->ResourceInterfaces(), mainResource);
	}

	const std::exception_ptr& CompletedResourceRequest::Exception() const
	{
		throw std::logic_error("Invalid status");
	}

	void CompletedResourceRequest::Cancel()
	{
	}

	void CompletedResourceRequest::Wait() const noexcept
	{
	}
}
