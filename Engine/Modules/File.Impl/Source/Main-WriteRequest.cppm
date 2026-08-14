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

export module PonyEngine.File.Impl:WriteRequest;

import std;

import PonyEngine.File;

import :IRequestController;
import :Request;

export namespace PonyEngine::File
{
	/// @brief Write request.
	class WriteRequest final : public IWriteRequest
	{
	public:
		/// @brief Creates a write request.
		/// @param controller Request controller.
		/// @param params Write parameters.
		/// @param observer Observer. Can be nullptr.
		[[nodiscard("Pure constructor")]]
		WriteRequest(IRequestController& controller, const WriteParams& params, IWriteRequestObserver* observer) noexcept;
		WriteRequest(const WriteRequest&) = delete;
		WriteRequest(WriteRequest&&) = delete;

		~WriteRequest() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual const WriteParams& Params() const noexcept override;

		[[nodiscard("Pure function")]]
		virtual RequestStatus Status() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::size_t ByteCount() const override;
		[[nodiscard("Pure function")]]
		virtual const std::exception_ptr& Exception() const override;

		virtual void Cancel() override;

		virtual void Wait() const noexcept override;

		/// @brief Sets the status to success.
		/// @param byteCount Transferred byte count.
		void SetSuccess(std::size_t byteCount) noexcept;
		/// @brief Sets the status to failure.
		/// @param exception Exception that occured during the request execution.
		void SetFailure(const std::exception_ptr& exception) noexcept;
		/// @brief Sets the status to canceled.
		void SetCanceled() noexcept;

		WriteRequest& operator =(const WriteRequest&) = delete;
		WriteRequest& operator =(WriteRequest&&) = delete;

	private:
		IRequestController* controller; ///< Request controller.
		WriteParams params; ///< Write parameters.
		Request request; ///< Write request.

		IWriteRequestObserver* observer; ///< Observer.
	};
}

namespace PonyEngine::File
{
	WriteRequest::WriteRequest(IRequestController& controller, const WriteParams& params, IWriteRequestObserver* const observer) noexcept :
		controller{ &controller },
		params(params),
		observer{observer}
	{
	}

	const WriteParams& WriteRequest::Params() const noexcept
	{
		return params;
	}

	RequestStatus WriteRequest::Status() const noexcept
	{
		return request.Status();
	}

	std::size_t WriteRequest::ByteCount() const
	{
		return request.ByteCount();
	}

	const std::exception_ptr& WriteRequest::Exception() const
	{
		return request.Exception();
	}

	void WriteRequest::Cancel()
	{
		controller->Cancel();
	}

	void WriteRequest::Wait() const noexcept
	{
		request.Wait();
	}

	void WriteRequest::SetSuccess(const std::size_t byteCount) noexcept
	{
		request.SetSuccess(byteCount);
		
		if (observer)
		{
			observer->OnSuccess(byteCount);
		}
	}

	void WriteRequest::SetFailure(const std::exception_ptr& exception) noexcept
	{
		request.SetFailed(exception);
		
		if (observer)
		{
			observer->OnFailure(exception);
		}
	}

	void WriteRequest::SetCanceled() noexcept
	{
		request.SetCanceled();
		
		if (observer)
		{
			observer->OnCancel();
		}
	}
}
