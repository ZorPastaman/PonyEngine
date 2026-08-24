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

export module PonyEngine.Resource.Pack.Impl:MemoryLoadableDataAccess;

import std;

import PonyEngine.Math;
import PonyEngine.Resource.Ext;

import :LoadableDataAccessRequest;
import :LoadableDataAccessRequestWorker;

export namespace PonyEngine::Resource::Pack
{
	class MemoryLoadableDataAccess final : public ILoadableDataAccess
	{
	public:
		[[nodiscard("Pure constructor")]]
		MemoryLoadableDataAccess(LoadableDataAccessRequestWorker& worker, const std::shared_ptr<const std::byte[]>& loadedData, std::size_t offset, std::size_t size) noexcept;
		MemoryLoadableDataAccess(const MemoryLoadableDataAccess&) = delete;
		MemoryLoadableDataAccess(MemoryLoadableDataAccess&&) = delete;

		~MemoryLoadableDataAccess() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual std::size_t Size() const noexcept override;

		[[nodiscard("Must be used")]]
		virtual std::shared_ptr<ILoadableDataAccessRequest> Load(const LoadParams& params,
			std::move_only_function<void(const ILoadableDataAccessRequest&) noexcept> callback) override;

		MemoryLoadableDataAccess& operator =(const MemoryLoadableDataAccess&) = delete;
		MemoryLoadableDataAccess& operator =(MemoryLoadableDataAccess&&) = delete;

	private:
		LoadableDataAccessRequestWorker* worker;

		std::shared_ptr<const std::byte[]> loadedData;
		std::span<const std::byte> buffer;
	};
}

namespace PonyEngine::Resource::Pack
{
	MemoryLoadableDataAccess::MemoryLoadableDataAccess(LoadableDataAccessRequestWorker& worker, const std::shared_ptr<const std::byte[]>& loadedData, 
		const std::size_t offset, const std::size_t size) noexcept :
		worker{&worker},
		loadedData(loadedData),
		buffer(&loadedData[offset], size)
	{
		assert(this->worker && "Worker is nullptr.");
		assert(this->loadedData && "Data is nullptr.");
	}

	std::size_t MemoryLoadableDataAccess::Size() const noexcept
	{
		return buffer.size();
	}

	std::shared_ptr<ILoadableDataAccessRequest> MemoryLoadableDataAccess::Load(const LoadParams& params,
		std::move_only_function<void(const ILoadableDataAccessRequest&) noexcept> callback)
	{
		return worker->CreateRequest(loadedData, buffer, params, std::move(callback));
	}
}
