/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Resource.Pack.Impl:PackFileResourceData;

import std;

import PonyEngine.Resource.Ext;

export namespace PonyEngine::Resource::Pack
{
	class PackFileResourceData final : public IFileResourceData
	{
	public:
		[[nodiscard("Pure constructor")]]
		PackFileResourceData(const std::filesystem::path& packPath, std::size_t offset, std::size_t size);
		[[nodiscard("Pure constructor")]]
		PackFileResourceData(const PackFileResourceData& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		PackFileResourceData(PackFileResourceData&& other) noexcept = default;

		~PackFileResourceData() noexcept = default;

		[[nodiscard("Pure function")]] 
		virtual const std::filesystem::path& Path() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual std::size_t Offset() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual std::size_t Size() const noexcept override;

		PackFileResourceData& operator =(const PackFileResourceData& other) noexcept = default;
		PackFileResourceData& operator =(PackFileResourceData&& other) noexcept = default;

	private:
		std::filesystem::path packPath;
		std::size_t offset;
		std::size_t size;
	};
}

namespace PonyEngine::Resource::Pack
{
	PackFileResourceData::PackFileResourceData(const std::filesystem::path& packPath, const std::size_t offset, const std::size_t size) :
		packPath(packPath),
		offset{offset},
		size{size}
	{
		if (std::filesystem::file_size(this->packPath) < this->offset + this->size) [[unlikely]]
		{
			throw std::out_of_range("File out of range");
		}
	}

	const std::filesystem::path& PackFileResourceData::Path() const noexcept
	{
		return packPath;
	}

	std::size_t PackFileResourceData::Offset() const noexcept
	{
		return offset;
	}

	std::size_t PackFileResourceData::Size() const noexcept
	{
		return size;
	}
}
