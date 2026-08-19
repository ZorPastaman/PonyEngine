/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Resource.Pack.Impl:FileDataAccess;

import std;

import PonyEngine.File;
import PonyEngine.Resource.Ext;

export namespace PonyEngine::Resource::Pack
{
	class FileDataAccess final : public IFileDataAccess
	{
	public:
		[[nodiscard("Pure constructor")]]
		FileDataAccess(const std::filesystem::path& path, std::size_t offset, std::size_t size) noexcept;
		[[nodiscard("Pure constructor")]]
		FileDataAccess(const FileDataAccess& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		FileDataAccess(FileDataAccess&& other) noexcept = default;

		~FileDataAccess() noexcept = default;

		[[nodiscard("Pure function")]] 
		virtual const std::filesystem::path& Path() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual std::size_t Offset() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual std::size_t Size() const noexcept override;

		FileDataAccess& operator =(const FileDataAccess& other) noexcept = default;
		FileDataAccess& operator =(FileDataAccess&& other) noexcept = default;

	private:
		std::filesystem::path path;
		std::size_t offset;
		std::size_t size;
	};
}

namespace PonyEngine::Resource::Pack
{
	FileDataAccess::FileDataAccess(const std::filesystem::path& path, const std::size_t offset, const std::size_t size) noexcept :
		path(path),
		offset{offset},
		size{size}
	{
	}

	const std::filesystem::path& FileDataAccess::Path() const noexcept
	{
		return path;
	}

	std::size_t FileDataAccess::Offset() const noexcept
	{
		return offset;
	}

	std::size_t FileDataAccess::Size() const noexcept
	{
		return size;
	}
}
