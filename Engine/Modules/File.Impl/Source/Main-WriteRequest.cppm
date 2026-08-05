/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

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
		/// @param handler Request handler. Can be nullptr.
		[[nodiscard("Pure constructor")]]
		WriteRequest(IRequestController& controller, const WriteParams& params, IWriteHandler* handler) noexcept;
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
		/// @brief Invokes the handler complete if it's not nullptr.
		void InvokeHandlerComplete() const;
		/// @brief Invokes the handler cancel if it's not nullptr.
		void InvokeHandlerCancel() const;

		IRequestController* controller; ///< Request controller.
		WriteParams params; ///< Write parameters.
		Request request; ///< Write request.
		IWriteHandler* handler; ///< Request handler.
	};
}

namespace PonyEngine::File
{
	WriteRequest::WriteRequest(IRequestController& controller, const WriteParams& params, IWriteHandler* const handler) noexcept :
		controller{&controller},
		params(params),
		handler{handler}
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
		InvokeHandlerComplete();
	}

	void WriteRequest::SetFailure(const std::exception_ptr& exception) noexcept
	{
		request.SetFailed(exception);
		InvokeHandlerComplete();
	}

	void WriteRequest::SetCanceled() noexcept
	{
		request.SetCanceled();
		InvokeHandlerCancel();
	}

	void WriteRequest::InvokeHandlerComplete() const
	{
		if (handler)
		{
			handler->OnCompleted(*this);
		}
	}

	void WriteRequest::InvokeHandlerCancel() const
	{
		if (handler)
		{
			handler->OnCanceled(*this);
		}
	}
}
