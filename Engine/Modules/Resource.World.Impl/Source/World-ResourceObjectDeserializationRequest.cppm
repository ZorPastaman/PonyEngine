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

export module PonyEngine.Resource.World.Impl:ResourceObjectDeserializationRequest;

import std;

import PonyEngine.Async;
import PonyEngine.Resource.World.Ext;
import PonyEngine.World;

export namespace PonyEngine::Resource::World
{
	/// @brief Resource object deserialization request.
	class ResourceObjectDeserializationRequest final : public IWorldDeserializationRequest
	{
	public:
		/// @brief Creates a resource object deserialization request.
		/// @param output Object output.
		/// @param callback Callback.
		[[nodiscard("Pure constructor")]]
		ResourceObjectDeserializationRequest(PonyEngine::World::Object& output, std::move_only_function<void(const IWorldDeserializationRequest&) noexcept> callback);
		ResourceObjectDeserializationRequest(const ResourceObjectDeserializationRequest&) = delete;
		ResourceObjectDeserializationRequest(ResourceObjectDeserializationRequest&&) = delete;

		~ResourceObjectDeserializationRequest() noexcept = default;

		[[nodiscard("Pure function")]] 
		virtual Async::RequestStatus Status() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::span<const std::exception_ptr> Exceptions() const override;

		virtual void Cancel() override;

		virtual void Wait() const noexcept override;

		/// @brief Gets the load request.
		/// @return Load request.
		[[nodiscard("Pure function")]]
		const std::shared_ptr<IResourceRequest>& LoadRequest() const noexcept;
		/// @brief Sets the load request.
		/// @param request Load request.
		void LoadRequest(std::shared_ptr<IResourceRequest> request) noexcept;

		/// @brief Sets the status to success.
		/// @param object World object.
		void SetSuccess(PonyEngine::World::Object object) noexcept;
		/// @brief Sets the status to failure.
		/// @param exceptions Exceptions.
		void SetFailure(std::span<const std::exception_ptr> exceptions) noexcept;
		/// @brief Sets the status to canceled.
		void SetCanceled() noexcept;

		ResourceObjectDeserializationRequest& operator =(const ResourceObjectDeserializationRequest&) = delete;
		ResourceObjectDeserializationRequest& operator =(ResourceObjectDeserializationRequest&&) = delete;

	private:
		/// @brief Invokes the callback.
		void InvokeCallback() noexcept;

		PonyEngine::World::Object* output; ///< World object slot.

		std::vector<std::exception_ptr> exceptions; ///< Exceptions.
		std::atomic<Async::RequestStatus> status; ///< Status.

		std::shared_ptr<IResourceRequest> loadRequest; ///< Load request.

		std::move_only_function<void(const IWorldDeserializationRequest&) noexcept> callback; ///< Callback.

		static_assert(std::atomic<Async::RequestStatus>::is_always_lock_free, "std::atomic<Async::RequestStatus> isn't lock-free");
	};
}

namespace PonyEngine::Resource::World
{
	ResourceObjectDeserializationRequest::ResourceObjectDeserializationRequest(PonyEngine::World::Object& output, 
		std::move_only_function<void(const IWorldDeserializationRequest&) noexcept> callback) :
		output{&output},
		status(Async::RequestStatus::Pending),
		callback(std::move(callback))
	{
		exceptions.reserve(4uz);
	}

	Async::RequestStatus ResourceObjectDeserializationRequest::Status() const noexcept
	{
		return status.load(std::memory_order::acquire);
	}

	std::span<const std::exception_ptr> ResourceObjectDeserializationRequest::Exceptions() const
	{
		if (status.load(std::memory_order::acquire) != Async::RequestStatus::Failure) [[unlikely]]
		{
			throw std::logic_error("Invalid status");
		}

		return exceptions;
	}

	void ResourceObjectDeserializationRequest::Cancel()
	{
		loadRequest->Cancel();
	}

	void ResourceObjectDeserializationRequest::Wait() const noexcept
	{
		status.wait(Async::RequestStatus::Pending, std::memory_order::acquire);
	}

	const std::shared_ptr<IResourceRequest>& ResourceObjectDeserializationRequest::LoadRequest() const noexcept
	{
		return loadRequest;
	}

	void ResourceObjectDeserializationRequest::LoadRequest(std::shared_ptr<IResourceRequest> request) noexcept
	{
		loadRequest = std::move(request);
	}

	void ResourceObjectDeserializationRequest::SetSuccess(PonyEngine::World::Object object) noexcept
	{
		assert(status.load(std::memory_order::relaxed) == Async::RequestStatus::Pending && "Invalid status.");

		*output = std::move(object);

		status.store(Async::RequestStatus::Success, std::memory_order::release);
		status.notify_all();

		InvokeCallback();
	}

	void ResourceObjectDeserializationRequest::SetFailure(const std::span<const std::exception_ptr> exceptions) noexcept
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

	void ResourceObjectDeserializationRequest::SetCanceled() noexcept
	{
		assert(status.load(std::memory_order::relaxed) == Async::RequestStatus::Pending && "Invalid status.");

		status.store(Async::RequestStatus::Canceled, std::memory_order::release);
		status.notify_all();

		InvokeCallback();
	}

	void ResourceObjectDeserializationRequest::InvokeCallback() noexcept
	{
		if (callback)
		{
			callback(*this);
		}
	}
}
