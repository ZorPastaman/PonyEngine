/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <cassert>

export module PonyEngine.Resource.Pack.Impl:FileLoadableDataAccess;

import std;

import PonyEngine.File;
import PonyEngine.Resource.Ext;

import :LoadableDataAccessRequest;
import :LoadableDataAccessRequestWorker;

export namespace PonyEngine::Resource::Pack
{
	/// @brief File loadable data access.
	class FileLoadableDataAccess final : public ILoadableDataAccess
	{
	public:
		/// @brief Creates a file loadable data access.
		/// @param worker Loadable data access request worker.
		/// @param dataFile Data file.
		/// @param offset Data offset.
		/// @param size Data size.
		[[nodiscard("Pure constructor")]]
		FileLoadableDataAccess(LoadableDataAccessRequestWorker& worker, std::shared_ptr<File::IFile> dataFile, std::size_t offset, std::size_t size) noexcept;
		FileLoadableDataAccess(const FileLoadableDataAccess&) = delete;
		FileLoadableDataAccess(FileLoadableDataAccess&&) = delete;

		~FileLoadableDataAccess() noexcept = default;

		[[nodiscard("Pure function")]] 
		virtual std::size_t Size() const noexcept override;

		[[nodiscard("Must be used")]] 
		virtual std::shared_ptr<ILoadableDataAccessRequest> Load(const LoadParams& params,
			std::move_only_function<void(const ILoadableDataAccessRequest&) noexcept> callback) override;

		FileLoadableDataAccess& operator =(const FileLoadableDataAccess&) = delete;
		FileLoadableDataAccess& operator =(FileLoadableDataAccess&&) = delete;

	private:
		LoadableDataAccessRequestWorker* worker; ///< Loadable data access request worker.

		std::shared_ptr<File::IFile> dataFile; ///< Data file.
		std::size_t offset; ///< Data offset.
		std::size_t size; ///< Data size.
	};
}

namespace PonyEngine::Resource::Pack
{
	FileLoadableDataAccess::FileLoadableDataAccess(LoadableDataAccessRequestWorker& worker, std::shared_ptr<File::IFile> dataFile, 
		const std::size_t offset, const std::size_t size) noexcept :
		worker{&worker},
		dataFile(std::move(dataFile)),
		offset{offset},
		size{size}
	{
		assert(this->dataFile && "Data file is nullptr.");
	}

	std::size_t FileLoadableDataAccess::Size() const noexcept
	{
		return size;
	}

	std::shared_ptr<ILoadableDataAccessRequest> FileLoadableDataAccess::Load(const LoadParams& params,
		std::move_only_function<void(const ILoadableDataAccessRequest&) noexcept> callback)
	{
		return worker->CreateRequest(*dataFile, size, params, std::move(callback));
	}
}
