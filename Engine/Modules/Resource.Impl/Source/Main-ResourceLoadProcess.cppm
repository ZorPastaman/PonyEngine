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

import PonyEngine.Async;
import PonyEngine.Resource.Ext;

import :Resource;
import :Utility;

export namespace PonyEngine::Resource
{
	/// @brief Resource request that is used when a resource isn't alive.
	class OngoingResourceRequest;

	/// @brief Resource load process.
	class ResourceLoadProcess final : public ILoadContext
	{
	public:
		/// @brief Creates a resource load process.
		/// @param resource Resource load process.
		/// @param resourceDataAccess Resource data access. Must be of a valid type declared in the @p resource.
		[[nodiscard("Pure constructor")]]
		ResourceLoadProcess(std::shared_ptr<class Resource> resource, std::shared_ptr<void> resourceDataAccess);
		ResourceLoadProcess(const ResourceLoadProcess&) = delete;
		ResourceLoadProcess(ResourceLoadProcess&&) = delete;

		~ResourceLoadProcess() noexcept = default;

		[[nodiscard("Pure function")]] 
		virtual void* ResourceDataAccess() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual std::type_index ResourceDataAccessType() const noexcept override;

		[[nodiscard("Pure function")]] 
		virtual struct ResourceType ResourceType() const noexcept override;

		[[nodiscard("Pure function")]] 
		virtual std::size_t LoadDataCount() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual const void* LoadData(std::size_t index) const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual std::type_index LoadDataType(std::size_t index) const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual std::span<const std::type_index> InterfaceTypes() const noexcept override;

		/// @brief Gets the resource.
		/// @return Resource.
		[[nodiscard("Pure function")]]
		const Resource* Resource() const noexcept;

		/// @brief Gets the resource ID.
		/// @return Resource ID.
		[[nodiscard("Pure function")]]
		struct ResourceID ResourceID() const noexcept;
		/// @brief Checks if the resource has interfaces.
		/// @param types Interfaces to check.
		/// @return @a True if it has all the required interfaces; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool HasInterfaces(std::span<const std::type_index> types) const noexcept;

		/// @brief Gets the status.
		/// @return Status.
		[[nodiscard("Pure function")]]
		Async::RequestStatus Status() const noexcept;
		/// @brief Gets a resource interface.
		/// @param type Resource interface type. Must be one of the resource interfaces.
		/// @return Resource interface.
		/// @note It's valid to call only if the status is success.
		[[nodiscard("Pure function")]]
		std::shared_ptr<const void> Resource(std::type_index type) const;
		/// @brief Gets an exception.
		/// @return Exception.
		/// @note It's valid to call only if the status is failure.
		[[nodiscard("Pure function")]]
		const std::exception_ptr& Exception() const;

		/// @brief Tries to increment the cancel count.
		/// @details If the cancel count is already 0, it will do nothing.
		/// @return @a True if the cancel count is incremented; @a false otherwise.
		[[nodiscard("Must be used")]]
		bool IncrementCancelCount() noexcept;
		/// @brief Decrements the cancel count.
		/// @details If it reaches 0, the load request will be canceled.
		void DecrementCancelCount() noexcept;

		/// @brief Waits till the process is finished.
		void Wait() const noexcept;

		/// @brief Adds the request callback.
		/// @param request Request callback to add.
		void AddRequest(OngoingResourceRequest& request);
		/// @brief Removes the request callback.
		/// @param request Request callback to remove.
		void RemoveRequest(OngoingResourceRequest& request);

		/// @brief Sets the load request.
		/// @param loadRequest Load request.
		void SetLoadRequest(std::shared_ptr<IResourceLoadRequest> loadRequest) noexcept;

		/// @brief Sets success.
		/// @param mainResource Main resource. Must be alive.
		/// @param resourceInterfaces Resource interfaces. Must be synced with resource interface types by index.
		void SetSuccess(std::shared_ptr<const void> mainResource, std::span<const void* const> resourceInterfaces) noexcept;
		/// @brief Sets failure.
		/// @param exception Exception.
		void SetFailure(std::exception_ptr exception);
		/// @brief Sets canceled.
		void SetCanceled();

		ResourceLoadProcess& operator =(const ResourceLoadProcess&) = delete;
		ResourceLoadProcess& operator =(ResourceLoadProcess&&) = delete;

	private:
		/// @brief Invokes callback.
		void InvokeCallback() noexcept;

		std::shared_ptr<class Resource> resource; ///< Resource.
		std::shared_ptr<void> resourceDataAccess; ///< Resource data access.

		std::shared_ptr<const void> mainResource; ///< Main resource.
		std::exception_ptr exception; ///< Exception.
		std::atomic<Async::RequestStatus> status; ///< Status.
		std::atomic_size_t cancelCount; ///< Cancel count.
		
		std::shared_ptr<IResourceLoadRequest> loadRequest; ///< Load request.

		std::vector<OngoingResourceRequest*> requests; ///< Request callbacks.
		bool finished; ///< Were the @p requests called?
		std::mutex requestMutex; ///< Request callback mutex.

		static_assert(std::atomic<Async::RequestStatus>::is_always_lock_free, "RequestStatus isn't lock-free.");
		static_assert(std::atomic_size_t::is_always_lock_free, "std::size_t isn't lock-free.");
	};

	/// @brief Resource request that is used when a resource isn't alive.
	class OngoingResourceRequest final : public IResourceRequest
	{
	public:
		/// @brief Creates an ongoing resource load request.
		/// @param loadProcess Load process. Must be alive.
		/// @param callback Callback. Can be nullptr.
		[[nodiscard("Pure constructor")]]
		OngoingResourceRequest(std::shared_ptr<ResourceLoadProcess> loadProcess, std::move_only_function<void(const IResourceRequest&) noexcept> callback) noexcept;
		OngoingResourceRequest(const OngoingResourceRequest&) = delete;
		OngoingResourceRequest(OngoingResourceRequest&&) = delete;

		~OngoingResourceRequest() noexcept;

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

		/// @brief Called on load process status change.
		void OnStatusChanged() noexcept;

		OngoingResourceRequest& operator =(const OngoingResourceRequest&) = delete;
		OngoingResourceRequest& operator =(OngoingResourceRequest&&) = delete;

	private:
		std::shared_ptr<ResourceLoadProcess> loadProcess; ///< Load process.
		std::atomic_bool canceled; ///< Is the request canceled?

		std::move_only_function<void(const IResourceRequest&) noexcept> callback; ///< Callback.

		static_assert(std::atomic_bool::is_always_lock_free, "bool isn't lock-free.");
	};
}

namespace PonyEngine::Resource
{
	ResourceLoadProcess::ResourceLoadProcess(std::shared_ptr<class Resource> resource, std::shared_ptr<void> resourceDataAccess) :
		resource(std::move(resource)),
		resourceDataAccess(std::move(resourceDataAccess)),
		status(Async::RequestStatus::Pending),
		cancelCount(1uz),
		finished{false}
	{
		assert(this->resource && "Resource is nullptr.");
		assert(this->resourceDataAccess && "Resource data access is nullptr.");
	}

	void* ResourceLoadProcess::ResourceDataAccess() const noexcept
	{
		return resourceDataAccess.get();
	}

	std::type_index ResourceLoadProcess::ResourceDataAccessType() const noexcept
	{
		return resource->DataAccessType();
	}

	struct ResourceType ResourceLoadProcess::ResourceType() const noexcept
	{
		return resource->Type();
	}

	std::size_t ResourceLoadProcess::LoadDataCount() const noexcept
	{
		return resource->LoadData().size();
	}

	const void* ResourceLoadProcess::LoadData(const std::size_t index) const noexcept
	{
		return resource->LoadData()[index].first.get();
	}

	std::type_index ResourceLoadProcess::LoadDataType(const std::size_t index) const noexcept
	{
		return resource->LoadData()[index].second;
	}

	std::span<const std::type_index> ResourceLoadProcess::InterfaceTypes() const noexcept
	{
		return resource->InterfaceTypes();
	}

	const Resource* ResourceLoadProcess::Resource() const noexcept
	{
		return resource.get();
	}

	struct ResourceID ResourceLoadProcess::ResourceID() const noexcept
	{
		return resource->ID();
	}

	bool ResourceLoadProcess::HasInterfaces(const std::span<const std::type_index> types) const noexcept
	{
		return CheckTypes(types, resource->InterfaceTypes());
	}

	Async::RequestStatus ResourceLoadProcess::Status() const noexcept
	{
		return status.load(std::memory_order::acquire);
	}

	std::shared_ptr<const void> ResourceLoadProcess::Resource(const std::type_index type) const
	{
		if (status.load(std::memory_order::acquire) != Async::RequestStatus::Success)
		{
			throw std::logic_error("Invalid status");
		}

		return MakeResource(type, resource->InterfaceTypes(), resource->ResourceInterfaces(), mainResource);
	}

	const std::exception_ptr& ResourceLoadProcess::Exception() const
	{
		if (status.load(std::memory_order::acquire) != Async::RequestStatus::Failure)
		{
			throw std::logic_error("Invalid status");
		}

		return exception;
	}

	bool ResourceLoadProcess::IncrementCancelCount() noexcept
	{
		std::size_t count = cancelCount.load(std::memory_order::relaxed);
		while (count != 0uz && !cancelCount.compare_exchange_weak(count, count + 1uz, std::memory_order::relaxed))
		{
		}

		return count != 0uz;
	}

	void ResourceLoadProcess::DecrementCancelCount() noexcept
	{
		if (cancelCount.fetch_sub(1uz, std::memory_order::relaxed) == 1uz)
		{
			loadRequest->Cancel();
		}
	}

	void ResourceLoadProcess::Wait() const noexcept
	{
		while (status.load(std::memory_order::acquire) == Async::RequestStatus::Pending)
		{
			status.wait(Async::RequestStatus::Pending, std::memory_order::acquire);
		}
	}

	void ResourceLoadProcess::AddRequest(OngoingResourceRequest& request)
	{
		const auto lock = std::lock_guard(requestMutex);

		requests.push_back(&request);

		if (finished)
		{
			request.OnStatusChanged();
		}
	}

	void ResourceLoadProcess::RemoveRequest(OngoingResourceRequest& request)
	{
		const auto lock = std::lock_guard(requestMutex);

		const auto position = std::ranges::find(requests, &request);
		assert(position != requests.cend() && "Request not found.");
		requests.erase(position);
	}

	void ResourceLoadProcess::SetLoadRequest(std::shared_ptr<IResourceLoadRequest> loadRequest) noexcept
	{
		assert(loadRequest && "Load request is nullptr.");
		this->loadRequest = std::move(loadRequest);
	}

	void ResourceLoadProcess::SetSuccess(std::shared_ptr<const void> mainResource, const std::span<const void* const> resourceInterfaces) noexcept
	{
		assert(status.load(std::memory_order::relaxed) == Async::RequestStatus::Pending && "Invalid status.");
		assert(mainResource && "Main resource is nullptr.");

		this->mainResource = std::move(mainResource);
		{
			const std::lock_guard<std::mutex> lock = resource->Lock();
			resource->SetResourceData(this->mainResource, resourceInterfaces);
		}

		status.store(Async::RequestStatus::Success, std::memory_order::release);
		status.notify_all();

		InvokeCallback();
	}

	void ResourceLoadProcess::SetFailure(std::exception_ptr exception)
	{
		assert(status.load(std::memory_order::relaxed) == Async::RequestStatus::Pending && "Invalid status.");

		this->exception = std::move(exception);

		status.store(Async::RequestStatus::Failure, std::memory_order::release);
		status.notify_all();

		InvokeCallback();
	}

	void ResourceLoadProcess::SetCanceled()
	{
		assert(status.load(std::memory_order::relaxed) == Async::RequestStatus::Pending && "Invalid status.");

		status.store(Async::RequestStatus::Canceled, std::memory_order::release);
		status.notify_all();

		InvokeCallback();
	}

	void ResourceLoadProcess::InvokeCallback() noexcept
	{
		const auto lock = std::lock_guard(requestMutex);

		for (OngoingResourceRequest* const request : requests)
		{
			request->OnStatusChanged();
		}

		finished = true;
	}

	OngoingResourceRequest::OngoingResourceRequest(std::shared_ptr<ResourceLoadProcess> loadProcess, 
		std::move_only_function<void(const IResourceRequest&) noexcept> callback) noexcept :
		loadProcess(std::move(loadProcess)),
		canceled(false),
		callback(std::move(callback))
	{
		assert(this->loadProcess && "Load process is nullptr.");

		if (this->callback)
		{
			this->loadProcess->AddRequest(*this);
		}
	}

	OngoingResourceRequest::~OngoingResourceRequest() noexcept
	{
		if (callback)
		{
			loadProcess->RemoveRequest(*this);
		}
	}

	struct ResourceID OngoingResourceRequest::ResourceID() const noexcept
	{
		return loadProcess->ResourceID();
	}

	bool OngoingResourceRequest::HasInterfaces(const std::span<const std::type_index> types) const noexcept
	{
		return loadProcess->HasInterfaces(types);
	}

	Async::RequestStatus OngoingResourceRequest::Status() const noexcept
	{
		return canceled.load(std::memory_order::relaxed) ? Async::RequestStatus::Canceled : loadProcess->Status();
	}

	std::shared_ptr<const void> OngoingResourceRequest::Resource(const std::type_index type) const
	{
		if (canceled.load(std::memory_order::relaxed))
		{
			throw std::logic_error("Invalid status");
		}

		return loadProcess->Resource(type);
	}

	const std::exception_ptr& OngoingResourceRequest::Exception() const
	{
		if (canceled.load(std::memory_order::relaxed))
		{
			throw std::logic_error("Invalid status");
		}

		return loadProcess->Exception();
	}

	void OngoingResourceRequest::Cancel()
	{
		if (!canceled.exchange(true, std::memory_order::relaxed))
		{
			loadProcess->DecrementCancelCount();
		}
	}

	void OngoingResourceRequest::Wait() const noexcept
	{
		if (canceled.load(std::memory_order::relaxed))
		{
			return;
		}

		loadProcess->Wait();
	}

	void OngoingResourceRequest::OnStatusChanged() noexcept
	{
		callback(*this);
	}
}
