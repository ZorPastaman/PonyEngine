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
import PonyEngine.Memory;
import PonyEngine.Resource.Ext;

import :MemoryLoadableDataAccessRequest;
import :LoadableDataAccessRequestBuffer;

export namespace PonyEngine::Resource::Pack
{
	class MemoryLoadableDataAccess final : public ILoadableDataAccess
	{
	public:
		[[nodiscard("Pure constructor")]]
		MemoryLoadableDataAccess(const std::shared_ptr<const std::byte[]>& loadedData, std::size_t offset, std::size_t size,
			const std::shared_ptr<LoadableDataAccessRequestBuffer>& requestBuffer) noexcept;
		MemoryLoadableDataAccess(const MemoryLoadableDataAccess&) = delete;
		MemoryLoadableDataAccess(MemoryLoadableDataAccess&&) = delete;

		~MemoryLoadableDataAccess() noexcept = default;

		[[nodiscard("Pure function")]]
		virtual std::size_t Size() const noexcept override;

		[[nodiscard("Must be used")]]
		virtual std::shared_ptr<ILoadableDataAccessRequest> Load(std::span<std::byte> buffer, std::size_t offset, ILoadableDataAccessRequestObserver* observer) override;

		MemoryLoadableDataAccess& operator =(const MemoryLoadableDataAccess&) = delete;
		MemoryLoadableDataAccess& operator =(MemoryLoadableDataAccess&&) = delete;

	private:
		std::shared_ptr<const std::byte[]> loadedData;
		std::span<const std::byte> buffer;

		std::shared_ptr<LoadableDataAccessRequestBuffer> requestBuffer;
	};
}

namespace PonyEngine::Resource::Pack
{
	MemoryLoadableDataAccess::MemoryLoadableDataAccess(const std::shared_ptr<const std::byte[]>& loadedData, const std::size_t offset, const std::size_t size,
		const std::shared_ptr<LoadableDataAccessRequestBuffer>& requestBuffer) noexcept :
		loadedData(loadedData),
		buffer(&loadedData[offset], size),
		requestBuffer(requestBuffer)
	{
		assert(this->loadedData && "Data is nullptr.");
		assert(this->requestBuffer && "Request buffer is nullptr.");
	}

	std::size_t MemoryLoadableDataAccess::Size() const noexcept
	{
		return buffer.size();
	}

	std::shared_ptr<ILoadableDataAccessRequest> MemoryLoadableDataAccess::Load(const std::span<std::byte> buffer, const std::size_t offset,
		ILoadableDataAccessRequestObserver* const observer)
	{
		if (Math::SumClamp(buffer.size(), offset) > this->buffer.size()) [[unlikely]]
		{
			throw std::out_of_range("Out of range");
		}

		return requestBuffer->CreateRequest(loadedData, this->buffer.subspan(offset, buffer.size()), buffer, observer);
	}
}
