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

import :OverlappedUtility;

export namespace PonyEngine::File::Windows
{
	class OverlappedRequest final
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit OverlappedRequest(const ReadParams& params, const std::function<void(const IReadRequest&)>& callback) noexcept;
		[[nodiscard("Pure constructor")]]
		explicit OverlappedRequest(const WriteParams& params, const std::function<void(const IWriteRequest&)>& callback) noexcept;
		OverlappedRequest(const OverlappedRequest&) = delete;
		OverlappedRequest(OverlappedRequest&&) = delete;

		~OverlappedRequest() noexcept = default;

		[[nodiscard("Pure function")]]
		OVERLAPPED& Overlapped() noexcept;
		[[nodiscard("Pure function")]]
		const OVERLAPPED& Overlapped() const noexcept;
		[[nodiscard("Pure function")]]
		RequestVariant& Request() noexcept;
		[[nodiscard("Pure function")]]
		const RequestVariant& Request() const noexcept;

		OverlappedRequest& operator =(const OverlappedRequest&) = delete;
		OverlappedRequest& operator =(OverlappedRequest&&) = delete;

	private:
		OVERLAPPED overlapped;
		RequestVariant request;
	};
}

namespace PonyEngine::File::Windows
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
}
