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
		FileRequestStatus Status() const noexcept;
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
		void SetFailed(const std::exception_ptr& exception) noexcept;
		/// @brief Sets the status to canceled.
		void SetCanceled() noexcept;
		
		/// @brief Makes the thread sleep till the request is completed with success or failure.
		void Wait() const noexcept;

		Request& operator =(const Request&) = delete;
		Request& operator =(Request&&) = delete;

	private:
		std::size_t byteCount; ///< Transferred byte count.
		std::exception_ptr exception; ///< Exception that occured during the request execution.
		std::atomic<FileRequestStatus> status; ///< Request status.

		static_assert(std::atomic<FileRequestStatus>::is_always_lock_free, "FileRequestStatus is not lock-free.");
	};
}

namespace PonyEngine::File
{
	Request::Request() noexcept :
		byteCount{0uz},
		status(FileRequestStatus::Pending)
	{
	}

	FileRequestStatus Request::Status() const noexcept
	{
		return status.load(std::memory_order::acquire);
	}

	std::size_t Request::ByteCount() const
	{
		if (status.load(std::memory_order::acquire) != FileRequestStatus::Success) [[unlikely]]
		{
			throw std::logic_error("Invalid status");
		}

		return byteCount;
	}

	const std::exception_ptr& Request::Exception() const
	{
		if (status.load(std::memory_order::acquire) != FileRequestStatus::Failure) [[unlikely]]
		{
			throw std::logic_error("Invalid status");
		}

		return exception;
	}

	void Request::SetSuccess(const std::size_t byteCount) noexcept
	{
		assert(status.load(std::memory_order::relaxed) == FileRequestStatus::Pending && "Invalid status.");

		this->byteCount = byteCount;
		status.store(FileRequestStatus::Success, std::memory_order::release);
		status.notify_all();
	}

	void Request::SetFailed(const std::exception_ptr& exception) noexcept
	{
		assert(status.load(std::memory_order::relaxed) == FileRequestStatus::Pending && "Invalid status.");
		
		this->exception = exception;
		status.store(FileRequestStatus::Failure, std::memory_order::release);
		status.notify_all();
	}

	void Request::SetCanceled() noexcept
	{
		assert(status.load(std::memory_order::relaxed) == FileRequestStatus::Pending && "Invalid status.");
		status.store(FileRequestStatus::Canceled, std::memory_order::release);
		status.notify_all();
	}

	void Request::Wait() const noexcept
	{
		while (status.load(std::memory_order::acquire) == FileRequestStatus::Pending)
		{
			status.wait(FileRequestStatus::Pending, std::memory_order::acquire);
		}
	}
}
