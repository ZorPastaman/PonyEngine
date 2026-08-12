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

export module PonyEngine.Resource.Impl:ResourceLoadRequest;

import std;

import PonyEngine.Log;
import PonyEngine.Resource.Ext;

import :IResourceLoadRequestObserver;
import :ResourceCache;

export namespace PonyEngine::Resource
{
	class ResourceLoadRequest final : private IResourceLoadRequest, private IResourceRequestObserver
	{
	public:
		[[nodiscard("Pure constructor")]]
		ResourceLoadRequest(Log::ILogService* logService, ResourceType resourceType, std::shared_ptr<void>&& resourceDataAccess, std::type_index resourceDataAccessType,
			std::span<const std::pair<std::shared_ptr<const void>, std::type_index>> loadData, std::vector<std::shared_ptr<IResourceRequest>>&& dependencies, 
			const std::shared_ptr<ResourceCache>& cache, IResourceLoader& loader);
		ResourceLoadRequest(const ResourceLoadRequest&) = delete;
		ResourceLoadRequest(ResourceLoadRequest&&) = delete;

		~ResourceLoadRequest() noexcept;

		[[nodiscard("Pure function")]] 
		RequestStatus Status() const noexcept;
		[[nodiscard("Pure function")]] 
		const std::shared_ptr<const ResourceCache>& Cache() const;
		[[nodiscard("Pure function")]] 
		const std::exception_ptr& Exception() const;

		bool IncrementRequiredCancelCount() noexcept;
		void Cancel();

		void Wait() const noexcept;

		void AddObserver(IResourceLoadRequestObserver& observer);
		void RemoveObserver(IResourceLoadRequestObserver& observer);

		ResourceLoadRequest& operator =(const ResourceLoadRequest&) = delete;
		ResourceLoadRequest& operator =(ResourceLoadRequest&&) = delete;

	private:
		virtual void SetSuccess(const std::shared_ptr<const void>& mainResource, std::span<const std::pair<const void*, std::type_index>> resources) override;
		virtual void SetFailure(const std::exception_ptr& exception) override;

		virtual void OnStatusChanged(ResourceID resourceId) noexcept override;

		void OnFinished() noexcept;

		Log::ILogService* logService;

		std::vector<std::shared_ptr<IResourceRequest>> dependencies; ///< Resource dependencies. May be not loaded.

		std::shared_ptr<ResourceCache> cache;
		std::shared_ptr<const void> mainResource;
		std::exception_ptr exception;
		std::atomic<RequestStatus> status;
		std::size_t requiredCancelCount;
		std::size_t cancelCount;
		std::mutex stateMutex;

		std::vector<IResourceLoadRequestObserver*> observers;
		bool observerCalled;
		std::mutex observerMutex;

		std::shared_ptr<IResourceLoadProcess> loadProcess;

		static_assert(std::atomic<RequestStatus>::is_always_lock_free, "std::atomic<RequestStatus> is not lock-free.");
	};
}

namespace PonyEngine::Resource
{
	ResourceLoadRequest::ResourceLoadRequest(Log::ILogService* const logService, const ResourceType resourceType, std::shared_ptr<void>&& resourceDataAccess, const std::type_index resourceDataAccessType,
		const std::span<const std::pair<std::shared_ptr<const void>, std::type_index>> loadData, std::vector<std::shared_ptr<IResourceRequest>>&& dependencies, 
		const std::shared_ptr<ResourceCache>& cache, IResourceLoader& loader) :
		logService{logService},
		dependencies(std::move(dependencies)),
		cache(cache),
		status(RequestStatus::Pending),
		requiredCancelCount{1uz},
		cancelCount{0uz},
		observerCalled{false}
	{
		std::vector<std::shared_ptr<const IResourceRequest>> constDependencies;
		constDependencies.reserve(this->dependencies.size());
		for (const std::shared_ptr<IResourceRequest>& dependency : this->dependencies)
		{
			constDependencies.push_back(dependency);
		}

		const auto context = ResourceLoadContext
		{
			.resourceType = resourceType,
			.resourceDataAccess = std::move(resourceDataAccess),
			.resourceDataAccessType = resourceDataAccessType,
			.loadData = loadData,
			.dependencies = constDependencies,
			.outputTypes = this->cache->OutputTypes()
		};
		loadProcess = loader.Load(context, *this);
		assert(loadProcess && "Load process is nullptr.");

		for (const std::shared_ptr<IResourceRequest>& dependency : this->dependencies)
		{
			dependency->AddObserver(*this);
		}
	}

	ResourceLoadRequest::~ResourceLoadRequest() noexcept
	{
		assert(observers.empty() && "Observers weren't removed.");

		for (const std::shared_ptr<IResourceRequest>& dependency : this->dependencies)
		{
			dependency->RemoveObserver(*this);
		}
	}

	RequestStatus ResourceLoadRequest::Status() const noexcept
	{
		return status.load(std::memory_order::acquire);
	}

	const std::shared_ptr<const ResourceCache>& ResourceLoadRequest::Cache() const
	{
		if (Status() != RequestStatus::Success) [[unlikely]]
		{
			throw std::logic_error("Invalid status");
		}

		return cache;
	}

	const std::exception_ptr& ResourceLoadRequest::Exception() const
	{
		if (Status() != RequestStatus::Failure) [[unlikely]]
		{
			throw std::logic_error("Invalid status");
		}

		return exception;
	}

	bool ResourceLoadRequest::IncrementRequiredCancelCount() noexcept
	{
		const auto lock = std::lock_guard(stateMutex);

		if (status.load(std::memory_order::relaxed) != RequestStatus::Pending)
		{
			return false;
		}

		++requiredCancelCount;
		return true;
	}

	void ResourceLoadRequest::Cancel()
	{
		const auto lock = std::lock_guard(stateMutex);

		if (Status() == RequestStatus::Pending)
		{
			++cancelCount;
			if (cancelCount >= requiredCancelCount)
			{
				status.store(RequestStatus::Canceled, std::memory_order::release);

				try
				{
					loadProcess->OnCancel();
				}
				catch (...)
				{
					PONY_LOG(logService, Log::LogType::Error, std::current_exception(), "On canceling load process.");
				}

				for (const std::shared_ptr<IResourceRequest>& dependency : dependencies)
				{
					try
					{
						dependency->Cancel();
					}
					catch (...)
					{
						PONY_LOG(logService, Log::LogType::Error, std::current_exception(), "On canceling load request dependency.");
					}
				}

				OnFinished();
			}
		}
	}

	void ResourceLoadRequest::Wait() const noexcept
	{
		while (status.load(std::memory_order::acquire) == RequestStatus::Pending)
		{
			status.wait(RequestStatus::Pending, std::memory_order::acquire);
		}
	}

	void ResourceLoadRequest::AddObserver(IResourceLoadRequestObserver& observer)
	{
		const auto lock = std::lock_guard(observerMutex);
		observers.push_back(&observer);

		if (observerCalled)
		{
			observer.OnStatusChanged();
		}
	}

	void ResourceLoadRequest::RemoveObserver(IResourceLoadRequestObserver& observer)
	{
		const auto lock = std::lock_guard(observerMutex);
		if (const auto position = std::ranges::find(observers, &observer); position != observers.cend())
		{
			observers.erase(position);
		}

		assert(false && "Observer not found");
	}

	void ResourceLoadRequest::SetSuccess(const std::shared_ptr<const void>& mainResource, const std::span<const std::pair<const void*, std::type_index>> resources)
	{
		const auto lock = std::lock_guard(stateMutex);

		if (status.load(std::memory_order::relaxed) != RequestStatus::Pending)
		{
			return;
		}

		cache->Set(mainResource, resources);
		this->mainResource = mainResource;

		status.store(RequestStatus::Success, std::memory_order::release);
		OnFinished();
	}

	void ResourceLoadRequest::SetFailure(const std::exception_ptr& exception)
	{
		const auto lock = std::lock_guard(stateMutex);

		if (status.load(std::memory_order::relaxed) != RequestStatus::Pending)
		{
			return;
		}

		this->exception = exception;
		status.store(RequestStatus::Failure, std::memory_order::release);
		OnFinished();
	}

	void ResourceLoadRequest::OnStatusChanged(const ResourceID resourceId) noexcept
	{
		for (std::size_t i = 0uz; i < dependencies.size(); ++i)
		{
			const std::shared_ptr<const IResourceRequest>& dependency = dependencies[i];
			if (dependency->ResourceID() == resourceId)
			{
				const RequestStatus dependencyStatus = dependency->Status();
				try
				{
					if (dependencyStatus == RequestStatus::Success)
					{
						loadProcess->OnDependencySuccess(i);
					}
					else if (dependencyStatus == RequestStatus::Failure)
					{
						loadProcess->OnDependencyFailure(i);
					}
				}
				catch (...)
				{
					PONY_LOG(logService, Log::LogType::Error, std::current_exception(), "On updating load request dependency.");
				}

				break;
			}
		}
	}

	void ResourceLoadRequest::OnFinished() noexcept
	{
		const auto lock = std::lock_guard(observerMutex);

		for (IResourceLoadRequestObserver* const observer : observers)
		{
			try
			{
				observer->OnStatusChanged();
			}
			catch (...)
			{
				PONY_LOG(logService, Log::LogType::Error, std::current_exception(), "On sending on status changed to resource load request observer. Observer: '{}'.",
					typeid(*observer).name());
			}
		}

		observerCalled = true;
	}
}
