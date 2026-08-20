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

import :Request;

export namespace PonyEngine::File
{
	/// @brief Read request.
	class ReadRequest : public IReadRequest
	{
	public:
		/// @brief Creates a read request.
		/// @param params Read parameters.
		/// @param callback Callback. Can be nullptr.
		[[nodiscard("Pure constructor")]]
		ReadRequest(const ReadParams& params, std::move_only_function<void(const IReadRequest&) noexcept> callback) noexcept;
		ReadRequest(const ReadRequest&) = delete;
		ReadRequest(ReadRequest&&) = delete;

		virtual ~ReadRequest() noexcept = default;

		[[nodiscard("Pure function")]] 
		virtual const ReadParams& Params() const noexcept override;

		[[nodiscard("Pure function")]] 
		virtual FileRequestStatus Status() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual std::size_t ByteCount() const override;
		[[nodiscard("Pure function")]] 
		virtual const std::exception_ptr& Exception() const override;

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
		/// @brief Invokes the callback if it's not nullptr.
		void InvokeCallback() noexcept;

		ReadParams params; ///< Read parameters.
		Request request; ///< Read request.

		std::move_only_function<void(const IReadRequest&) noexcept> callback; ///< Callback.
	};
}

namespace PonyEngine::File
{
	ReadRequest::ReadRequest(const ReadParams& params, std::move_only_function<void(const IReadRequest&) noexcept> callback) noexcept :
		params(params),
		callback(std::move(callback))
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

	void ReadRequest::Wait() const noexcept
	{
		request.Wait();
	}

	void ReadRequest::SetSuccess(const std::size_t byteCount) noexcept
	{
		request.SetSuccess(byteCount);
		InvokeCallback();
	}

	void ReadRequest::SetFailure(const std::exception_ptr& exception) noexcept
	{
		request.SetFailed(exception);
		InvokeCallback();
	}

	void ReadRequest::SetCanceled() noexcept
	{
		request.SetCanceled();
		InvokeCallback();
	}

	void ReadRequest::InvokeCallback() noexcept
	{
		if (callback)
		{
			callback(*this);
		}
	}
}
