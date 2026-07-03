/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Resource.File.Impl:FileFileResourceData;

import std;

import PonyEngine.Resource.Ext;

export namespace PonyEngine::Resource::File
{
	class FileFileResourceData final : public IFileResourceData
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit FileFileResourceData(const std::filesystem::path* filePath);
		[[nodiscard("Pure constructor")]]
		FileFileResourceData(const FileFileResourceData& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		FileFileResourceData(FileFileResourceData&& other) noexcept = default;

		~FileFileResourceData() noexcept = default;

		[[nodiscard("Pure function")]] 
		virtual const std::filesystem::path& Path() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual std::size_t Offset() const noexcept override;
		[[nodiscard("Pure function")]]
		virtual std::size_t Size() const noexcept override;

		FileFileResourceData& operator =(const FileFileResourceData& other) noexcept = default;
		FileFileResourceData& operator =(FileFileResourceData&& other) noexcept = default;

	private:
		const std::filesystem::path* filePath;
		std::size_t size;
	};
}

namespace PonyEngine::Resource::File
{
	FileFileResourceData::FileFileResourceData(const std::filesystem::path* const filePath) :
		filePath{filePath},
		size{static_cast<std::size_t>(std::filesystem::file_size(*this->filePath))}
	{
	}

	const std::filesystem::path& FileFileResourceData::Path() const noexcept
	{
		return *filePath;
	}

	std::size_t FileFileResourceData::Offset() const noexcept
	{
		return 0uz;
	}

	std::size_t FileFileResourceData::Size() const noexcept
	{
		return size;
	}
}
