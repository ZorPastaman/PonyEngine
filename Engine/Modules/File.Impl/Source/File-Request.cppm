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

export module PonyEngine.File.Impl:Request;

import std;

import PonyEngine.Async;
import PonyEngine.File;

export namespace PonyEngine::File
{
	/// @brief Request.
	class Request final
	{
	public:
		[[nodiscard("Pure constructor")]]
		Request() noexcept;
		Request(const Request&) = delete;
		Request(Request&&) = delete;

		~Request() noexcept = default;

		/// @brief Gets the request status.
		/// @return Request status.
		[[nodiscard("Pure function")]]
		Async::RequestStatus Status() const noexcept;
		/// @brief Gets how many bytes were transferred.
		/// @return Transferred byte count.
		/// @note It's valid to call it only if the request status is success.
		[[nodiscard("Pure function")]]
		std::size_t ByteCount() const;
		/// @brief Gets an exception that occured during the request execution.
		/// @return Exception.
		/// @note It's valid to call it only if the request status is failure.
		[[nodiscard("Pure function")]]
		const std::exception_ptr& Exception() const;

		/// @brief Sets the status to success.
		/// @param byteCount Transferred byte count.
		void SetSuccess(std::size_t byteCount) noexcept;
		/// @brief Sets the status to failure.
		/// @param exception Exception that occured during the request execution.
		void SetFailed(std::exception_ptr exception) noexcept;
		/// @brief Sets the status to canceled.
		void SetCanceled() noexcept;
		
		/// @brief Makes the thread sleep till the request is completed with success or failure.
		void Wait() const noexcept;

		Request& operator =(const Request&) = delete;
		Request& operator =(Request&&) = delete;

	private:
		std::size_t byteCount; ///< Transferred byte count.
		std::exception_ptr exception; ///< Exception that occured during the request execution.
		std::atomic<Async::RequestStatus> status; ///< Request status.

		static_assert(std::atomic<Async::RequestStatus>::is_always_lock_free, "RequestStatus is not lock-free.");
	};
}

namespace PonyEngine::File
{
	Request::Request() noexcept :
		byteCount{0uz},
		status(Async::RequestStatus::Pending)
	{
	}

	Async::RequestStatus Request::Status() const noexcept
	{
		return status.load(std::memory_order::acquire);
	}

	std::size_t Request::ByteCount() const
	{
		if (status.load(std::memory_order::acquire) != Async::RequestStatus::Success) [[unlikely]]
		{
			throw std::logic_error("Invalid status");
		}

		return byteCount;
	}

	const std::exception_ptr& Request::Exception() const
	{
		if (status.load(std::memory_order::acquire) != Async::RequestStatus::Failure) [[unlikely]]
		{
			throw std::logic_error("Invalid status");
		}

		return exception;
	}

	void Request::SetSuccess(const std::size_t byteCount) noexcept
	{
		assert(status.load(std::memory_order::relaxed) == Async::RequestStatus::Pending && "Invalid status.");

		this->byteCount = byteCount;
		status.store(Async::RequestStatus::Success, std::memory_order::release);
		status.notify_all();
	}

	void Request::SetFailed(std::exception_ptr exception) noexcept
	{
		assert(status.load(std::memory_order::relaxed) == Async::RequestStatus::Pending && "Invalid status.");
		
		this->exception = std::move(exception);
		status.store(Async::RequestStatus::Failure, std::memory_order::release);
		status.notify_all();
	}

	void Request::SetCanceled() noexcept
	{
		assert(status.load(std::memory_order::relaxed) == Async::RequestStatus::Pending && "Invalid status.");
		status.store(Async::RequestStatus::Canceled, std::memory_order::release);
		status.notify_all();
	}

	void Request::Wait() const noexcept
	{
		while (status.load(std::memory_order::acquire) == Async::RequestStatus::Pending)
		{
			status.wait(Async::RequestStatus::Pending, std::memory_order::acquire);
		}
	}
}
