/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Resource.File.Impl:LoadableResourceData;

import std;

import PonyEngine.File;
import PonyEngine.Resource.Ext;

import :LoadRequestManager;

export namespace PonyEngine::Resource::File
{
	/// @brief Loadable resource data.
	class LoadableResourceData final : public ILoadableResourceData
	{
	public:
		/// @brief Creates a loadable resource data.
		/// @param loadRequestManager Load request manager.
		/// @param file Resource file.
		[[nodiscard("Pure constructor")]]
		LoadableResourceData(const LoadRequestManager& loadRequestManager, const std::shared_ptr<PonyEngine::File::IFile>& file);
		/// @brief Creates a loadable resource data.
		/// @param loadRequestManager Load request manager.
		/// @param file Resource file.
		[[nodiscard("Pure constructor")]]
		LoadableResourceData(const LoadRequestManager& loadRequestManager, std::shared_ptr<PonyEngine::File::IFile>&& file);
		[[nodiscard("Pure constructor")]]
		LoadableResourceData(const LoadableResourceData& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		LoadableResourceData(LoadableResourceData&& other) noexcept = default;

		~LoadableResourceData() noexcept = default;

		[[nodiscard("Pure function")]] 
		virtual std::size_t Size() const noexcept override;
		[[nodiscard("Must be used")]] 
		virtual std::shared_ptr<ILoadRequest> Load(const LoadParams& params, const std::function<void(const ILoadRequest&)>& callback) const override;

		LoadableResourceData& operator =(const LoadableResourceData& other) noexcept = default;
		LoadableResourceData& operator =(LoadableResourceData&& other) noexcept = default;

	private:
		const LoadRequestManager* loadRequestManager; ///< Load request manager.
		std::shared_ptr<PonyEngine::File::IFile> file; ///< Resource file.
		std::size_t size; ///< Resource size.
	};
}

namespace PonyEngine::Resource::File
{
	LoadableResourceData::LoadableResourceData(const LoadRequestManager& loadRequestManager, const std::shared_ptr<PonyEngine::File::IFile>& file) :
		loadRequestManager{&loadRequestManager},
		file(file),
		size{static_cast<std::size_t>(std::filesystem::file_size(this->file->Path()))}
	{
	}

	LoadableResourceData::LoadableResourceData(const LoadRequestManager& loadRequestManager, std::shared_ptr<PonyEngine::File::IFile>&& file) :
		loadRequestManager{&loadRequestManager},
		file(std::move(file)),
		size{static_cast<std::size_t>(std::filesystem::file_size(this->file->Path()))}
	{
	}

	std::size_t LoadableResourceData::Size() const noexcept
	{
		return size;
	}

	std::shared_ptr<ILoadRequest> LoadableResourceData::Load(const LoadParams& params, const std::function<void(const ILoadRequest&)>& callback) const
	{
		if (params.buffer.size() + params.offset > size) [[unlikely]]
		{
			throw std::out_of_range("Out of range of file bounds");
		}

		return loadRequestManager->CreateRequest(*file, params, callback);
	}
}
