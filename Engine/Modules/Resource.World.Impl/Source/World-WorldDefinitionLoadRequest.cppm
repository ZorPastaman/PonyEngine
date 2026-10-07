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
	class WorldDefinitionLoadRequest : public IResourceLoadRequest
	{
	public:
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
		virtual const std::exception_ptr& Exception() const override final;

		virtual void Cancel() override;

		virtual void Wait() const noexcept override final;

		[[nodiscard("Pure function")]]
		std::span<const std::byte> Input() const noexcept;
		[[nodiscard("Pure function")]]
		PonyEngine::World::WorldDefinition& WorldDefinition() const noexcept;

		/// @brief Sets the status to success.
		void SetSuccess() noexcept;
		/// @brief Sets the status to exception.
		/// @param exception Exception.
		void SetException(std::exception_ptr exception) noexcept;
		/// @brief Sets the status to canceled.
		void SetCanceled() noexcept;

		WorldDefinitionLoadRequest& operator =(const WorldDefinitionLoadRequest&) = delete;
		WorldDefinitionLoadRequest& operator =(WorldDefinitionLoadRequest&&) = delete;

	private:
		/// @brief Invokes the callback if it's not nullptr.
		void InvokeCallback() noexcept;

		std::exception_ptr exception; ///< Exception.
		std::atomic<Async::RequestStatus> status; ///< Status.

		std::span<const std::byte> input;
		std::shared_ptr<PonyEngine::World::WorldDefinition> worldDefinition;
		const void* worldDefinitionInterface;

		std::move_only_function<void(const IResourceLoadRequest&) noexcept> callback;
	};
}

namespace PonyEngine::Resource::World
{
	WorldDefinitionLoadRequest::WorldDefinitionLoadRequest(std::shared_ptr<PonyEngine::World::WorldDefinition> worldDefinition,
		const std::span<const std::byte> input, std::move_only_function<void(const IResourceLoadRequest&) noexcept> callback) :
		status(Async::RequestStatus::Pending),
		input(input),
		worldDefinition(std::move(worldDefinition)),
		worldDefinitionInterface{worldDefinition.get()},
		callback(std::move(callback))
	{
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

	const std::exception_ptr& WorldDefinitionLoadRequest::Exception() const
	{
		if (status.load(std::memory_order::acquire) != Async::RequestStatus::Success) [[unlikely]]
		{
			throw std::logic_error("Invalid status");
		}

		return exception;
	}

	void WorldDefinitionLoadRequest::Cancel()
	{
		// TODO: Implement
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

	void WorldDefinitionLoadRequest::SetSuccess() noexcept
	{
		assert(status.load(std::memory_order::relaxed) == Async::RequestStatus::Pending && "Invalid status.");

		status.store(Async::RequestStatus::Success, std::memory_order::release);
		status.notify_all();

		InvokeCallback();
	}

	void WorldDefinitionLoadRequest::SetException(std::exception_ptr exception) noexcept
	{
		assert(status.load(std::memory_order::relaxed) == Async::RequestStatus::Pending && "Invalid status.");

		this->exception = std::move(exception);

		status.store(Async::RequestStatus::Failure, std::memory_order::release);
		status.notify_all();

		InvokeCallback();
	}

	void WorldDefinitionLoadRequest::SetCanceled() noexcept
	{
		assert(status.load(std::memory_order::relaxed) == Async::RequestStatus::Pending && "Invalid status.");

		status.store(Async::RequestStatus::Canceled, std::memory_order::release);
		status.notify_all();

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
