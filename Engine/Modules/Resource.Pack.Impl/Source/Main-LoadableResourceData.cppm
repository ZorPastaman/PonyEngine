/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Resource.Pack.Impl:LoadableResourceData;

import std;

import PonyEngine.File;
import PonyEngine.Resource.Ext;

import :LoadRequestManager;

export namespace PonyEngine::Resource::Pack
{
	/// @brief Loadable resource data.
	class LoadableResourceData final : public ILoadableResourceData
	{
	public:
		/// @brief Creates a loadable resource data.
		/// @param loadRequestManager Load request manager.
		/// @param file Pack file.
		/// @param offset Resource offset in bytes.
		/// @param size Resource size in bytes.
		[[nodiscard("Pure constructor")]]
		LoadableResourceData(const LoadRequestManager& loadRequestManager, const File::IFile* file, std::size_t offset, std::size_t size);
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
		const File::IFile* file; ///< Pack file.
		std::size_t offset; ///< Resource offset.
		std::size_t size; ///< Resource size.
	};
}

namespace PonyEngine::Resource::Pack
{
	LoadableResourceData::LoadableResourceData(const LoadRequestManager& loadRequestManager, const File::IFile* const file,
		const std::size_t offset, const std::size_t size) :
		loadRequestManager{&loadRequestManager},
		file{file},
		offset{offset},
		size{size}
	{
	}

	std::size_t LoadableResourceData::Size() const noexcept
	{
		return size;
	}

	std::shared_ptr<ILoadRequest> LoadableResourceData::Load(const LoadParams& params, const std::function<void(const ILoadRequest&)>& callback) const
	{
		if (params.buffer.size() + params.offset > offset + size) [[unlikely]]
		{
			throw std::out_of_range("Out of range of pack bounds");
		}

		return loadRequestManager->CreateRequest(*file, offset, params, callback);
	}
}
