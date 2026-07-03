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

import PonyEngine.File;
import PonyEngine.Resource.Ext;

export namespace PonyEngine::Resource::Pack
{
	class PackFileResourceData final : public IFileResourceData
	{
	public:
		[[nodiscard("Pure constructor")]]
		PackFileResourceData(const File::IFile* pack, std::size_t offset, std::size_t size);
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
		const File::IFile* pack;
		std::size_t offset;
		std::size_t size;
	};
}

namespace PonyEngine::Resource::Pack
{
	PackFileResourceData::PackFileResourceData(const File::IFile* const pack, const std::size_t offset, const std::size_t size) :
		pack{pack},
		offset{offset},
		size{size}
	{
	}

	const std::filesystem::path& PackFileResourceData::Path() const noexcept
	{
		return pack->Path();
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
