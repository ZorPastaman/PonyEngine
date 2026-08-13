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

export module PonyEngine.Resource.Impl:ResourceLoadHandler;

import std;

import PonyEngine.Resource.Ext;

import :IResourceLoadObserver;
import :ResourceData;

export namespace PonyEngine::Resource
{
	class ResourceLoadHandler final : private IResourceLoadHandler
	{
	public:
		[[nodiscard("Pure constructor")]]
		ResourceLoadHandler(const std::shared_ptr<ResourceData>& resource, const std::shared_ptr<std::mutex>& resourceMutex,
			IResourceLoader& loader, const ResourceLoadContext& loadContext);
		ResourceLoadHandler(const ResourceLoadHandler&) = delete;
		ResourceLoadHandler(ResourceLoadHandler&&) = delete;

		~ResourceLoadHandler() noexcept;

		[[nodiscard("Pure function")]]
		bool IsTypeOf(std::span<const std::type_index> types) const noexcept;

		[[nodiscard("Pure function")]]
		RequestStatus Status() const noexcept;
		[[nodiscard("Pure function")]]
		std::shared_ptr<const void> Resource(std::type_index type) const;
		[[nodiscard("Pure function")]]
		const std::exception_ptr& Exception() const;

		void IncrementCancelCount() noexcept;
		void DecrementCancelCount();

		void Wait() const noexcept;

		void AddObserver(IResourceLoadObserver& observer) const;
		void RemoveObserver(IResourceLoadObserver& observer) const;

		ResourceLoadHandler& operator =(const ResourceLoadHandler&) = delete;
		ResourceLoadHandler& operator =(ResourceLoadHandler&&) = delete;

	private:
		virtual void SetSuccess(const std::shared_ptr<const void>& mainResource, std::span<const void* const> resources) override;
		virtual void SetFailure(const std::exception_ptr& exception) override;
		virtual void SetCancel() override;

		void Observe() noexcept;

		std::vector<std::type_index> outputTypes;
		std::shared_ptr<const void> mainResource;
		std::shared_ptr<ResourceData> resource;
		std::shared_ptr<std::mutex> resourceMutex;
		std::exception_ptr exception;
		std::atomic<RequestStatus> status;

		std::atomic_size_t cancelCount;

		std::shared_ptr<IResourceLoadRequest> loadRequest;

		mutable std::vector<IResourceLoadObserver*> observers;
		bool isObserverCalled;
		mutable std::mutex observerMutex;

		static_assert(std::atomic_size_t::is_always_lock_free, "std::size_t isn't lock-free.");
	};
}

namespace PonyEngine::Resource
{
	ResourceLoadHandler::ResourceLoadHandler(const std::shared_ptr<ResourceData>& resource, const std::shared_ptr<std::mutex>& resourceMutex, 
		IResourceLoader& loader, const ResourceLoadContext& loadContext) :
		outputTypes(loadContext.outputTypes.cbegin(), loadContext.outputTypes.cend()),
		resource(resource),
		resourceMutex(resourceMutex),
		status(RequestStatus::Pending),
		cancelCount(0uz),
		loadRequest(loader.Load(loadContext, *this)),
		isObserverCalled{false}
	{
	}

	ResourceLoadHandler::~ResourceLoadHandler() noexcept
	{
		loadRequest->ForgetHandler();
	}

	bool ResourceLoadHandler::IsTypeOf(const std::span<const std::type_index> types) const noexcept
	{
		for (const std::type_index type : types)
		{
			if (!std::ranges::contains(outputTypes, type))
			{
				return false;
			}
		}

		return true;
	}

	RequestStatus ResourceLoadHandler::Status() const noexcept
	{
		return status.load(std::memory_order::acquire);
	}

	std::shared_ptr<const void> ResourceLoadHandler::Resource(const std::type_index type) const
	{
		if (Status() != RequestStatus::Success)
		{
			throw std::logic_error("Invalid status");
		}

		for (std::size_t i = 0uz; i < outputTypes.size(); ++i)
		{
			if (outputTypes[i] == type)
			{
				return std::shared_ptr<const void>(mainResource, resource->Resources()[i]);
			}
		}

		throw std::invalid_argument("Invalid type");
	}

	const std::exception_ptr& ResourceLoadHandler::Exception() const
	{
		if (Status() != RequestStatus::Failure)
		{
			throw std::logic_error("Invalid status");
		}

		return exception;
	}

	void ResourceLoadHandler::IncrementCancelCount() noexcept
	{
		cancelCount.fetch_add(1uz, std::memory_order::relaxed);
	}

	void ResourceLoadHandler::DecrementCancelCount()
	{
		if (cancelCount.fetch_sub(1uz, std::memory_order::relaxed) == 1uz)
		{
			loadRequest->Cancel();
		}
	}

	void ResourceLoadHandler::Wait() const noexcept
	{
		while (status.load(std::memory_order::acquire) == RequestStatus::Pending)
		{
			status.wait(RequestStatus::Pending, std::memory_order::acquire);
		}
	}

	void ResourceLoadHandler::AddObserver(IResourceLoadObserver& observer) const
	{
		const auto lock = std::lock_guard(observerMutex);
		observers.push_back(&observer);

		if (isObserverCalled)
		{
			observer.OnStatusChanged();
		}
	}

	void ResourceLoadHandler::RemoveObserver(IResourceLoadObserver& observer) const
	{
		const auto lock = std::lock_guard(observerMutex);
		const auto position = std::ranges::find(observers, &observer);
		assert(position != observers.cend() && "Observer wasn't added.");
		observers.erase(position);
	}

	void ResourceLoadHandler::SetSuccess(const std::shared_ptr<const void>& mainResource, const std::span<const void* const> resources)
	{
		assert(status.load(std::memory_order::relaxed) == RequestStatus::Pending && "Invalid status");

		{
			const auto lock = std::lock_guard(*resourceMutex);
			resource->SetResource(mainResource, resources);
			this->mainResource = mainResource;
		}

		status.store(RequestStatus::Success, std::memory_order::release);

		Observe();
	}

	void ResourceLoadHandler::SetFailure(const std::exception_ptr& exception)
	{
		assert(status.load(std::memory_order::relaxed) == RequestStatus::Pending && "Invalid status");

		this->exception = exception;

		status.store(RequestStatus::Failure, std::memory_order::release);

		Observe();
	}

	void ResourceLoadHandler::SetCancel()
	{
		assert(status.load(std::memory_order::relaxed) == RequestStatus::Pending && "Invalid status");

		status.store(RequestStatus::Canceled, std::memory_order::release);

		Observe();
	}

	void ResourceLoadHandler::Observe() noexcept
	{
		const auto lock = std::lock_guard(observerMutex);

		for (IResourceLoadObserver* const observer : observers)
		{
			observer->OnStatusChanged();
		}

		isObserverCalled = true;
	}
}
