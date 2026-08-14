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
	class LoadedResourceRequest;

	class ResourceLoadProcess final
	{
	public:
		[[nodiscard("Pure constructor")]]
		ResourceLoadProcess(const std::shared_ptr<const ResourceInfo>& resourceInfo, const std::shared_ptr<ResourceData>& resourceData,
			const std::shared_ptr<std::mutex>& resourceMutex, std::shared_ptr<void>&& resourceDataAccess, IResourceLoader& loader);
		ResourceLoadProcess(const ResourceLoadProcess&) = delete;
		ResourceLoadProcess(ResourceLoadProcess&&) = delete;

		~ResourceLoadProcess() noexcept;

		[[nodiscard("Pure function")]]
		struct ResourceID ResourceID() const noexcept;
		[[nodiscard("Pure function")]]
		bool IsTypeOf(std::span<const std::type_index> types) const noexcept;

		[[nodiscard("Pure function")]]
		RequestStatus Status() const noexcept;
		[[nodiscard("Pure function")]]
		const std::shared_ptr<const ResourceRequestResult>& Result() const;
		[[nodiscard("Pure function")]]
		const std::exception_ptr& Exception() const;

		void IncrementCancelCount() noexcept;
		void DecrementCancelCount();

		void AddObserver(const LoadedResourceRequest& request) const;
		void RemoveObserver(const LoadedResourceRequest& request) const;

		void Wait() const noexcept;

		ResourceLoadProcess& operator =(const ResourceLoadProcess&) = delete;
		ResourceLoadProcess& operator =(ResourceLoadProcess&&) = delete;

	private:
		void SetSuccess(const std::shared_ptr<const void>& mainResource, std::span<const void* const> resources);
		void SetFailure(const std::exception_ptr& exception);
		void SetCancel();

		class ResourceLoadHandler final : public IResourceLoadHandler
		{
		public:
			[[nodiscard("Pure constructor")]]
			explicit ResourceLoadHandler(ResourceLoadProcess* process);
			ResourceLoadHandler(const ResourceLoadHandler&) = delete;
			ResourceLoadHandler(ResourceLoadHandler&&) = delete;

			~ResourceLoadHandler() noexcept = default;

			virtual void SetSuccess(const std::shared_ptr<const void>& mainResource, std::span<const void* const> resources) override;
			virtual void SetFailure(const std::exception_ptr& exception) override;
			virtual void SetCancel() override;

			void Detach() noexcept;

			ResourceLoadHandler& operator =(const ResourceLoadHandler&) = delete;
			ResourceLoadHandler& operator =(ResourceLoadHandler&&) = delete;

		private:
			ResourceLoadProcess* process;
			std::mutex mutex;
		};

		std::shared_ptr<const ResourceInfo> resourceInfo;
		std::shared_ptr<ResourceData> resourceData;
		std::shared_ptr<std::mutex> resourceMutex;

		std::shared_ptr<const ResourceRequestResult> result;
		std::exception_ptr exception;
		std::atomic<RequestStatus> status;

		std::atomic_size_t cancelCount;

		std::shared_ptr<ResourceLoadHandler> handler;
		std::shared_ptr<IResourceLoadRequest> request;

		mutable std::vector<const LoadedResourceRequest*> observers;
		bool observersCalled;
		mutable std::mutex observerMutex;

		static_assert(std::atomic<RequestStatus>::is_always_lock_free, "RequestStatus isn't lock-free.");
		static_assert(std::atomic_size_t::is_always_lock_free, "std::size_t isn't lock-free.");
	};

	class LoadedResourceRequest final : public IResourceRequest
	{
	public:
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
		void OnSuccess() const;
		void OnFailure() const;
		void OnCanceled() const;

		std::shared_ptr<ResourceLoadProcess> process;
		IResourceRequestObserver* observer;

		std::atomic_bool canceled;

		friend ResourceLoadProcess;
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
		cancelCount(0uz),
		handler(std::make_shared<ResourceLoadHandler>(this)),
		request(loader.Load(ResourceLoadContext
		{
			.resourceType = resourceInfo->type,
			.resourceDataAccess = std::move(resourceDataAccess),
			.resourceDataAccessType = resourceInfo->dataAccessType,
			.loadData = resourceInfo->loadData,
			.outputTypes = resourceInfo->outputTypes
		}, handler)),
		observersCalled{false}
	{
	}

	ResourceLoadProcess::~ResourceLoadProcess() noexcept
	{
		handler->Detach();
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
		if (Status() != RequestStatus::Success)
		{
			throw std::logic_error("Invalid status");
		}

		return result;
	}

	const std::exception_ptr& ResourceLoadProcess::Exception() const
	{
		if (Status() != RequestStatus::Failure)
		{
			throw std::logic_error("Invalid status");
		}

		return exception;
	}

	void ResourceLoadProcess::IncrementCancelCount() noexcept
	{
		cancelCount.fetch_add(1uz, std::memory_order::relaxed);
	}

	void ResourceLoadProcess::DecrementCancelCount()
	{
		if (cancelCount.fetch_sub(1uz, std::memory_order::relaxed) == 1uz)
		{
			request->Cancel();
		}
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
		assert(status.load(std::memory_order::relaxed) == RequestStatus::Pending && "Invalid status.");

		{
			const auto lock = std::lock_guard(*resourceMutex);
			resourceData->SetResource(mainResource, resources);
		}
		result = std::make_shared<ResourceRequestResult>(resourceInfo, resourceData, mainResource);
		
		status.store(RequestStatus::Success, std::memory_order::release);

		const auto lock = std::lock_guard(observerMutex);
		for (const LoadedResourceRequest* request : observers)
		{
			request->OnSuccess();
		}
		observersCalled = true;
	}

	void ResourceLoadProcess::SetFailure(const std::exception_ptr& exception)
	{
		assert(status.load(std::memory_order::relaxed) == RequestStatus::Pending && "Invalid status.");

		this->exception = exception;

		status.store(RequestStatus::Failure, std::memory_order::release);

		const auto lock = std::lock_guard(observerMutex);
		for (const LoadedResourceRequest* request : observers)
		{
			request->OnFailure();
		}
		observersCalled = true;
	}

	void ResourceLoadProcess::SetCancel()
	{
		assert(status.load(std::memory_order::relaxed) == RequestStatus::Pending && "Invalid status.");

		status.store(RequestStatus::Canceled, std::memory_order::release);

		const auto lock = std::lock_guard(observerMutex);
		for (const LoadedResourceRequest* request : observers)
		{
			request->OnCanceled();
		}
		observersCalled = true;
	}

	ResourceLoadProcess::ResourceLoadHandler::ResourceLoadHandler(ResourceLoadProcess* const process) :
		process{process}
	{
	}

	void ResourceLoadProcess::ResourceLoadHandler::SetSuccess(const std::shared_ptr<const void>& mainResource, const std::span<const void* const> resources)
	{
		const auto lock = std::lock_guard(mutex);

		if (process)
		{
			process->SetSuccess(mainResource, resources);
		}
	}

	void ResourceLoadProcess::ResourceLoadHandler::SetFailure(const std::exception_ptr& exception)
	{
		const auto lock = std::lock_guard(mutex);

		if (process)
		{
			process->SetFailure(exception);
		}
	}

	void ResourceLoadProcess::ResourceLoadHandler::SetCancel()
	{
		const auto lock = std::lock_guard(mutex);

		if (process)
		{
			process->SetCancel();
		}
	}

	void ResourceLoadProcess::ResourceLoadHandler::Detach() noexcept
	{
		const auto lock = std::lock_guard(mutex);
		process = nullptr;
	}

	struct ResourceID LoadedResourceRequest::ResourceID() const noexcept
	{
		return process->ResourceID();
	}

	LoadedResourceRequest::LoadedResourceRequest(const std::shared_ptr<ResourceLoadProcess>& process, IResourceRequestObserver* const observer) :
		process(process),
		observer{observer},
		canceled(false)
	{
		process->IncrementCancelCount();

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

	void LoadedResourceRequest::OnSuccess() const
	{
		observer->OnSuccess(process->Result());
	}

	void LoadedResourceRequest::OnFailure() const
	{
		observer->OnFailure(process->Exception());
	}

	void LoadedResourceRequest::OnCanceled() const
	{
		observer->OnCancel();
	}
}
