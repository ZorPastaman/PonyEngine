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

export module PonyEngine.Resource.Pack.Impl:PackUnmountRequest;

import std;

import PonyEngine.Async;
import PonyEngine.Resource.Pack;

export namespace PonyEngine::Resource::Pack
{
	class PackUnmountRequest final : public IPackUnmountRequest
	{
	public:
		[[nodiscard("Pure constructor")]]
		PackUnmountRequest(PackHandle packHandle, std::move_only_function<void(const IPackUnmountRequest&) noexcept> callback) noexcept;
		PackUnmountRequest(const PackUnmountRequest&) = delete;
		PackUnmountRequest(PackUnmountRequest&&) = delete;

		~PackUnmountRequest() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual PackHandle Pack() const noexcept override;

		[[nodiscard("Pure function")]] 
		virtual Async::RequestStatus Status() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual const std::exception_ptr& Exception() const override;

		virtual void Cancel() override;

		virtual void Wait() const noexcept override;

		[[nodiscard("Pure function")]]
		bool IsCancelRequested() const noexcept;

		void SetSuccess() noexcept;
		void SetFailure(std::exception_ptr exception) noexcept;
		void SetCanceled() noexcept;

		PackUnmountRequest& operator =(const PackUnmountRequest&) = delete;
		PackUnmountRequest& operator =(PackUnmountRequest&&) = delete;

	private:
		void InvokeCallback() noexcept;

		PackHandle packHandle;

		std::exception_ptr exception;
		std::atomic<Async::RequestStatus> status;

		std::atomic_bool isCancelRequested;

		std::move_only_function<void(const IPackUnmountRequest&) noexcept> callback;

		static_assert(std::atomic<Async::RequestStatus>::is_always_lock_free, "RequestStatus isn't lock-free.");
		static_assert(std::atomic_bool::is_always_lock_free, "bool isn't lock-free.");
	};
}

namespace PonyEngine::Resource::Pack
{
	PackUnmountRequest::PackUnmountRequest(const PackHandle packHandle, std::move_only_function<void(const IPackUnmountRequest&) noexcept> callback) noexcept :
		packHandle(packHandle),
		status(Async::RequestStatus::Pending),
		isCancelRequested(false),
		callback(std::move(callback))
	{
	}

	PackHandle PackUnmountRequest::Pack() const noexcept
	{
		return packHandle;
	}

	Async::RequestStatus PackUnmountRequest::Status() const noexcept
	{
		return status.load(std::memory_order::acquire);
	}

	const std::exception_ptr& PackUnmountRequest::Exception() const
	{
		if (status.load(std::memory_order::acquire) != Async::RequestStatus::Failure)
		{
			throw std::logic_error("Invalid status");
		}

		return exception;
	}

	void PackUnmountRequest::Cancel()
	{
		isCancelRequested.store(true, std::memory_order::relaxed);
	}

	void PackUnmountRequest::Wait() const noexcept
	{
		while (status.load(std::memory_order::acquire) == Async::RequestStatus::Pending)
		{
			status.wait(Async::RequestStatus::Pending, std::memory_order::relaxed);
		}
	}

	bool PackUnmountRequest::IsCancelRequested() const noexcept
	{
		return isCancelRequested.load(std::memory_order::relaxed);
	}

	void PackUnmountRequest::SetSuccess() noexcept
	{
		assert(status.load(std::memory_order::relaxed) == Async::RequestStatus::Pending && "Invalid status");

		status.store(Async::RequestStatus::Success, std::memory_order::release);
		status.notify_all();

		InvokeCallback();
	}

	void PackUnmountRequest::SetFailure(std::exception_ptr exception) noexcept
	{
		assert(status.load(std::memory_order::relaxed) == Async::RequestStatus::Pending && "Invalid status");

		this->exception = std::move(exception);
		status.store(Async::RequestStatus::Failure, std::memory_order::release);
		status.notify_all();

		InvokeCallback();
	}

	void PackUnmountRequest::SetCanceled() noexcept
	{
		assert(status.load(std::memory_order::relaxed) == Async::RequestStatus::Pending && "Invalid status");

		status.store(Async::RequestStatus::Canceled, std::memory_order::release);
		status.notify_all();

		InvokeCallback();
	}

	void PackUnmountRequest::InvokeCallback() noexcept
	{
		if (callback)
		{
			callback(*this);
		}
	}
}
