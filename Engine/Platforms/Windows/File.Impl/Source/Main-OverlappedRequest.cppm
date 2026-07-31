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
	class OverlappedRequest final
	{
	public:
		/// @brief Creates a read request.
		/// @param params Read parameters.
		/// @param callback Read request callback.
		[[nodiscard("Pure constructor")]]
		explicit OverlappedRequest(const ReadParams& params, const std::function<void(const IReadRequest&)>& callback) noexcept;
		/// @brief Creates a write request.
		/// @param params Write parameters.
		/// @param callback Write request callback.
		[[nodiscard("Pure constructor")]]
		explicit OverlappedRequest(const WriteParams& params, const std::function<void(const IWriteRequest&)>& callback) noexcept;
		OverlappedRequest(const OverlappedRequest&) = delete;
		OverlappedRequest(OverlappedRequest&&) = delete;

		~OverlappedRequest() noexcept = default;

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

		OverlappedRequest& operator =(const OverlappedRequest&) = delete;
		OverlappedRequest& operator =(OverlappedRequest&&) = delete;

	private:
		OVERLAPPED overlapped; ///< Overlapped.
		RequestVariant request; ///< Request.
	};
}

namespace PonyEngine::File
{
	OverlappedRequest::OverlappedRequest(const ReadParams& params, const std::function<void(const IReadRequest&)>& callback) noexcept :
		overlapped{CreateOverlapped(params.offset)},
		request(params, callback)
	{
	}

	OverlappedRequest::OverlappedRequest(const WriteParams& params, const std::function<void(const IWriteRequest&)>& callback) noexcept :
		overlapped{CreateOverlapped(params.offset)},
		request(params, callback)
	{
	}

	OVERLAPPED& OverlappedRequest::Overlapped() noexcept
	{
		static_assert(offsetof(OverlappedRequest, overlapped) == 0, "Invalid overlapped placement.");
		return overlapped;
	}

	const OVERLAPPED& OverlappedRequest::Overlapped() const noexcept
	{
		static_assert(offsetof(OverlappedRequest, overlapped) == 0, "Invalid overlapped placement.");
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
}
