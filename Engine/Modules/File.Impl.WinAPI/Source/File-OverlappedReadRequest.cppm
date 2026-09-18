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

export module PonyEngine.File.Impl.WinAPI:OverlappedReadRequest;

import std;

import PonyEngine.File.Impl;

import :OverlappedUtility;

export namespace PonyEngine::File
{
	/// @brief Overlapped read request.
	class OverlappedReadRequest final : public ReadRequest
	{
	public:
		/// @brief Creates an overlapped read request.
		/// @param params Read parameters.
		/// @param callback Callback.
		/// @param file File that created this request.
		[[nodiscard("Pure constructor")]]
		OverlappedReadRequest(const ReadParams& params, std::move_only_function<void(const IReadRequest&) noexcept> callback, HANDLE file) noexcept;
		OverlappedReadRequest(const OverlappedReadRequest&) = delete;
		OverlappedReadRequest(OverlappedReadRequest&&) = delete;

		virtual ~OverlappedReadRequest() noexcept override = default;

		virtual void Cancel() override;

		[[nodiscard("Pure function")]]
		OVERLAPPED& Overlapped() noexcept;
		[[nodiscard("Pure function")]]
		const OVERLAPPED& Overlapped() const noexcept;

		OverlappedReadRequest& operator =(const OverlappedReadRequest&) = delete;
		OverlappedReadRequest& operator =(OverlappedReadRequest&&) = delete;

	private:
		HANDLE file; ///< File that created this request.
		OVERLAPPED overlapped; ///< Overlapped.
	};
}

namespace PonyEngine::File
{
	OverlappedReadRequest::OverlappedReadRequest(const ReadParams& params, std::move_only_function<void(const IReadRequest&) noexcept> callback, const HANDLE file) noexcept :
		ReadRequest(params, std::move(callback)),
		file(file),
		overlapped(CreateOverlapped(params.offset))
	{
	}

	void OverlappedReadRequest::Cancel()
	{
		if (!CancelIoEx(file, &overlapped)) [[unlikely]]
		{
			if (const DWORD error = GetLastError(); error != ERROR_NOT_FOUND) [[unlikely]]
			{
				throw std::runtime_error(std::format("Failed to cancel file request: Error code = '0x{:X}'", error));
			}
		}
	}

	OVERLAPPED& OverlappedReadRequest::Overlapped() noexcept
	{
		return overlapped;
	}

	const OVERLAPPED& OverlappedReadRequest::Overlapped() const noexcept
	{
		return overlapped;
	}
}
