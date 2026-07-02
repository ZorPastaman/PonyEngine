/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Resource.Pack.Impl:PackLoadableResourceData;

import std;

import PonyEngine.File;
import PonyEngine.Resource.Ext;

import :LoadRequestManager;

export namespace PonyEngine::Resource::Pack
{
	class PackLoadableResourceData final : public ILoadableResourceData
	{
	public:
		[[nodiscard("Pure constructor")]]
		PackLoadableResourceData(const LoadRequestManager& loadRequestManager, const std::shared_ptr<File::IFile>& file, std::size_t offset, std::size_t size);
		[[nodiscard("Pure constructor")]]
		PackLoadableResourceData(const LoadRequestManager& loadRequestManager, std::shared_ptr<File::IFile>&& file, std::size_t offset, std::size_t size);
		[[nodiscard("Pure constructor")]]
		PackLoadableResourceData(const PackLoadableResourceData& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		PackLoadableResourceData(PackLoadableResourceData&& other) noexcept = default;

		~PackLoadableResourceData() noexcept = default;

		[[nodiscard("Pure function")]] 
		virtual std::size_t Size() const noexcept override;
		[[nodiscard("Must be used")]] 
		virtual std::shared_ptr<ILoadRequest> Load(const LoadParams& params, const std::function<void(const ILoadRequest&)>& callback) const override;

		PackLoadableResourceData& operator =(const PackLoadableResourceData& other) noexcept = default;
		PackLoadableResourceData& operator =(PackLoadableResourceData&& other) noexcept = default;

	private:
		const LoadRequestManager* loadRequestManager;
		std::shared_ptr<File::IFile> file;
		std::size_t offset;
		std::size_t size;
	};
}

namespace PonyEngine::Resource::Pack
{
	PackLoadableResourceData::PackLoadableResourceData(const LoadRequestManager& loadRequestManager, const std::shared_ptr<File::IFile>& file, 
		const std::size_t offset, const std::size_t size) :
		loadRequestManager{&loadRequestManager},
		file(file),
		offset{offset},
		size{size}
	{
		if (std::filesystem::file_size(this->file->Path()) < this->offset + this->size) [[unlikely]]
		{
			throw std::out_of_range("File out of range");
		}
	}

	PackLoadableResourceData::PackLoadableResourceData(const LoadRequestManager& loadRequestManager, std::shared_ptr<File::IFile>&& file,
		const std::size_t offset, const std::size_t size) :
		loadRequestManager{&loadRequestManager},
		file(std::move(file)),
		offset{offset},
		size{size}
	{
		if (std::filesystem::file_size(this->file->Path()) < this->offset + this->size) [[unlikely]]
		{
			throw std::out_of_range("File out of range");
		}
	}

	std::size_t PackLoadableResourceData::Size() const noexcept
	{
		return size;
	}

	std::shared_ptr<ILoadRequest> PackLoadableResourceData::Load(const LoadParams& params, const std::function<void(const ILoadRequest&)>& callback) const
	{
		if (params.buffer.size() + params.offset > offset + size) [[unlikely]]
		{
			throw std::out_of_range("Out of range of pack bounds");
		}

		return loadRequestManager->CreateRequest(*file, offset, params, callback);
	}
}
