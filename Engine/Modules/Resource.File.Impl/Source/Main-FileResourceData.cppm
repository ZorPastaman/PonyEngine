/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Resource.File.Impl:FileResourceData;

import std;

import PonyEngine.Resource.Ext;

export namespace PonyEngine::Resource::File
{
	/// @brief File resource data.
	class FileResourceData final : public IFileResourceData
	{
	public:
		/// @brief Creates a file resource data.
		/// @param filePath File path.
		[[nodiscard("Pure constructor")]]
		explicit FileResourceData(const std::filesystem::path* filePath);
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
		const std::filesystem::path* filePath; ///< File path.
		std::size_t size; ///< File size.
	};
}

namespace PonyEngine::Resource::File
{
	FileResourceData::FileResourceData(const std::filesystem::path* const filePath) :
		filePath{filePath},
		size{static_cast<std::size_t>(std::filesystem::file_size(*this->filePath))}
	{
	}

	const std::filesystem::path& FileResourceData::Path() const noexcept
	{
		return *filePath;
	}

	std::size_t FileResourceData::Offset() const noexcept
	{
		return 0uz;
	}

	std::size_t FileResourceData::Size() const noexcept
	{
		return size;
	}
}
