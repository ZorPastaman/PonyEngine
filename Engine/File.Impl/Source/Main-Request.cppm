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

import PonyEngine.File;

export namespace PonyEngine::File
{
	class Request final
	{
	public:
		[[nodiscard("Pure constructor")]]
		Request() noexcept;
		Request(const Request&) = delete;
		Request(Request&&) = delete;

		~Request() noexcept = default;

		[[nodiscard("Pure function")]]
		RequestStatus Status() const noexcept;
		[[nodiscard("Pure function")]]
		std::size_t ByteCount() const;
		[[nodiscard("Pure function")]]
		const std::exception_ptr& Exception() const;

		void SetSuccess(std::size_t byteCount) noexcept;
		void SetFailed(const std::exception_ptr& exception) noexcept;

		void Wait() const noexcept;

		Request& operator =(const Request&) = delete;
		Request& operator =(Request&&) = delete;

	private:
		std::size_t byteCount;
		std::exception_ptr exception;
		std::atomic<RequestStatus> status;

		static_assert(std::atomic<RequestStatus>::is_always_lock_free, "RequestStatus is not lock-free.");
	};
}

namespace PonyEngine::File
{
	Request::Request() noexcept :
		byteCount{0uz},
		status{RequestStatus::Pending}
	{
	}

	RequestStatus Request::Status() const noexcept
	{
		return status.load(std::memory_order::acquire);
	}

	std::size_t Request::ByteCount() const
	{
#ifndef NDEBUG
		if (status.load(std::memory_order::acquire) != RequestStatus::Success) [[unlikely]]
		{
			throw std::logic_error("Invalid status");
		}
#endif

		return byteCount;
	}

	const std::exception_ptr& Request::Exception() const
	{
#ifndef NDEBUG
		if (status.load(std::memory_order::acquire) != RequestStatus::Failed) [[unlikely]]
		{
			throw std::logic_error("Invalid status");
		}
#endif

		return exception;
	}

	void Request::SetSuccess(const std::size_t byteCount) noexcept
	{
		assert(status.load(std::memory_order::relaxed) == RequestStatus::Pending && "Invalid status.");

		this->byteCount = byteCount;
		status.store(RequestStatus::Success, std::memory_order::release);
	}

	void Request::SetFailed(const std::exception_ptr& exception) noexcept
	{
		assert(status.load(std::memory_order::relaxed) == RequestStatus::Pending && "Invalid status.");
		
		this->exception = exception;
		status.store(RequestStatus::Failed, std::memory_order::release);
	}

	void Request::Wait() const noexcept
	{
		while (status.load(std::memory_order::acquire) == RequestStatus::Pending)
		{
			status.wait(RequestStatus::Pending, std::memory_order::acquire);
		}
	}
}
