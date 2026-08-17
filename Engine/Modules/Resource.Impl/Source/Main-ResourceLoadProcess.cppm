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

export module PonyEngine.Resource.Impl:ResourceLoadProcess;

import std;

import PonyEngine.Resource.Ext;

import :ResourceData;
import :ResourceInfo;
import :ResourceRequestResult;
import :Utility;

export namespace PonyEngine::Resource
{
	/// @brief Resource request that is attached to an actual load process.
	class LoadedResourceRequest;

	/// @brief Resource load process.
	class ResourceLoadProcess final : private IResourceLoadHandler
	{
	public:
		/// @brief Creates a resource load process.
		/// @param resourceInfo Resource info.
		/// @param resourceData Resource data.
		/// @param resourceMutex Resource mutex.
		/// @param resourceDataAccess Resource data access. Must be of a chosen type.
		/// @param loader Loader.
		[[nodiscard("Pure constructor")]]
		ResourceLoadProcess(const std::shared_ptr<const ResourceInfo>& resourceInfo, const std::shared_ptr<ResourceData>& resourceData,
			const std::shared_ptr<std::mutex>& resourceMutex, std::shared_ptr<void>&& resourceDataAccess, IResourceLoader& loader);
		ResourceLoadProcess(const ResourceLoadProcess&) = delete;
		ResourceLoadProcess(ResourceLoadProcess&&) = delete;

		~ResourceLoadProcess() noexcept;

		/// @brief Gets the resource ID.
		/// @return Resource ID.
		[[nodiscard("Pure function")]]
		struct ResourceID ResourceID() const noexcept;
		/// @brief Checks if the output type of the resource contains the @p types.
		/// @param types Types to check against.
		/// @return @a True if the resource is of type @p types; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsTypeOf(std::span<const std::type_index> types) const noexcept;

		/// @brief Gets the request status.
		/// @return Request status.
		[[nodiscard("Pure function")]]
		RequestStatus Status() const noexcept;
		/// @brief Gets the request result.
		/// @return Request result.
		/// @note It's valid to call only if the status is success.
		[[nodiscard("Pure function")]]
		const std::shared_ptr<const ResourceRequestResult>& Result() const;
		/// @brief Gets the exception.
		/// @return Exception.
		/// @note It's valid to call only if the status is failure.
		[[nodiscard("Pure function")]]
		const std::exception_ptr& Exception() const;

		/// @brief Increments the cancel count if it's greater than 0.
		/// @return @a True if the process is still valid; @a false otherwise.
		bool IncrementCancelCount() noexcept;
		/// @brief Decrements the cancel count.
		/// @details If the cancel count reaches 0, it calls a cancel function.
		void DecrementCancelCount();

		/// @brief Adds the request observer.
		/// @param request Request observer.
		void AddObserver(const LoadedResourceRequest& request) const;
		/// @brief Removes the request observer.
		/// @param request Request observer.
		void RemoveObserver(const LoadedResourceRequest& request) const;

		/// @brief Waits till the process is finished.
		void Wait() const noexcept;

		ResourceLoadProcess& operator =(const ResourceLoadProcess&) = delete;
		ResourceLoadProcess& operator =(ResourceLoadProcess&&) = delete;

	private:
		/// @brief Sets success.
		/// @param mainResource Main resource.
		/// @param resources Output resources.
		virtual void SetSuccess(const std::shared_ptr<const void>& mainResource, std::span<const void* const> resources) override;
		/// @brief Sets failure.
		/// @param exception Exception.
		virtual void SetFailure(const std::exception_ptr& exception) override;

		std::shared_ptr<const ResourceInfo> resourceInfo; ///< Resource info.
		std::shared_ptr<ResourceData> resourceData; ///< Resource data.
		std::shared_ptr<std::mutex> resourceMutex; ///< Resource mutex.

		std::shared_ptr<const ResourceRequestResult> result; ///< Result.
		std::exception_ptr exception; ///< Exception.
		std::atomic<RequestStatus> status; ///< Process status.
		std::atomic_size_t cancelCount; ///< Cancel count.

		std::shared_ptr<IResourceLoadRequest> request; ///< Load request.

		mutable std::vector<const LoadedResourceRequest*> observers; ///< Observers.
		bool observersCalled; ///< Were the observers called?
		mutable std::mutex observerMutex; ///< Observer mutex.

		static_assert(std::atomic<RequestStatus>::is_always_lock_free, "RequestStatus isn't lock-free.");
		static_assert(std::atomic_size_t::is_always_lock_free, "std::size_t isn't lock-free.");
	};

	/// @brief Resource request that is attached to an actual load process.
	class LoadedResourceRequest final : public IResourceRequest
	{
	public:
		/// @brief Creates a loaded resource request.
		/// @param process Load process.
		/// @param observer Observer.
		[[nodiscard("Pure constructor")]]
		explicit LoadedResourceRequest(const std::shared_ptr<ResourceLoadProcess>& process, IResourceRequestObserver* observer);
		LoadedResourceRequest(const LoadedResourceRequest&) = delete;
		LoadedResourceRequest(LoadedResourceRequest&&) = delete;

		~LoadedResourceRequest() noexcept;

		[[nodiscard("Pure function")]] 
		virtual struct ResourceID ResourceID() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual bool IsTypeOf(std::span<const std::type_index> types) const noexcept override;

		[[nodiscard("Pure function")]] 
		virtual RequestStatus Status() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual std::shared_ptr<const IResourceRequestResult> Result() const override;
		[[nodiscard("Pure function")]] 
		virtual const std::exception_ptr& Exception() const override;

		virtual void Cancel() override;

		virtual void Wait() const noexcept override;

		LoadedResourceRequest& operator =(const LoadedResourceRequest&) = delete;
		LoadedResourceRequest& operator =(LoadedResourceRequest&&) = delete;

	private:
		/// @brief Invoked on success.
		void OnSuccess() const noexcept;
		/// @brief Invoked on failure.
		void OnFailure() const noexcept;
		/// @brief Invoked on canceled.
		void OnCanceled() const noexcept;

		std::shared_ptr<ResourceLoadProcess> process; ///< Load process.
		IResourceRequestObserver* observer; ///< Request observer.

		std::atomic_bool canceled; ///< Is this request canceled?

		friend ResourceLoadProcess;

		static_assert(std::atomic_bool::is_always_lock_free, "bool isn't lock-free.");
	};
}

namespace PonyEngine::Resource
{
	ResourceLoadProcess::ResourceLoadProcess(const std::shared_ptr<const ResourceInfo>& resourceInfo, const std::shared_ptr<ResourceData>& resourceData,
		const std::shared_ptr<std::mutex>& resourceMutex, std::shared_ptr<void>&& resourceDataAccess, IResourceLoader& loader) :
		resourceInfo(resourceInfo),
		resourceData(resourceData),
		resourceMutex(resourceMutex),
		status(RequestStatus::Pending),
		cancelCount(1uz),
		observersCalled{false}
	{
		assert(this->resourceInfo && "Resource info is nullptr.");
		assert(this->resourceData && "Resource data is nullptr.");
		assert(resourceDataAccess && "Resource data access is nullptr.");

		request = loader.Load(ResourceLoadContext
		{
			.resourceType = this->resourceInfo->type,
			.resourceDataAccess = std::move(resourceDataAccess),
			.resourceDataAccessType = this->resourceInfo->dataAccessType,
			.loadData = this->resourceInfo->loadData,
			.outputTypes = this->resourceInfo->outputTypes
		}, *this);
	}

	ResourceLoadProcess::~ResourceLoadProcess() noexcept
	{
		assert(observers.empty() && "Some observers weren't removed.");
		request->Stop();
	}

	struct ResourceID ResourceLoadProcess::ResourceID() const noexcept
	{
		return resourceInfo->id;
	}

	bool ResourceLoadProcess::IsTypeOf(const std::span<const std::type_index> types) const noexcept
	{
		return CheckTypes(types, resourceInfo->outputTypes);
	}

	RequestStatus ResourceLoadProcess::Status() const noexcept
	{
		return status.load(std::memory_order::acquire);
	}

	const std::shared_ptr<const ResourceRequestResult>& ResourceLoadProcess::Result() const
	{
		if (status.load(std::memory_order::acquire) != RequestStatus::Success)
		{
			throw std::logic_error("Invalid status");
		}

		return result;
	}

	const std::exception_ptr& ResourceLoadProcess::Exception() const
	{
		if (status.load(std::memory_order::acquire) != RequestStatus::Failure)
		{
			throw std::logic_error("Invalid status");
		}

		return exception;
	}

	bool ResourceLoadProcess::IncrementCancelCount() noexcept
	{
		std::size_t currentCancelCount = cancelCount.load(std::memory_order::relaxed);
		while (currentCancelCount != 0uz && !cancelCount.compare_exchange_weak(currentCancelCount, currentCancelCount + 1uz, std::memory_order::relaxed))
		{
		}

		return currentCancelCount != 0uz;
	}

	void ResourceLoadProcess::DecrementCancelCount()
	{
		if (cancelCount.fetch_sub(1uz, std::memory_order::relaxed) != 1uz)
		{
			return;
		}

		assert(status.load(std::memory_order::acquire) == RequestStatus::Pending && "Invalid status.");

		request->Stop();
		
		status.store(RequestStatus::Canceled, std::memory_order::release);
		status.notify_all();

		const auto observerLock = std::lock_guard(observerMutex);
		for (const LoadedResourceRequest* request : observers)
		{
			request->OnCanceled();
		}
		observersCalled = true;
	}

	void ResourceLoadProcess::AddObserver(const LoadedResourceRequest& request) const
	{
		const auto lock = std::lock_guard(observerMutex);
		observers.push_back(&request);

		if (observersCalled)
		{
			switch (Status())
			{
			case RequestStatus::Success:
				request.OnSuccess();
				break;
			case RequestStatus::Failure:
				request.OnFailure();
				break;
			case RequestStatus::Canceled:
				request.OnCanceled();
				break;
			default: 
				break;
			}
		}
	}

	void ResourceLoadProcess::RemoveObserver(const LoadedResourceRequest& request) const
	{
		const auto lock = std::lock_guard(observerMutex);
		const auto position = std::ranges::find(observers, &request);
		assert(position != observers.cend() && "Observer not found.");
		observers.erase(position);
	}

	void ResourceLoadProcess::Wait() const noexcept
	{
		while (status.load(std::memory_order::acquire) == RequestStatus::Pending)
		{
			status.wait(RequestStatus::Pending, std::memory_order::acquire);
		}
	}

	void ResourceLoadProcess::SetSuccess(const std::shared_ptr<const void>& mainResource, const std::span<const void* const> resources)
	{
		if (!IncrementCancelCount())
		{
			return;
		}

		assert(status.load(std::memory_order::acquire) == RequestStatus::Pending && "Invalid status.");

		{
			const auto resourceLock = std::lock_guard(*resourceMutex);
			resourceData->SetResource(mainResource, resources);
		}
		result = std::make_shared<ResourceRequestResult>(resourceInfo, resourceData, mainResource);
		
		status.store(RequestStatus::Success, std::memory_order::release);
		status.notify_all();

		const auto observerLock = std::lock_guard(observerMutex);
		for (const LoadedResourceRequest* request : observers)
		{
			request->OnSuccess();
		}
		observersCalled = true;
	}

	void ResourceLoadProcess::SetFailure(const std::exception_ptr& exception)
	{
		if (!IncrementCancelCount())
		{
			return;
		}

		assert(status.load(std::memory_order::acquire) == RequestStatus::Pending && "Invalid status.");

		this->exception = exception;

		status.store(RequestStatus::Failure, std::memory_order::release);
		status.notify_all();

		const auto observerLock = std::lock_guard(observerMutex);
		for (const LoadedResourceRequest* request : observers)
		{
			request->OnFailure();
		}
		observersCalled = true;
	}

	LoadedResourceRequest::LoadedResourceRequest(const std::shared_ptr<ResourceLoadProcess>& process, IResourceRequestObserver* const observer) :
		process(process),
		observer{observer},
		canceled(false)
	{
		if (this->observer)
		{
			process->AddObserver(*this);
		}
	}

	LoadedResourceRequest::~LoadedResourceRequest() noexcept
	{
		if (observer)
		{
			process->RemoveObserver(*this);
		}
	}

	struct ResourceID LoadedResourceRequest::ResourceID() const noexcept
	{
		return process->ResourceID();
	}

	bool LoadedResourceRequest::IsTypeOf(const std::span<const std::type_index> types) const noexcept
	{
		return process->IsTypeOf(types);
	}

	RequestStatus LoadedResourceRequest::Status() const noexcept
	{
		return process->Status();
	}

	std::shared_ptr<const IResourceRequestResult> LoadedResourceRequest::Result() const
	{
		return process->Result();
	}

	const std::exception_ptr& LoadedResourceRequest::Exception() const
	{
		return process->Exception();
	}

	void LoadedResourceRequest::Cancel()
	{
		if (!canceled.exchange(true))
		{
			process->DecrementCancelCount();
		}
	}

	void LoadedResourceRequest::Wait() const noexcept
	{
		process->Wait();
	}

	void LoadedResourceRequest::OnSuccess() const noexcept
	{
		observer->OnSuccess(process->Result());
	}

	void LoadedResourceRequest::OnFailure() const noexcept
	{
		observer->OnFailure(process->Exception());
	}

	void LoadedResourceRequest::OnCanceled() const noexcept
	{
		observer->OnCancel();
	}
}
