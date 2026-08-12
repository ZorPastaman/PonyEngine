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

export module PonyEngine.Resource.Impl:ResourceRequest;

import std;

import PonyEngine.Resource.Ext;

import :ResourceCache;
import :ResourceLoadRequest;

export namespace PonyEngine::Resource
{
	class ResourceRequest final : IResourceRequest
	{
	public:
		[[nodiscard("Pure constructor")]]
		ResourceRequest(struct ResourceID resourceId, const std::shared_ptr<ResourceCache>& cache, std::shared_ptr<const void>&& mainResource) noexcept;

		[[nodiscard("Pure function")]] 
		virtual struct ResourceID ResourceID() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual bool IsTypeOf(std::span<const std::type_index> types) const noexcept override;

		[[nodiscard("Pure function")]] 
		virtual RequestStatus Status() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual std::shared_ptr<const void> Resource(std::type_index type) const override;
		[[nodiscard("Pure function")]] 
		virtual const std::exception_ptr& Exception() const override;

		virtual void Cancel() override;

		virtual void Wait() const noexcept override;

		virtual void AddObserver(IResourceRequestObserver& observer) const override;
		virtual void RemoveObserver(IResourceRequestObserver& observer) const override;

	private:
		struct ResourceID resourceId;
		std::shared_ptr<ResourceCache> cache;
		std::shared_ptr<ResourceLoadRequest> loadRequest;
		std::shared_ptr<const void> mainResource;

		mutable std::vector<IResourceRequestObserver*> observers;
		bool observerCalled;
		mutable std::mutex observerMutex;

		std::atomic_bool canceled;

		static_assert(std::atomic_bool::is_always_lock_free, "Atomic bool isn't lock-free.");
	};
}

namespace PonyEngine::Resource
{
	ResourceRequest::ResourceRequest(const struct ResourceID resourceId, const std::shared_ptr<ResourceCache>& cache, std::shared_ptr<const void>&& mainResource) noexcept :
		resourceId{resourceId},	
		cache(cache),
		mainResource(std::move(mainResource)),
		observerCalled{false},
		canceled(false)
	{
	}

	struct ResourceID ResourceRequest::ResourceID() const noexcept
	{
		return resourceId;
	}

	bool ResourceRequest::IsTypeOf(const std::span<const std::type_index> types) const noexcept
	{
		const std::span<const std::type_index> outputTypes = cache->OutputTypes();

		for (const std::type_index type : types)
		{
			if (!std::ranges::contains(outputTypes, type))
			{
				return false;
			}
		}

		return true;
	}

	RequestStatus ResourceRequest::Status() const noexcept
	{
		return loadRequest ? loadRequest->Status() : RequestStatus::Success;
	}

	std::shared_ptr<const void> ResourceRequest::Resource(const std::type_index type) const
	{
		if (Status() != RequestStatus::Success)
		{
			throw std::logic_error("Invalid status");
		}

		return cache->Resource(type);
	}

	const std::exception_ptr& ResourceRequest::Exception() const
	{
		if (Status() != RequestStatus::Failure)
		{
			throw std::logic_error("Invalid status");
		}

		return loadRequest->Exception();
	}

	void ResourceRequest::Cancel()
	{
		if (!canceled.exchange(true))
		{
			if (loadRequest)
			{
				loadRequest->Cancel();
			}
		}
	}

	void ResourceRequest::Wait() const noexcept
	{
		if (loadRequest)
		{
			loadRequest->Wait();
		}
	}

	void ResourceRequest::AddObserver(IResourceRequestObserver& observer) const
	{
		const auto lock = std::lock_guard(observerMutex);
		observers.push_back(&observer);

		if (observerCalled)
		{
			observer.OnStatusChanged(resourceId);
		}
	}

	void ResourceRequest::RemoveObserver(IResourceRequestObserver& observer) const
	{
		const auto lock = std::lock_guard(observerMutex);
		if (const auto position = std::ranges::find(observers, &observer); position != observers.cend())
		{
			observers.erase(position);
		}

		assert(false && "Observer not found");
	}
}
