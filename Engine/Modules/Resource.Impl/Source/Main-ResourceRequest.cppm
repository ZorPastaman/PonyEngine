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

#include "PonyEngine/Log/Log.h"

export module PonyEngine.Resource.Impl:ResourceRequest;

import std;

import PonyEngine.Log;
import PonyEngine.Resource.Ext;

import :Resource;

export namespace PonyEngine::Resource
{
	class ResourceRequest final : public IResourceRequest, private IResourceLoadRequest
	{
	public:
		[[nodiscard("Pure constructor")]]
		ResourceRequest(const Log::ILogService* logService, const struct Resource& resource, std::shared_ptr<void>&& resourceDataAccess,
			std::vector<std::shared_ptr<const IResourceRequest>>&& dependencies, IResourceLoader& loader);
		ResourceRequest(const ResourceRequest&) = delete;
		ResourceRequest(ResourceRequest&&) = delete;

		~ResourceRequest() noexcept;

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

		virtual void AddObserver(IResourceRequestObserver& observer) override;
		virtual void RemoveObserver(IResourceRequestObserver& observer) override;

		ResourceRequest& operator =(const ResourceRequest&) = delete;
		ResourceRequest& operator =(ResourceRequest&&) = delete;

	private:
		virtual void SetSuccess(const std::shared_ptr<const void>& mainResource, std::span<const std::pair<const void*, std::type_index>> resources) override;
		virtual void SetFailure(const std::exception_ptr& exception) override;
		virtual void SetCanceled() override;

		void OnFinished() const noexcept;

		const Log::ILogService* logService;

		struct ResourceID resourceId;
		ResourceType resourceType; ///< Resource type.
		std::shared_ptr<void> resourceDataAccess; ///< Resource data access.
		std::type_index resourceDataAccessType; ///< Resource data access type.
		std::vector<std::pair<std::shared_ptr<const void>, std::type_index>> loadData; ///< Resource load data.
		std::vector<std::shared_ptr<const IResourceRequest>> dependencies; ///< Resource dependencies. May be not loaded.
		std::vector<std::type_index> outputTypes; ///< Resource output types.

		std::shared_ptr<const void> mainResource;
		std::vector<const void*> resources;
		std::exception_ptr exception;
		std::atomic<RequestStatus> status;

		std::vector<IResourceRequestObserver*> observers;
		mutable bool observerCalled;
		mutable std::mutex observerMutex;

		std::shared_ptr<IResourceLoadProcess> loadProcess;

		static_assert(std::atomic<RequestStatus>::is_always_lock_free, "std::atomic<RequestStatus> is not lock-free.");
	};
}

namespace PonyEngine::Resource
{
	ResourceRequest::ResourceRequest(const Log::ILogService* const logService, const struct Resource& resource, std::shared_ptr<void>&& resourceDataAccess,
		std::vector<std::shared_ptr<const IResourceRequest>>&& dependencies, IResourceLoader& loader) :
		logService{logService},
		resourceId(resource.id),
		resourceType(resource.type),
		resourceDataAccess(std::move(resourceDataAccess)),
		resourceDataAccessType(resource.dataAccessType),
		loadData(resource.loadData),
		dependencies(std::move(dependencies)),
		outputTypes(resource.outputTypes),
		resources(outputTypes.size()),
		status(RequestStatus::Pending),
		observerCalled{false}
	{
		const auto context = ResourceLoadContext
		{
			.resourceType = this->resourceType,
			.resourceDataAccess = this->resourceDataAccess,
			.resourceDataAccessType = this->resourceDataAccessType,
			.loadData = this->loadData,
			.dependencies = this->dependencies,
			.outputTypes = this->outputTypes
		};
		loadProcess = loader.Load(context, *this);
		assert(loadProcess && "Load process is nullptr.");
	}

	struct ResourceID ResourceRequest::ResourceID() const noexcept
	{
		return resourceId;
	}

	ResourceRequest::~ResourceRequest() noexcept
	{
		assert(observers.empty() && "Observers weren't removed.");
	}

	bool ResourceRequest::IsTypeOf(const std::span<const std::type_index> types) const noexcept
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

	RequestStatus ResourceRequest::Status() const noexcept
	{
		return status.load(std::memory_order::acquire);
	}

	std::shared_ptr<const void> ResourceRequest::Resource(const std::type_index type) const
	{
		if (status.load(std::memory_order::acquire) != RequestStatus::Success) [[unlikely]]
		{
			throw std::logic_error("Invalid status");
		}

		for (std::size_t i = 0uz; i < outputTypes.size(); ++i)
		{
			if (outputTypes[i] == type)
			{
				return std::shared_ptr<const void>(mainResource, resources[i]);
			}
		}

		throw std::invalid_argument("Invalid type");
	}

	const std::exception_ptr& ResourceRequest::Exception() const
	{
		if (status.load(std::memory_order::acquire) != RequestStatus::Failure) [[unlikely]]
		{
			throw std::logic_error("Invalid status");
		}

		return exception;
	}

	void ResourceRequest::Cancel()
	{
		if (status.load(std::memory_order::relaxed) == RequestStatus::Pending)
		{
			loadProcess->OnCancel();
		}
	}

	void ResourceRequest::Wait() const noexcept
	{
		while (status.load(std::memory_order::acquire) == RequestStatus::Pending)
		{
			status.wait(RequestStatus::Pending, std::memory_order::acquire);
		}
	}

	void ResourceRequest::AddObserver(IResourceRequestObserver& observer)
	{
		const auto lock = std::lock_guard(observerMutex);
		observers.push_back(&observer);

		if (observerCalled)
		{
			observer.OnStatusChanged(resourceId);
		}
	}

	void ResourceRequest::RemoveObserver(IResourceRequestObserver& observer)
	{
		const auto lock = std::lock_guard(observerMutex);
		if (const auto position = std::ranges::find(observers, &observer); position != observers.cend())
		{
			observers.erase(position);
		}

		assert(false && "Observer not found");
	}

	void ResourceRequest::SetSuccess(const std::shared_ptr<const void>& mainResource, const std::span<const std::pair<const void*, std::type_index>> resources)
	{
		assert(status.load(std::memory_order::relaxed) == RequestStatus::Pending && "Invalid status");

		assert(mainResource && "Main resource is nullptr.");
		this->mainResource = mainResource;

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

		status.store(RequestStatus::Success, std::memory_order::release);
		OnFinished();
	}

	void ResourceRequest::SetFailure(const std::exception_ptr& exception)
	{
		assert(status.load(std::memory_order::relaxed) == RequestStatus::Pending && "Invalid status");
		this->exception = exception;
		status.store(RequestStatus::Failure, std::memory_order::release);
		OnFinished();
	}

	void ResourceRequest::SetCanceled()
	{
		assert(status.load(std::memory_order::relaxed) == RequestStatus::Pending && "Invalid status");
		status.store(RequestStatus::Canceled, std::memory_order::release);
		OnFinished();
	}

	void ResourceRequest::OnFinished() const noexcept
	{
		const auto lock = std::lock_guard(observerMutex);

		for (IResourceRequestObserver* const observer : observers)
		{
			try
			{
				observer->OnStatusChanged(resourceId);
			}
			catch (...)
			{
				PONY_LOG(logService, Log::LogType::Error, std::current_exception(), "On resource request observer on status changed. Observer: '{}'.", typeid(*observer).name());
			}
		}

		observerCalled = true;
	}
}
