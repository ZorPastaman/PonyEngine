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

export module PonyEngine.Resource.World.Impl:WorldDefinitionLoadRequest;

import std;

import PonyEngine.Async;
import PonyEngine.Resource.World;
import PonyEngine.World;

export namespace PonyEngine::Resource::World
{
	/// @brief World definition load request.
	class WorldDefinitionLoadRequest : public IResourceLoadRequest
	{
	public:
		/// @brief Creates a world definition load request.
		/// @param worldDefinition World definition.
		/// @param input World data input.
		/// @param callback Callback.
		[[nodiscard("Pure constructor")]]
		WorldDefinitionLoadRequest(std::shared_ptr<PonyEngine::World::WorldDefinition> worldDefinition, 
			std::span<const std::byte> input, std::move_only_function<void(const IResourceLoadRequest&) noexcept> callback);
		WorldDefinitionLoadRequest(const WorldDefinitionLoadRequest&) = delete;
		WorldDefinitionLoadRequest(WorldDefinitionLoadRequest&&) = delete;

		virtual ~WorldDefinitionLoadRequest() noexcept = default;

		[[nodiscard("Pure function")]] 
		virtual Async::RequestStatus Status() const noexcept override final;
		[[nodiscard("Pure function")]] 
		virtual std::shared_ptr<const void> MainResource() const override final;
		[[nodiscard("Pure function")]] 
		virtual std::span<const void* const> ResourceInterfaces() const override final;
		[[nodiscard("Pure function")]] 
		virtual std::span<const std::exception_ptr> Exceptions() const override final;

		virtual void Cancel() override;

		virtual void Wait() const noexcept override final;

		/// @brief Gets the input data.
		/// @return Input data.
		[[nodiscard("Pure function")]]
		std::span<const std::byte> Input() const noexcept;
		/// @brief Gets the world definition.
		/// @return World definition.
		[[nodiscard("Pure function")]]
		PonyEngine::World::WorldDefinition& WorldDefinition() const noexcept;

		/// @brief Sets the max job count.
		/// @param count Job count.
		void SetMaxJobCount(std::size_t count);
		/// @brief Increments the job count.
		void IncrementJobCount() noexcept;
		/// @brief Decrements the job count.
		/// @return @a True if it reached 0; @a false otherwise.
		bool DecrementJobCount() noexcept;

		/// @brief Adds the deserialization request.
		/// @param request Deserialization request.
		void AddDeserializationRequest(std::shared_ptr<IWorldDeserializationRequest> request);

		/// @brief Checks if it has at least one exception.
		/// @return @a True if it has; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool HasException() const noexcept;
		/// @brief Adds the exception.
		/// @param exception Exception to add.
		void AddException(std::exception_ptr exception) noexcept;
		/// @brief Adds the exceptions.
		/// @param exceptions Exceptions to add.
		void AddExceptions(std::span<const std::exception_ptr> exceptions) noexcept;

		/// @brief Checks if the cancel is requested.
		/// @return @a True if it's requested; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsCancelRequested() const noexcept;
		/// @brief Checks if the cancel count is greater than 0.
		/// @return @a True if it's greater; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool HasCancel() const noexcept;
		/// @brief Increments the cancel count.
		void IncrementCancelCount() noexcept;

		/// @brief Sets the status to success.
		void SetSuccess() noexcept;
		/// @brief Sets the status to failure.
		void SetFailure() noexcept;
		/// @brief Sets the status to canceled.
		void SetCanceled() noexcept;

		WorldDefinitionLoadRequest& operator =(const WorldDefinitionLoadRequest&) = delete;
		WorldDefinitionLoadRequest& operator =(WorldDefinitionLoadRequest&&) = delete;

	private:
		/// @brief Sets the status.
		/// @param status Status.
		void SetStatus(Async::RequestStatus status) noexcept;

		/// @brief Invokes the callback if it's not nullptr.
		void InvokeCallback() noexcept;

		std::vector<std::exception_ptr> exceptions; ///< Exceptions.
		mutable std::mutex exceptionMutex; /// Exception mutex.
		std::atomic<Async::RequestStatus> status; ///< Status.

		std::atomic_bool cancelRequested; ///< Is cancel requested?
		std::atomic_size_t cancelCount; ///< Request cancel count.

		std::span<const std::byte> input; ///< Data input.
		std::shared_ptr<PonyEngine::World::WorldDefinition> worldDefinition; ///< World definition.
		const void* worldDefinitionInterface; ///< World definition interface.

		std::atomic_size_t jobCount; ///< Job count.
		std::vector<std::shared_ptr<IWorldDeserializationRequest>> deserializationRequests; ///< Deserialization requests.
		std::size_t nextDeserializationRequest; ///< Next deserialization request.
		std::atomic_size_t deserializationRequestCount; ///< Deserialization request count.

		std::move_only_function<void(const IResourceLoadRequest&) noexcept> callback; ///< Callback.

		static_assert(std::atomic_size_t::is_always_lock_free, "std::size_t isn't lock-free");
		static_assert(std::atomic_bool::is_always_lock_free, "bool isn't lock-free");
	};
}

namespace PonyEngine::Resource::World
{
	WorldDefinitionLoadRequest::WorldDefinitionLoadRequest(std::shared_ptr<PonyEngine::World::WorldDefinition> worldDefinition,
		const std::span<const std::byte> input, std::move_only_function<void(const IResourceLoadRequest&) noexcept> callback) :
		status(Async::RequestStatus::Pending),
		cancelRequested(false),
		cancelCount(0uz),
		input(input),
		worldDefinition(std::move(worldDefinition)),
		worldDefinitionInterface{this->worldDefinition.get()},
		jobCount(1uz),
		nextDeserializationRequest(0uz),
		deserializationRequestCount(0uz),
		callback(std::move(callback))
	{
		exceptions.reserve(4uz);
	}

	Async::RequestStatus WorldDefinitionLoadRequest::Status() const noexcept
	{
		return status.load(std::memory_order::acquire);
	}

	std::shared_ptr<const void> WorldDefinitionLoadRequest::MainResource() const
	{
		if (status.load(std::memory_order::acquire) != Async::RequestStatus::Success) [[unlikely]]
		{
			throw std::logic_error("Invalid status");
		}

		return worldDefinition;
	}

	std::span<const void* const> WorldDefinitionLoadRequest::ResourceInterfaces() const
	{
		if (status.load(std::memory_order::acquire) != Async::RequestStatus::Success) [[unlikely]]
		{
			throw std::logic_error("Invalid status");
		}

		return std::span(&worldDefinitionInterface, 1uz);
	}

	std::span<const std::exception_ptr> WorldDefinitionLoadRequest::Exceptions() const
	{
		if (status.load(std::memory_order::acquire) != Async::RequestStatus::Failure) [[unlikely]]
		{
			throw std::logic_error("Invalid status");
		}

		return exceptions;
	}

	void WorldDefinitionLoadRequest::Cancel()
	{
		cancelRequested.store(true, std::memory_order::relaxed);

		const std::size_t requestCount = deserializationRequestCount.load(std::memory_order::acquire);
		for (std::size_t i = 0uz; i < requestCount; ++i)
		{
			deserializationRequests[i]->Cancel();
		}
	}

	void WorldDefinitionLoadRequest::Wait() const noexcept
	{
		while (status.load(std::memory_order::acquire) == Async::RequestStatus::Pending)
		{
			status.wait(Async::RequestStatus::Pending, std::memory_order::acquire);
		}
	}

	std::span<const std::byte> WorldDefinitionLoadRequest::Input() const noexcept
	{
		return input;
	}

	PonyEngine::World::WorldDefinition& WorldDefinitionLoadRequest::WorldDefinition() const noexcept
	{
		return *worldDefinition;
	}

	void WorldDefinitionLoadRequest::SetMaxJobCount(const std::size_t count)
	{
		deserializationRequests.resize(count);
	}

	void WorldDefinitionLoadRequest::IncrementJobCount() noexcept
	{
		jobCount.fetch_add(1uz, std::memory_order::relaxed);
	}

	bool WorldDefinitionLoadRequest::DecrementJobCount() noexcept
	{
		return jobCount.fetch_sub(1uz, std::memory_order::relaxed) == 1uz;
	}

	void WorldDefinitionLoadRequest::AddDeserializationRequest(std::shared_ptr<IWorldDeserializationRequest> request)
	{
		deserializationRequests[nextDeserializationRequest++] = std::move(request);
		deserializationRequestCount.fetch_add(1uz, std::memory_order::release);
	}

	bool WorldDefinitionLoadRequest::HasException() const noexcept
	{
		const auto lock = std::lock_guard(exceptionMutex);
		return exceptions.size() > 0uz;
	}

	void WorldDefinitionLoadRequest::AddException(std::exception_ptr exception) noexcept
	{
		const auto lock = std::lock_guard(exceptionMutex);
		try
		{
			exceptions.push_back(std::move(exception));
		}
		catch (...)
		{
			// Nothing to do
		}
	}

	void WorldDefinitionLoadRequest::AddExceptions(const std::span<const std::exception_ptr> exceptions) noexcept
	{
		const auto lock = std::lock_guard(exceptionMutex);

		try
		{
			this->exceptions.append_range(exceptions);
		}
		catch (...)
		{
			const std::size_t preallocatedCount = this->exceptions.capacity() - this->exceptions.size();
			try
			{
				this->exceptions.append_range(exceptions.subspan(0uz, preallocatedCount));
			}
			catch (...)
			{
				// Nothing to do
			}
		}
	}

	bool WorldDefinitionLoadRequest::IsCancelRequested() const noexcept
	{
		return cancelRequested.load(std::memory_order::relaxed);
	}

	bool WorldDefinitionLoadRequest::HasCancel() const noexcept
	{
		return cancelCount.load(std::memory_order::relaxed) > 0uz;
	}

	void WorldDefinitionLoadRequest::IncrementCancelCount() noexcept
	{
		cancelCount.fetch_add(1uz, std::memory_order::relaxed);
	}

	void WorldDefinitionLoadRequest::SetSuccess() noexcept
	{
		SetStatus(Async::RequestStatus::Success);
	}

	void WorldDefinitionLoadRequest::SetFailure() noexcept
	{
		SetStatus(Async::RequestStatus::Failure);
	}

	void WorldDefinitionLoadRequest::SetCanceled() noexcept
	{
		SetStatus(Async::RequestStatus::Canceled);
	}

	void WorldDefinitionLoadRequest::SetStatus(const Async::RequestStatus status) noexcept
	{
		assert(this->status.load(std::memory_order::relaxed) == Async::RequestStatus::Pending && "Invalid status.");

		this->status.store(Async::RequestStatus::Canceled, std::memory_order::release);
		this->status.notify_all();

		InvokeCallback();
	}

	void WorldDefinitionLoadRequest::InvokeCallback() noexcept
	{
		if (callback)
		{
			callback(*this);
		}
	}
}
