/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Platform/Windows/Framework.h"

export module PonyEngine.File.Impl.Windows:OverlappedRequest;

import std;

import PonyEngine.File.Impl;
import PonyEngine.Type;

import :OverlappedReadRequest;
import :OverlappedWriteRequest;

export namespace PonyEngine::File
{
	/// @brief File request with the @p OVERLAPPED structure.
	class OverlappedRequest final
	{
	public:
		/// @brief Creates a read request.
		/// @param params Read parameters.
		/// @param callback Callback.
		/// @param file File that created this request.
		[[nodiscard("Pure constructor")]]
		explicit OverlappedRequest(const ReadParams& params, std::move_only_function<void(const IReadRequest&)> callback, HANDLE file) noexcept;
		/// @brief Creates a write request.
		/// @param params Write parameters.
		/// @param callback Callback.
		/// @param file File that created this request.
		[[nodiscard("Pure constructor")]]
		explicit OverlappedRequest(const WriteParams& params, std::move_only_function<void(const IWriteRequest&)> callback, HANDLE file) noexcept;
		OverlappedRequest(const OverlappedRequest&) = delete;
		OverlappedRequest(OverlappedRequest&&) = delete;

		~OverlappedRequest() noexcept = default;

		[[nodiscard("Pure function")]]
		bool IsRead() const noexcept;
		[[nodiscard("Pure function")]]
		bool IsWrite() const noexcept;

		[[nodiscard("Pure function")]]
		OverlappedReadRequest& Read() noexcept;
		[[nodiscard("Pure function")]]
		const OverlappedReadRequest& Read() const noexcept;

		[[nodiscard("Pure function")]]
		OverlappedWriteRequest& Write() noexcept;
		[[nodiscard("Pure function")]]
		const OverlappedWriteRequest& Write() const noexcept;

		/// @brief Gets the overlapped.
		/// @return Overlapped.
		[[nodiscard("Pure function")]]
		OVERLAPPED& Overlapped() noexcept;
		/// @brief Gets the overlapped.
		/// @return Overlapped.
		[[nodiscard("Pure function")]]
		const OVERLAPPED& Overlapped() const noexcept;

		/// @brief Sets the status to success.
		/// @param byteCount Transferred byte count.
		void SetSuccess(std::size_t byteCount) noexcept;
		/// @brief Sets the status to failure.
		/// @param exception Exception that occured during the request execution.
		void SetFailure(const std::exception_ptr& exception) noexcept;
		/// @brief Sets the status to canceled.
		void SetCanceled() noexcept;

		OverlappedRequest& operator =(const OverlappedRequest&) = delete;
		OverlappedRequest& operator =(OverlappedRequest&&) = delete;

	private:
		std::variant<OverlappedReadRequest, OverlappedWriteRequest> request;
	};
}

namespace PonyEngine::File
{
	OverlappedRequest::OverlappedRequest(const ReadParams& params, std::move_only_function<void(const IReadRequest&)> callback, const HANDLE file) noexcept :
		request(std::in_place_type<OverlappedReadRequest>, params, std::move(callback), file)
	{
	}

	OverlappedRequest::OverlappedRequest(const WriteParams& params, std::move_only_function<void(const IWriteRequest&)> callback, const HANDLE file) noexcept :
		request(std::in_place_type<OverlappedWriteRequest>, params, std::move(callback), file)
	{
	}

	bool OverlappedRequest::IsRead() const noexcept
	{
		return std::holds_alternative<OverlappedReadRequest>(request);
	}

	bool OverlappedRequest::IsWrite() const noexcept
	{
		return std::holds_alternative<OverlappedWriteRequest>(request);
	}

	OverlappedReadRequest& OverlappedRequest::Read() noexcept
	{
		return std::get<OverlappedReadRequest>(request);
	}

	const OverlappedReadRequest& OverlappedRequest::Read() const noexcept
	{
		return std::get<OverlappedReadRequest>(request);
	}

	OverlappedWriteRequest& OverlappedRequest::Write() noexcept
	{
		return std::get<OverlappedWriteRequest>(request);
	}

	const OverlappedWriteRequest& OverlappedRequest::Write() const noexcept
	{
		return std::get<OverlappedWriteRequest>(request);
	}

	OVERLAPPED& OverlappedRequest::Overlapped() noexcept
	{
		return std::visit<OVERLAPPED&>(Type::Overload
		{
			[](OverlappedReadRequest& readRequest) -> OVERLAPPED&
			{
				return readRequest.Overlapped();
			},
			[](OverlappedWriteRequest& writeRequest) -> OVERLAPPED&
			{
				return writeRequest.Overlapped();
			}
		}, request);
	}

	const OVERLAPPED& OverlappedRequest::Overlapped() const noexcept
	{
		return std::visit<const OVERLAPPED&>(Type::Overload
		{
			[](const OverlappedReadRequest& readRequest) -> const OVERLAPPED&
			{
				return readRequest.Overlapped();
			},
			[](const OverlappedWriteRequest& writeRequest) -> const OVERLAPPED&
			{
				return writeRequest.Overlapped();
			}
		}, request);
	}

	void OverlappedRequest::SetSuccess(const std::size_t byteCount) noexcept
	{
		std::visit(Type::Overload
		{
			[&](OverlappedReadRequest& readRequest)
			{
				readRequest.SetSuccess(byteCount);
			},
			[&](OverlappedWriteRequest& writeRequest)
			{
				writeRequest.SetSuccess(byteCount);
			}
		}, request);
	}

	void OverlappedRequest::SetFailure(const std::exception_ptr& exception) noexcept
	{
		std::visit(Type::Overload
		{
			[&](OverlappedReadRequest& readRequest)
			{
				readRequest.SetFailure(exception);
			},
			[&](OverlappedWriteRequest& writeRequest)
			{
				writeRequest.SetFailure(exception);
			}
		}, request);
	}

	void OverlappedRequest::SetCanceled() noexcept
	{
		std::visit(Type::Overload
		{
			[](ReadRequest& readRequest)
			{
				readRequest.SetCanceled();
			},
			[](WriteRequest& writeRequest)
			{
				writeRequest.SetCanceled();
			}
		}, request);
	}
}
