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

import :OverlappedUtility;

export namespace PonyEngine::File
{
	/// @brief File request with the @p OVERLAPPED structure.
	class OverlappedRequest final : private IRequestController
	{
	public:
		/// @brief Creates a read request.
		/// @param fileHandle File handle.
		/// @param file File that created this request.
		/// @param params Read parameters.
		[[nodiscard("Pure constructor")]]
		explicit OverlappedRequest(HANDLE fileHandle, std::shared_ptr<IFile>&& file, const ReadParams& params);
		/// @brief Creates a write request.
		/// @param fileHandle File handle.
		/// @param file File that created this request.
		/// @param params Write parameters.
		[[nodiscard("Pure constructor")]]
		explicit OverlappedRequest(HANDLE fileHandle, std::shared_ptr<IFile>&& file, const WriteParams& params);
		OverlappedRequest(const OverlappedRequest&) = delete;
		OverlappedRequest(OverlappedRequest&&) = delete;

		~OverlappedRequest() noexcept = default;

		/// @brief Gets the overlapped.
		/// @return Overlapped.
		[[nodiscard("Pure function")]]
		OVERLAPPED& Overlapped() noexcept;
		/// @brief Gets the overlapped.
		/// @return Overlapped.
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

		OverlappedRequest& operator =(const OverlappedRequest&) = delete;
		OverlappedRequest& operator =(OverlappedRequest&&) = delete;

	private:
		virtual void Cancel() override;

		OVERLAPPED overlapped; ///< Overlapped.
		RequestVariant request; ///< Request.
		HANDLE fileHandle; ///< File handle.
		std::shared_ptr<IFile> file; ///< File that created this request.
	};
}

namespace PonyEngine::File
{
	OverlappedRequest::OverlappedRequest(const HANDLE fileHandle, std::shared_ptr<IFile>&& file, const ReadParams& params) :
		overlapped{CreateOverlapped(params.offset)},
		request(*this, params),
		fileHandle(fileHandle),
		file(std::move(file))
	{
	}

	OverlappedRequest::OverlappedRequest(const HANDLE fileHandle, std::shared_ptr<IFile>&& file, const WriteParams& params) :
		overlapped{CreateOverlapped(params.offset)},
		request(*this, params),
		fileHandle(fileHandle),
		file(std::move(file))
	{
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

	void OverlappedRequest::Cancel()
	{
		if (!CancelIoEx(fileHandle, &overlapped)) [[unlikely]]
		{
			if (const DWORD error = GetLastError(); error != ERROR_NOT_FOUND) [[unlikely]]
			{
				throw std::runtime_error(std::format("Failed to cancel file request: Error code = '0x{:X}'", error));
			}
		}
	}
}
