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

export module PonyEngine.Resource.Pack.Impl:MemoryLoadableDataAccessRequest;

import std;

import PonyEngine.Job;

import :LoadableDataAccessRequest;

export namespace PonyEngine::Resource::Pack
{
	class MemoryLoadableDataAccessRequest final : public LoadableDataAccessRequest
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit MemoryLoadableDataAccessRequest(std::move_only_function<void(const ILoadableDataAccessRequest&) noexcept> callback) noexcept;

		virtual ~MemoryLoadableDataAccessRequest() noexcept override = default;

	private:
		std::shared_ptr<>
	};
}

namespace PonyEngine::Resource::Pack
{
	MemoryLoadableDataAccessRequest::MemoryLoadableDataAccessRequest(std::move_only_function<void(const ILoadableDataAccessRequest&) noexcept> callback) noexcept :
		LoadableDataAccessRequest(std::move(callback))
	{
	}

	void MemoryLoadableDataAccessRequest::Cancel()
	{
		memoryRequest->Cancel();
	}

	void MemoryLoadableDataAccessRequest::MemoryRequest(std::shared_ptr<Memory::IReadRequest>&& memoryRequest) noexcept
	{
		this->memoryRequest = std::move(memoryRequest);
	}
}
