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

import PonyEngine.Resource.Ext;

export namespace PonyEngine::Resource::Pack
{
	class LoadableDataAccessRequest : public ILoadableDataAccessRequest
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit LoadableDataAccessRequest(const LoadParams& params, std::move_only_function<void(const ILoadableDataAccessRequest&) noexcept> callback) noexcept;
		LoadableDataAccessRequest(const LoadableDataAccessRequest&) = delete;
		LoadableDataAccessRequest(LoadableDataAccessRequest&&) = delete;

		virtual ~LoadableDataAccessRequest() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual const LoadParams& Params() const noexcept override final;

		[[nodiscard("Pure function")]]
		virtual LoadableRequestStatus Status() const noexcept override final;
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
		void SetFailed(const std::exception_ptr& exception) noexcept;
		/// @brief Sets the status to canceled.
		void SetCanceled() noexcept;

		LoadableDataAccessRequest& operator =(const LoadableDataAccessRequest&) = delete;
		LoadableDataAccessRequest& operator =(LoadableDataAccessRequest&&) = delete;

	private:
		void InvokeCallback() noexcept;

		const LoadParams params;

		std::size_t byteCount; ///< Transferred byte count.
		std::exception_ptr exception; ///< Exception that occured during the request execution.
		std::atomic<LoadableRequestStatus> status;

		std::move_only_function<void(const ILoadableDataAccessRequest&) noexcept> callback;

		static_assert(std::atomic<LoadableRequestStatus>::is_always_lock_free, "LoadableRequestStatus isn't lock-free.");
		static_assert(std::atomic_bool::is_always_lock_free, "bool isn't lock-free.");
	};
}

namespace PonyEngine::Resource::Pack
{
	LoadableDataAccessRequest::LoadableDataAccessRequest(const LoadParams& params, std::move_only_function<void(const ILoadableDataAccessRequest&) noexcept> callback) noexcept :
		params(params),
		byteCount{0uz},
		status(LoadableRequestStatus::Pending),
		callback(std::move(callback))
	{
	}

	const LoadParams& LoadableDataAccessRequest::Params() const noexcept
	{
		return params;
	}

	LoadableRequestStatus LoadableDataAccessRequest::Status() const noexcept
	{
		return status.load(std::memory_order::acquire);
	}

	std::size_t LoadableDataAccessRequest::ByteCount() const
	{
		if (status.load(std::memory_order::acquire) != LoadableRequestStatus::Success) [[unlikely]]
		{
			throw std::logic_error("Invalid status");
		}

		return byteCount;
	}

	const std::exception_ptr& LoadableDataAccessRequest::Exception() const
	{
		if (status.load(std::memory_order::acquire) != LoadableRequestStatus::Failure) [[unlikely]]
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
		while (status.load(std::memory_order::acquire) == LoadableRequestStatus::Pending)
		{
			status.wait(LoadableRequestStatus::Pending, std::memory_order::acquire);
		}
	}

	void LoadableDataAccessRequest::SetSuccess(const std::size_t byteCount) noexcept
	{
		assert(status.load(std::memory_order::relaxed) == LoadableRequestStatus::Pending && "Invalid status.");

		this->byteCount = byteCount;
		status.store(LoadableRequestStatus::Success, std::memory_order::release);
		status.notify_all();

		InvokeCallback();
	}

	void LoadableDataAccessRequest::SetFailed(const std::exception_ptr& exception) noexcept
	{
		assert(status.load(std::memory_order::relaxed) == LoadableRequestStatus::Pending && "Invalid status.");

		this->exception = exception;
		status.store(LoadableRequestStatus::Failure, std::memory_order::release);
		status.notify_all();

		InvokeCallback();
	}

	void LoadableDataAccessRequest::SetCanceled() noexcept
	{
		assert(status.load(std::memory_order::relaxed) == LoadableRequestStatus::Pending && "Invalid status.");
		status.store(LoadableRequestStatus::Canceled, std::memory_order::release);
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
