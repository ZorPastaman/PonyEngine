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

export module PonyEngine.Resource.Pack.Impl:LoadableDataAccessRequest;

import std;

import PonyEngine.Async;
import PonyEngine.Resource.Ext;

export namespace PonyEngine::Resource::Pack
{
	/// @brief Loadable data access request.
	class LoadableDataAccessRequest : public ILoadableDataAccessRequest
	{
	public:
		/// @brief Creates a loadable data access request.
		/// @param params Load parameters.
		/// @param callback Request callback.
		[[nodiscard("Pure constructor")]]
		LoadableDataAccessRequest(const LoadParams& params, std::move_only_function<void(const ILoadableDataAccessRequest&) noexcept> callback) noexcept;
		LoadableDataAccessRequest(const LoadableDataAccessRequest&) = delete;
		LoadableDataAccessRequest(LoadableDataAccessRequest&&) = delete;

		virtual ~LoadableDataAccessRequest() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual const LoadParams& Params() const noexcept override final;

		[[nodiscard("Pure function")]]
		virtual Async::RequestStatus Status() const noexcept override final;
		[[nodiscard("Pure function")]]
		virtual std::size_t ByteCount() const override final;
		[[nodiscard("Pure function")]]
		virtual const std::exception_ptr& Exception() const override final;

		virtual void Cancel() override;

		virtual void Wait() const noexcept override final;

		/// @brief Sets the status to success.
		/// @param byteCount Transferred byte count.
		void SetSuccess(std::size_t byteCount) noexcept;
		/// @brief Sets the status to failure.
		/// @param exception Exception that occured during the request execution.
		void SetFailed(std::exception_ptr exception) noexcept;
		/// @brief Sets the status to canceled.
		void SetCanceled() noexcept;

		LoadableDataAccessRequest& operator =(const LoadableDataAccessRequest&) = delete;
		LoadableDataAccessRequest& operator =(LoadableDataAccessRequest&&) = delete;

	private:
		/// @brief Invokes a callback if it's set.
		void InvokeCallback() noexcept;

		const LoadParams params;

		std::size_t byteCount; ///< Transferred byte count.
		std::exception_ptr exception; ///< Exception that occured during the request execution.
		std::atomic<Async::RequestStatus> status; ///< Request status.

		std::move_only_function<void(const ILoadableDataAccessRequest&) noexcept> callback; ///< Callback.

		static_assert(std::atomic<Async::RequestStatus>::is_always_lock_free, "RequestStatus isn't lock-free.");
	};
}

namespace PonyEngine::Resource::Pack
{
	LoadableDataAccessRequest::LoadableDataAccessRequest(const LoadParams& params, std::move_only_function<void(const ILoadableDataAccessRequest&) noexcept> callback) noexcept :
		params(params),
		byteCount{0uz},
		status(Async::RequestStatus::Pending),
		callback(std::move(callback))
	{
	}

	const LoadParams& LoadableDataAccessRequest::Params() const noexcept
	{
		return params;
	}

	Async::RequestStatus LoadableDataAccessRequest::Status() const noexcept
	{
		return status.load(std::memory_order::acquire);
	}

	std::size_t LoadableDataAccessRequest::ByteCount() const
	{
		if (status.load(std::memory_order::acquire) != Async::RequestStatus::Success) [[unlikely]]
		{
			throw std::logic_error("Invalid status");
		}

		return byteCount;
	}

	const std::exception_ptr& LoadableDataAccessRequest::Exception() const
	{
		if (status.load(std::memory_order::acquire) != Async::RequestStatus::Failure) [[unlikely]]
		{
			throw std::logic_error("Invalid status");
		}

		return exception;
	}

	void LoadableDataAccessRequest::Cancel()
	{
	}

	void LoadableDataAccessRequest::Wait() const noexcept
	{
		while (status.load(std::memory_order::acquire) == Async::RequestStatus::Pending)
		{
			status.wait(Async::RequestStatus::Pending, std::memory_order::acquire);
		}
	}

	void LoadableDataAccessRequest::SetSuccess(const std::size_t byteCount) noexcept
	{
		assert(status.load(std::memory_order::relaxed) == Async::RequestStatus::Pending && "Invalid status.");

		this->byteCount = byteCount;
		status.store(Async::RequestStatus::Success, std::memory_order::release);
		status.notify_all();

		InvokeCallback();
	}

	void LoadableDataAccessRequest::SetFailed(std::exception_ptr exception) noexcept
	{
		assert(status.load(std::memory_order::relaxed) == Async::RequestStatus::Pending && "Invalid status.");

		this->exception = std::move(exception);
		status.store(Async::RequestStatus::Failure, std::memory_order::release);
		status.notify_all();

		InvokeCallback();
	}

	void LoadableDataAccessRequest::SetCanceled() noexcept
	{
		assert(status.load(std::memory_order::relaxed) == Async::RequestStatus::Pending && "Invalid status.");
		status.store(Async::RequestStatus::Canceled, std::memory_order::release);
		status.notify_all();

		InvokeCallback();
	}

	void LoadableDataAccessRequest::InvokeCallback() noexcept
	{
		if (callback)
		{
			callback(*this);
		}
	}
}
