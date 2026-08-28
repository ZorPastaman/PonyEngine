/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Resource.Pack.Impl:MemoryDataAccess;

import std;

import PonyEngine.Resource.Ext;

export namespace PonyEngine::Resource::Pack
{
	class MemoryDataAccess final : public IMemoryDataAccess
	{
	public:
		[[nodiscard("Pure constructor")]]
		MemoryDataAccess(std::shared_ptr<const std::byte[]> loadedData, std::size_t offset, std::size_t size) noexcept;
		[[nodiscard("Pure constructor")]]
		MemoryDataAccess(const MemoryDataAccess& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		MemoryDataAccess(MemoryDataAccess&& other) noexcept = default;

		~MemoryDataAccess() noexcept = default;

		[[nodiscard("Pure function")]] 
		virtual std::span<const std::byte> Buffer() const noexcept override;

		MemoryDataAccess& operator =(const MemoryDataAccess& other) noexcept = default;
		MemoryDataAccess& operator =(MemoryDataAccess&& other) noexcept = default;

	private:
		std::shared_ptr<const std::byte[]> loadedData;
		std::span<const std::byte> buffer;
	};
}

namespace PonyEngine::Resource::Pack
{
	MemoryDataAccess::MemoryDataAccess(std::shared_ptr<const std::byte[]> loadedData, const std::size_t offset, const std::size_t size) noexcept :
		loadedData(std::move(loadedData)),
		buffer(&this->loadedData[offset], size)
	{
	}

	std::span<const std::byte> MemoryDataAccess::Buffer() const noexcept
	{
		return buffer;
	}
}
