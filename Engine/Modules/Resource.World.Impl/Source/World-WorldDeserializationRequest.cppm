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

export module PonyEngine.Resource.World.Impl:WorldDeserializationRequest;

import std;

import PonyEngine.Async;
import PonyEngine.Resource.World.Ext;
import PonyEngine.World;

export namespace PonyEngine::Resource::World
{
	class WorldDeserializationRequest final : public IWorldDeserializationRequest
	{
	public:
		[[nodiscard("Pure constructor")]]
		WorldDeserializationRequest(PonyEngine::World::Object& output, std::move_only_function<void(const IWorldDeserializationRequest&) noexcept> callback);
		WorldDeserializationRequest(const WorldDeserializationRequest&) = delete;
		WorldDeserializationRequest(WorldDeserializationRequest&&) = delete;

		~WorldDeserializationRequest() noexcept = default;

		[[nodiscard("Pure function")]] 
		virtual Async::RequestStatus Status() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::span<const std::exception_ptr> Exceptions() const override;

		virtual void Cancel() override;

		virtual void Wait() const noexcept override;

		[[nodiscard("Pure function")]]
		const std::shared_ptr<IResourceRequest>& LoadRequest() const noexcept;
		void LoadRequest(std::shared_ptr<IResourceRequest> request) noexcept;

		void SetSuccess(PonyEngine::World::Object object) noexcept;
		void SetFailure(std::span<const std::exception_ptr> exceptions) noexcept;
		void SetCanceled() noexcept;

		WorldDeserializationRequest& operator =(const WorldDeserializationRequest&) = delete;
		WorldDeserializationRequest& operator =(WorldDeserializationRequest&&) = delete;

	private:
		void InvokeCallback() noexcept;

		PonyEngine::World::Object* output;

		std::vector<std::exception_ptr> exceptions;
		std::atomic<Async::RequestStatus> status;

		std::shared_ptr<IResourceRequest> loadRequest;

		std::move_only_function<void(const IWorldDeserializationRequest&) noexcept> callback;

		static_assert(std::atomic<Async::RequestStatus>::is_always_lock_free, "std::atomic<Async::RequestStatus> isn't lock-free");
	};
}

namespace PonyEngine::Resource::World
{
	WorldDeserializationRequest::WorldDeserializationRequest(PonyEngine::World::Object& output, 
		std::move_only_function<void(const IWorldDeserializationRequest&) noexcept> callback) :
		output{&output},
		status(Async::RequestStatus::Pending),
		callback(std::move(callback))
	{
		exceptions.reserve(4uz);
	}

	Async::RequestStatus WorldDeserializationRequest::Status() const noexcept
	{
		return status.load(std::memory_order::acquire);
	}

	std::span<const std::exception_ptr> WorldDeserializationRequest::Exceptions() const
	{
		if (status.load(std::memory_order::acquire) != Async::RequestStatus::Failure) [[unlikely]]
		{
			throw std::logic_error("Invalid status");
		}

		return exceptions;
	}

	void WorldDeserializationRequest::Cancel()
	{
		loadRequest->Cancel();
	}

	void WorldDeserializationRequest::Wait() const noexcept
	{
		status.wait(Async::RequestStatus::Pending, std::memory_order::acquire);
	}

	const std::shared_ptr<IResourceRequest>& WorldDeserializationRequest::LoadRequest() const noexcept
	{
		return loadRequest;
	}

	void WorldDeserializationRequest::LoadRequest(std::shared_ptr<IResourceRequest> request) noexcept
	{
		loadRequest = std::move(request);
	}

	void WorldDeserializationRequest::SetSuccess(PonyEngine::World::Object object) noexcept
	{
		assert(status.load(std::memory_order::relaxed) == Async::RequestStatus::Pending && "Invalid status.");

		*output = std::move(object);

		status.store(Async::RequestStatus::Success, std::memory_order::release);
		status.notify_all();

		InvokeCallback();
	}

	void WorldDeserializationRequest::SetFailure(const std::span<const std::exception_ptr> exceptions) noexcept
	{
		assert(status.load(std::memory_order::relaxed) == Async::RequestStatus::Pending && "Invalid status.");

		try
		{
			this->exceptions.assign_range(exceptions);
		}
		catch (...)
		{
			const std::size_t count = std::min(this->exceptions.size(), exceptions.size());
			try
			{
				for (std::size_t i = 0uz; i < count; ++i)
				{
					this->exceptions.push_back(exceptions[i]);
				}
			}
			catch (...)
			{
				// Nothing to do.
			}
		}

		status.store(Async::RequestStatus::Failure, std::memory_order::release);
		status.notify_all();

		InvokeCallback();
	}

	void WorldDeserializationRequest::SetCanceled() noexcept
	{
		assert(status.load(std::memory_order::relaxed) == Async::RequestStatus::Pending && "Invalid status.");

		status.store(Async::RequestStatus::Canceled, std::memory_order::release);
		status.notify_all();

		InvokeCallback();
	}

	void WorldDeserializationRequest::InvokeCallback() noexcept
	{
		if (callback)
		{
			callback(*this);
		}
	}
}
