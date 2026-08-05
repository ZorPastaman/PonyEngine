/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <cstddef>

#include "PonyEngine/Platform/Windows/Framework.h"

export module PonyEngine.File.Impl.Windows:OverlappedRequest;

import std;

import PonyEngine.File.Impl;

import :FileContext;
import :OverlappedUtility;

export namespace PonyEngine::File
{
	/// @brief File request with the @p OVERLAPPED structure.
	class OverlappedRequest final : private IRequestController
	{
	public:
		/// @brief Creates a read request.
		/// @param fileContext File context.
		/// @param params Read parameters.
		/// @param handler Request handler. Can be nullptr.
		[[nodiscard("Pure constructor")]]
		explicit OverlappedRequest(const FileContext& fileContext, const ReadParams& params, IReadHandler* handler);
		/// @brief Creates a write request.
		/// @param fileContext File context.
		/// @param params Write parameters.
		/// @param handler Request handler. Can be nullptr.
		[[nodiscard("Pure constructor")]]
		explicit OverlappedRequest(const FileContext& fileContext, const WriteParams& params, IWriteHandler* handler);
		OverlappedRequest(const OverlappedRequest&) = delete;
		OverlappedRequest(OverlappedRequest&&) = delete;

		~OverlappedRequest() noexcept;

		/// @brief Gets the overlapped offset.
		/// @return Overlapped offset.
		[[nodiscard("Pure function")]]
		static std::size_t OverlappedOffset() noexcept;
		/// @brief Gets the overlapped.
		/// @return Overlapped. Guaranteed to be a member with the offset 0.
		[[nodiscard("Pure function")]]
		OVERLAPPED& Overlapped() noexcept;
		/// @brief Gets the overlapped.
		/// @return Overlapped. Guaranteed to be a member with the offset 0.
		[[nodiscard("Pure function")]]
		const OVERLAPPED& Overlapped() const noexcept;
		/// @brief Gets the request.
		/// @return Request.
		[[nodiscard("Pure function")]]
		RequestVariant& Request() noexcept;
		/// @brief Gets the request.
		/// @return Request.
		[[nodiscard("Pure function")]]
		const RequestVariant& Request() const noexcept;

		/// @brief Casts the overlapped to its overlapped request.
		/// @param overlapped Overlapped.
		/// @return Overlapped request.
		[[nodiscard("Pure function")]]
		static OverlappedRequest& ToRequest(OVERLAPPED& overlapped) noexcept;
		/// @brief Casts the overlapped to its overlapped request.
		/// @param overlapped Overlapped.
		/// @return Overlapped request.
		[[nodiscard("Pure function")]]
		static const OverlappedRequest& ToRequest(const OVERLAPPED& overlapped) noexcept;

		OverlappedRequest& operator =(const OverlappedRequest&) = delete;
		OverlappedRequest& operator =(OverlappedRequest&&) = delete;

	private:
		virtual void Cancel() override;

		OVERLAPPED overlapped; ///< Overlapped.
		const FileContext* fileContext; ///< File context.
		RequestVariant request; ///< Request.
	};
}

namespace PonyEngine::File
{
	OverlappedRequest::OverlappedRequest(const FileContext& fileContext, const ReadParams& params, IReadHandler* const handler) :
		overlapped{CreateOverlapped(params.offset)},
		fileContext{&fileContext},
		request(*this, params, handler)
	{
		try
		{
			if (params.buffer.size() > std::numeric_limits<DWORD>::max()) [[unlikely]]
			{
				throw std::invalid_argument("Too great buffer");
			}

			if (ReadFile(this->fileContext->FileHandle(), params.buffer.data(), static_cast<DWORD>(params.buffer.size()), nullptr, &overlapped)) [[unlikely]]
			{
				DWORD bytesTransferred = 0;
				if (GetOverlappedResult(this->fileContext->FileHandle(), &overlapped, &bytesTransferred, FALSE)) [[likely]]
				{
					request.SetSuccess(static_cast<std::size_t>(bytesTransferred));
				}
				else [[unlikely]]
				{
					throw std::runtime_error(std::format("Failed to create file read request: Error code = '0x{:X}'", GetLastError()));
				}
			}
			else [[likely]]
			{
				if (const DWORD error = GetLastError(); error != ERROR_IO_PENDING) [[unlikely]]
				{
					throw std::runtime_error(std::format("Failed to create file read request: Error code = '0x{:X}'", error));
				}
			}
		}
		catch (...)
		{
			request.SetCanceled();
			throw;
		}

		this->fileContext->IncrementRequestCount();
	}

	OverlappedRequest::OverlappedRequest(const FileContext& fileContext, const WriteParams& params, IWriteHandler* const handler) :
		overlapped{CreateOverlapped(params.offset)},
		fileContext{&fileContext},
		request(*this, params, handler)
	{
		try
		{
			if (params.buffer.size() > std::numeric_limits<DWORD>::max()) [[unlikely]]
			{
				throw std::invalid_argument("Too great buffer");
			}

			if (WriteFile(this->fileContext->FileHandle(), params.buffer.data(), static_cast<DWORD>(params.buffer.size()), nullptr, &overlapped)) [[unlikely]]
			{
				DWORD bytesTransferred = 0;
				if (GetOverlappedResult(this->fileContext->FileHandle(), &overlapped, &bytesTransferred, FALSE)) [[likely]]
				{
					request.SetSuccess(static_cast<std::size_t>(bytesTransferred));
				}
				else [[unlikely]]
				{
					throw std::runtime_error(std::format("Failed to create file write request: Error code = '0x{:X}'", GetLastError()));
				}
			}
			else [[likely]]
			{
				if (const DWORD error = GetLastError(); error != ERROR_IO_PENDING) [[unlikely]]
				{
					throw std::runtime_error(std::format("Failed to create file write request: Error code = '0x{:X}'", error));
				}
			}
		}
		catch (...)
		{
			request.SetCanceled();
			throw;
		}

		this->fileContext->IncrementRequestCount();
	}

	OverlappedRequest::~OverlappedRequest() noexcept
	{
		fileContext->DecrementRequestCount();
	}

	std::size_t OverlappedRequest::OverlappedOffset() noexcept
	{
		return offsetof(OverlappedRequest, overlapped);
	}

	OVERLAPPED& OverlappedRequest::Overlapped() noexcept
	{
		return overlapped;
	}

	const OVERLAPPED& OverlappedRequest::Overlapped() const noexcept
	{
		return overlapped;
	}

	RequestVariant& OverlappedRequest::Request() noexcept
	{
		return request;
	}

	const RequestVariant& OverlappedRequest::Request() const noexcept
	{
		return request;
	}

	OverlappedRequest& OverlappedRequest::ToRequest(OVERLAPPED& overlapped) noexcept
	{
		return const_cast<OverlappedRequest&>(ToRequest(const_cast<const OVERLAPPED&>(overlapped)));
	}

	const OverlappedRequest& OverlappedRequest::ToRequest(const OVERLAPPED& overlapped) noexcept
	{
		return *reinterpret_cast<const OverlappedRequest*>(reinterpret_cast<std::uintptr_t>(&overlapped) - OverlappedOffset());
	}

	void OverlappedRequest::Cancel()
	{
		if (!CancelIoEx(fileContext->FileHandle(), &overlapped)) [[unlikely]]
		{
			if (const DWORD error = GetLastError(); error != ERROR_NOT_FOUND) [[unlikely]]
			{
				throw std::runtime_error(std::format("Failed to cancel file request: Error code = '0x{:X}'", error));
			}
		}
	}
}
