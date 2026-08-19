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

export module PonyEngine.File.Impl:ReadRequest;

import std;

import PonyEngine.File;

import :IRequestController;
import :Request;

export namespace PonyEngine::File
{
	/// @brief Read request.
	class ReadRequest final : public IReadRequest
	{
	public:
		/// @brief Creates a read request.
		/// @param controller Request controller.
		/// @param params Read parameters.
		/// @param observer Observer. Can be nullptr.
		[[nodiscard("Pure constructor")]]
		ReadRequest(IRequestController& controller, const ReadParams& params, IReadRequestObserver* observer) noexcept;
		ReadRequest(const ReadRequest&) = delete;
		ReadRequest(ReadRequest&&) = delete;

		~ReadRequest() noexcept = default;

		[[nodiscard("Pure function")]] 
		virtual const ReadParams& Params() const noexcept override;

		[[nodiscard("Pure function")]] 
		virtual FileRequestStatus Status() const noexcept override;
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

		ReadRequest& operator =(const ReadRequest&) = delete;
		ReadRequest& operator =(ReadRequest&&) = delete;

	private:
		IRequestController* controller; ///< Request controller.
		ReadParams params; ///< Read parameters.
		Request request; ///< Read request.

		IReadRequestObserver* observer; ///< Observer.
	};
}

namespace PonyEngine::File
{
	ReadRequest::ReadRequest(IRequestController& controller, const ReadParams& params, IReadRequestObserver* const observer) noexcept :
		controller{&controller},
		params(params),
		observer{observer}
	{
	}

	const ReadParams& ReadRequest::Params() const noexcept
	{
		return params;
	}

	FileRequestStatus ReadRequest::Status() const noexcept
	{
		return request.Status();
	}

	std::size_t ReadRequest::ByteCount() const
	{
		return request.ByteCount();
	}

	const std::exception_ptr& ReadRequest::Exception() const
	{
		return request.Exception();
	}

	void ReadRequest::Cancel()
	{
		controller->Cancel();
	}

	void ReadRequest::Wait() const noexcept
	{
		request.Wait();
	}

	void ReadRequest::SetSuccess(const std::size_t byteCount) noexcept
	{
		request.SetSuccess(byteCount);
		
		if (observer)
		{
			observer->OnSuccess(byteCount);
		}
	}

	void ReadRequest::SetFailure(const std::exception_ptr& exception) noexcept
	{
		request.SetFailed(exception);
		
		if (observer)
		{
			observer->OnFailure(exception);
		}
	}

	void ReadRequest::SetCanceled() noexcept
	{
		request.SetCanceled();
		
		if (observer)
		{
			observer->OnCancel();
		}
	}
}
