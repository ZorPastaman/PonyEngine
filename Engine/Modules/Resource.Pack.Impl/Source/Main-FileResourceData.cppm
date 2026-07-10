/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Resource.Pack.Impl:FileResourceData;

import std;

import PonyEngine.File;
import PonyEngine.Resource.Ext;

export namespace PonyEngine::Resource::Pack
{
	/// @brief File resource data.
	class FileResourceData final : public IFileResourceData
	{
	public:
		/// @brief Creates a file resource data.
		/// @param pack Pack file.
		/// @param offset Resource offset in bytes.
		/// @param size Resource size in bytes.
		[[nodiscard("Pure constructor")]]
		FileResourceData(const File::IFile* pack, std::size_t offset, std::size_t size);
		[[nodiscard("Pure constructor")]]
		FileResourceData(const FileResourceData& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		FileResourceData(FileResourceData&& other) noexcept = default;

		~FileResourceData() noexcept = default;

		[[nodiscard("Pure function")]] 
		virtual const std::filesystem::path& Path() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual std::size_t Offset() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual std::size_t Size() const noexcept override;

		FileResourceData& operator =(const FileResourceData& other) noexcept = default;
		FileResourceData& operator =(FileResourceData&& other) noexcept = default;

	private:
		const File::IFile* pack; ///< Pack file.
		std::size_t offset; ///< Resource offset.
		std::size_t size; ///< Resource size.
	};
}

namespace PonyEngine::Resource::Pack
{
	FileResourceData::FileResourceData(const File::IFile* const pack, const std::size_t offset, const std::size_t size) :
		pack{pack},
		offset{offset},
		size{size}
	{
	}

	const std::filesystem::path& FileResourceData::Path() const noexcept
	{
		return pack->Path();
	}

	std::size_t FileResourceData::Offset() const noexcept
	{
		return offset;
	}

	std::size_t FileResourceData::Size() const noexcept
	{
		return size;
	}
}
