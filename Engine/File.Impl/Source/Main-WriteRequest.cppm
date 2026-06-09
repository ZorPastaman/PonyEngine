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

import :Request;

export namespace PonyEngine::File
{
	class WriteRequest final : public IWriteRequest
	{
	public:
		[[nodiscard("Pure constructor")]]
		WriteRequest(const WriteParams& params, const std::function<void(const IWriteRequest&)>& callback) noexcept;
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

		virtual void Wait() const noexcept override;

		void SetSuccess(std::size_t byteCount) noexcept;
		void SetFailed(const std::exception_ptr& exception) noexcept;

		WriteRequest& operator =(const WriteRequest&) = delete;
		WriteRequest& operator =(WriteRequest&&) = delete;

	private:
		void InvokeCallback() const;

		WriteParams params;
		Request request;
		std::function<void(const IWriteRequest&)> callback;
	};
}

namespace PonyEngine::File
{
	WriteRequest::WriteRequest(const WriteParams& params, const std::function<void(const IWriteRequest&)>& callback) noexcept :
		params(params),
		callback(callback)
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

	void WriteRequest::Wait() const noexcept
	{
		request.Wait();
	}

	void WriteRequest::SetSuccess(const std::size_t byteCount) noexcept
	{
		request.SetSuccess(byteCount);
		InvokeCallback();
	}

	void WriteRequest::SetFailed(const std::exception_ptr& exception) noexcept
	{
		request.SetFailed(exception);
		InvokeCallback();
	}

	void WriteRequest::InvokeCallback() const
	{
		if (callback)
		{
			callback(*this);
		}
	}
}
