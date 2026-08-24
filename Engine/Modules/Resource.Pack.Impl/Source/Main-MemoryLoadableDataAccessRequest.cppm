/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Resource.Pack.Impl:MemoryLoadableDataAccessRequest;

import std;

import :LoadableDataAccessRequest;

export namespace PonyEngine::Resource::Pack
{
	class MemoryLoadableDataAccessRequest final : public LoadableDataAccessRequest
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit MemoryLoadableDataAccessRequest(const std::shared_ptr<const std::byte[]>& loadedData, const LoadParams& params,
			std::move_only_function<void(const ILoadableDataAccessRequest&) noexcept> callback) noexcept;
		MemoryLoadableDataAccessRequest(const MemoryLoadableDataAccessRequest&) = delete;
		MemoryLoadableDataAccessRequest(MemoryLoadableDataAccessRequest&&) = delete;

		virtual ~MemoryLoadableDataAccessRequest() noexcept override = default;

		MemoryLoadableDataAccessRequest& operator =(const MemoryLoadableDataAccessRequest&) = delete;
		MemoryLoadableDataAccessRequest& operator =(MemoryLoadableDataAccessRequest&&) = delete;

	private:
		std::shared_ptr<const std::byte[]> loadedData;
	};
}

namespace PonyEngine::Resource::Pack
{
	MemoryLoadableDataAccessRequest::MemoryLoadableDataAccessRequest(const std::shared_ptr<const std::byte[]>& loadedData, const LoadParams& params,
		std::move_only_function<void(const ILoadableDataAccessRequest&) noexcept> callback) noexcept :
		LoadableDataAccessRequest(params, std::move(callback)),
		loadedData(loadedData)
	{
	}
}
