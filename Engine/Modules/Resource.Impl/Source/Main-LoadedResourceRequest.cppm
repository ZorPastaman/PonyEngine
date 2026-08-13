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

export module PonyEngine.Resource.Impl:LoadedResourceRequest;

import std;

import PonyEngine.Resource;

import :IResourceLoadObserver;
import :ResourceLoadHandler;

export namespace PonyEngine::Resource
{
	class LoadedResourceRequest final : public IResourceRequest, private IResourceLoadObserver
	{
	public:
		[[nodiscard("Pure constructor")]]
		LoadedResourceRequest(struct ResourceID id, const std::shared_ptr<ResourceLoadHandler>& loadHandler);
		LoadedResourceRequest(const LoadedResourceRequest&) = delete;
		LoadedResourceRequest(LoadedResourceRequest&&) = delete;

		~LoadedResourceRequest() noexcept = default;

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

		LoadedResourceRequest& operator =(const LoadedResourceRequest&) = delete;
		LoadedResourceRequest& operator =(LoadedResourceRequest&&) = delete;

	private:
		virtual void OnStatusChanged() noexcept override;

		void Observe() noexcept;

		struct ResourceID id;

		std::shared_ptr<ResourceLoadHandler> loadHandler;

		std::atomic_bool canceled;

		mutable std::vector<IResourceRequestObserver*> observers;
		bool isObserverCalled;
		mutable std::mutex observerMutex;

		static_assert(std::atomic_bool::is_always_lock_free, "bool isn't lock-free.");
	};
}

namespace PonyEngine::Resource
{
	LoadedResourceRequest::LoadedResourceRequest(const struct ResourceID id, const std::shared_ptr<ResourceLoadHandler>& loadHandler) :
		id(id),
		loadHandler(loadHandler),
		canceled(false),
		isObserverCalled{false}
	{
	}

	struct ResourceID LoadedResourceRequest::ResourceID() const noexcept
	{
		return id;
	}

	bool LoadedResourceRequest::IsTypeOf(const std::span<const std::type_index> types) const noexcept
	{
		return loadHandler->IsTypeOf(types);
	}

	RequestStatus LoadedResourceRequest::Status() const noexcept
	{
		return loadHandler->Status();
	}

	std::shared_ptr<const void> LoadedResourceRequest::Resource(const std::type_index type) const
	{
		return loadHandler->Resource(type);
	}

	const std::exception_ptr& LoadedResourceRequest::Exception() const
	{
		return loadHandler->Exception();
	}

	void LoadedResourceRequest::Cancel()
	{
		if (!canceled.exchange(true, std::memory_order::relaxed))
		{
			loadHandler->DecrementCancelCount();
		}
	}

	void LoadedResourceRequest::Wait() const noexcept
	{
		loadHandler->Wait();
	}

	void LoadedResourceRequest::AddObserver(IResourceRequestObserver& observer) const
	{
		const auto lock = std::lock_guard(observerMutex);
		observers.push_back(&observer);

		if (isObserverCalled)
		{
			observer.OnStatusChanged(*this);
		}
	}

	void LoadedResourceRequest::RemoveObserver(IResourceRequestObserver& observer) const
	{
		const auto lock = std::lock_guard(observerMutex);
		const auto position = std::ranges::find(observers, &observer);
		assert(position != observers.cend() && "Observer wasn't added.");
		observers.erase(position);
	}

	void LoadedResourceRequest::OnStatusChanged() noexcept
	{
		Observe();
	}

	void LoadedResourceRequest::Observe() noexcept
	{
		const auto lock = std::lock_guard(observerMutex);

		for (IResourceRequestObserver* const observer : observers)
		{
			observer->OnStatusChanged(*this);
		}

		isObserverCalled = true;
	}
}
