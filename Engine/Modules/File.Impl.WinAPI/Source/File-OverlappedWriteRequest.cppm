/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>

export module PonyEngine.File.Impl.WinAPI:OverlappedWriteRequest;

import std;

import PonyEngine.File.Impl;

import :OverlappedUtility;

export namespace PonyEngine::File
{
	/// @brief Overlapped write request.
	class OverlappedWriteRequest final : public WriteRequest
	{
	public:
		/// @brief Creates an overlapped write request.
		/// @param params Write parameters.
		/// @param callback Callback.
		/// @param file File that created this request.
		[[nodiscard("Pure constructor")]]
		OverlappedWriteRequest(const WriteParams& params, std::move_only_function<void(const IWriteRequest&) noexcept> callback, HANDLE file) noexcept;
		OverlappedWriteRequest(const OverlappedWriteRequest&) = delete;
		OverlappedWriteRequest(OverlappedWriteRequest&&) = delete;

		virtual ~OverlappedWriteRequest() noexcept override = default;

		virtual void Cancel() override;

		[[nodiscard("Pure function")]]
		OVERLAPPED& Overlapped() noexcept;
		[[nodiscard("Pure function")]]
		const OVERLAPPED& Overlapped() const noexcept;

		OverlappedWriteRequest& operator =(const OverlappedWriteRequest&) = delete;
		OverlappedWriteRequest& operator =(OverlappedWriteRequest&&) = delete;

	private:
		HANDLE file; ///< File that created this request.
		OVERLAPPED overlapped; ///< Overlapped.
	};
}

namespace PonyEngine::File
{
	OverlappedWriteRequest::OverlappedWriteRequest(const WriteParams& params, std::move_only_function<void(const IWriteRequest&) noexcept> callback, const HANDLE file) noexcept :
		WriteRequest(params, std::move(callback)),
		file(file),
		overlapped(CreateOverlapped(params.offset))
	{
	}

	void OverlappedWriteRequest::Cancel()
	{
		if (!CancelIoEx(file, &overlapped)) [[unlikely]]
		{
			if (const DWORD error = GetLastError(); error != ERROR_NOT_FOUND) [[unlikely]]
			{
				throw std::runtime_error(std::format("Failed to cancel file request: Error code = '0x{:X}'", error));
			}
		}
	}

	OVERLAPPED& OverlappedWriteRequest::Overlapped() noexcept
	{
		return overlapped;
	}

	const OVERLAPPED& OverlappedWriteRequest::Overlapped() const noexcept
	{
		return overlapped;
	}
}
