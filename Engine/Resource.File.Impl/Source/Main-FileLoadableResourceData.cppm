/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Resource.File.Impl:FileLoadableResourceData;

import std;

import PonyEngine.File;
import PonyEngine.Resource.Ext;

import :LoadRequestManager;

export namespace PonyEngine::Resource::File
{
	class FileLoadableResourceData final : public ILoadableResourceData
	{
	public:
		[[nodiscard("Pure constructor")]]
		FileLoadableResourceData(const LoadRequestManager& loadRequestManager, const std::shared_ptr<PonyEngine::File::IFile>& file);
		[[nodiscard("Pure constructor")]]
		FileLoadableResourceData(const LoadRequestManager& loadRequestManager, std::shared_ptr<PonyEngine::File::IFile>&& file);
		[[nodiscard("Pure constructor")]]
		FileLoadableResourceData(const FileLoadableResourceData& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		FileLoadableResourceData(FileLoadableResourceData&& other) noexcept = default;

		~FileLoadableResourceData() noexcept = default;

		[[nodiscard("Pure function")]] 
		virtual std::size_t Size() const noexcept override;
		[[nodiscard("Must be used")]] 
		virtual std::shared_ptr<ILoadRequest> Load(const LoadParams& params, const std::function<void(const ILoadRequest&)>& callback) const override;

		FileLoadableResourceData& operator =(const FileLoadableResourceData& other) noexcept = default;
		FileLoadableResourceData& operator =(FileLoadableResourceData&& other) noexcept = default;

	private:
		const LoadRequestManager* loadRequestManager;
		std::shared_ptr<PonyEngine::File::IFile> file;
		std::size_t size;
	};
}

namespace PonyEngine::Resource::File
{
	FileLoadableResourceData::FileLoadableResourceData(const LoadRequestManager& loadRequestManager, const std::shared_ptr<PonyEngine::File::IFile>& file) :
		loadRequestManager{&loadRequestManager},
		file(file),
		size{static_cast<std::size_t>(std::filesystem::file_size(file->Path()))}
	{
	}

	FileLoadableResourceData::FileLoadableResourceData(const LoadRequestManager& loadRequestManager, std::shared_ptr<PonyEngine::File::IFile>&& file) :
		loadRequestManager{&loadRequestManager},
		file(std::move(file)),
		size{static_cast<std::size_t>(std::filesystem::file_size(file->Path()))}
	{
	}

	std::size_t FileLoadableResourceData::Size() const noexcept
	{
		return size;
	}

	std::shared_ptr<ILoadRequest> FileLoadableResourceData::Load(const LoadParams& params, const std::function<void(const ILoadRequest&)>& callback) const
	{
		return loadRequestManager->CreateRequest(*file, params, callback);
	}
}
