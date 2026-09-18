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

export module PonyEngine.Resource.Pack.Impl:DataAccessFactory;

import std;

import :FileLoadableDataAccess;
import :FileDataAccess;
import :LoadableDataAccessRequestWorker;
import :MemoryDataAccess;
import :MemoryLoadableDataAccess;

export namespace PonyEngine::Resource::Pack
{
	/// @brief Data access factory.
	class DataAccessFactory final
	{
	public:
		/// @brief Creates a data access factory.
		/// @param requestWorker Loadable data access request worker.
		[[nodiscard("Pure constructor")]]
		explicit DataAccessFactory(LoadableDataAccessRequestWorker& requestWorker) noexcept;
		DataAccessFactory(const DataAccessFactory&) = delete;
		DataAccessFactory(DataAccessFactory&&) = delete;

		~DataAccessFactory() noexcept;

		/// @brief Creates a file loadable data access.
		/// @param dataFile Data file. Must be valid.
		/// @param offset Data offset.
		/// @param size Data size.
		/// @return File loadable data access.
		[[nodiscard("Pure function")]]
		std::shared_ptr<FileLoadableDataAccess> CreateFileLoadableDataAccess(std::shared_ptr<File::IFile> dataFile, std::size_t offset, std::size_t size) const;
		/// @brief Creates a memory loadable data access.
		/// @param loadedData Loaded data. Must be valid.
		/// @param offset Data offset.
		/// @param size Data size.
		/// @return Memory loadable data access.
		[[nodiscard("Pure function")]]
		std::shared_ptr<MemoryLoadableDataAccess> CreateMemoryLoadableDataAccess(std::shared_ptr<const std::byte[]> loadedData, std::size_t offset, std::size_t size) const;
		/// @brief Creates a file data access.
		/// @param path File path. Must be valid.
		/// @param offset Data offset.
		/// @param size Data size.
		/// @return File data access.
		[[nodiscard("Pure function")]]
		std::shared_ptr<FileDataAccess> CreateFileDataAccess(std::filesystem::path path, std::size_t offset, std::size_t size) const;
		/// @brief Creates a memory data access.
		/// @param loadedData Loaded data. Must be valid.
		/// @param offset Data offset.
		/// @param size Data size.
		/// @return Memory data access.
		[[nodiscard("Pure function")]]
		std::shared_ptr<MemoryDataAccess> CreateMemoryDataAccess(std::shared_ptr<const std::byte[]> loadedData, std::size_t offset, std::size_t size) const;

		DataAccessFactory& operator =(const DataAccessFactory&) = delete;
		DataAccessFactory& operator =(DataAccessFactory&&) = delete;

	private:
		LoadableDataAccessRequestWorker* requestWorker; ///< Loadable data access request worker.

#ifndef NDEBUG
		mutable std::atomic_size_t accessCount; ///< Access count.
#endif
	};
}

namespace PonyEngine::Resource::Pack
{
	DataAccessFactory::DataAccessFactory(LoadableDataAccessRequestWorker& requestWorker) noexcept :
#ifndef NDEBUG
		accessCount(0uz),
#endif
		requestWorker{&requestWorker}
	{
	}

	DataAccessFactory::~DataAccessFactory() noexcept
	{
#ifndef NDEBUG
		assert(accessCount.load(std::memory_order::relaxed) == 0uz && "Some pack data accesses are still alive.");
#endif
	}

	std::shared_ptr<FileLoadableDataAccess> DataAccessFactory::CreateFileLoadableDataAccess(std::shared_ptr<File::IFile> dataFile,
		const std::size_t offset, const std::size_t size) const
	{
#ifndef NDEBUG
		const auto access = new FileLoadableDataAccess(*requestWorker, std::move(dataFile), offset, size);
		accessCount.fetch_add(1uz, std::memory_order::relaxed);
		try
		{
			return std::shared_ptr<FileLoadableDataAccess>(access, [this](const FileLoadableDataAccess* const dataAccess) noexcept
			{
				delete dataAccess;
				accessCount.fetch_sub(1uz, std::memory_order::relaxed);
			});
		}
		catch (...)
		{
			delete access;
			accessCount.fetch_sub(1uz, std::memory_order::relaxed);
			throw;
		}
#else
		return std::make_shared<FileLoadableDataAccess>(*requestWorker, std::move(dataFile), offset, size);
#endif
	}

	std::shared_ptr<MemoryLoadableDataAccess> DataAccessFactory::CreateMemoryLoadableDataAccess(std::shared_ptr<const std::byte[]> loadedData, 
		const std::size_t offset, const std::size_t size) const
	{
#ifndef NDEBUG
		const auto access = new MemoryLoadableDataAccess(*requestWorker, std::move(loadedData), offset, size);
		accessCount.fetch_add(1uz, std::memory_order::relaxed);
		try
		{
			return std::shared_ptr<MemoryLoadableDataAccess>(access, [this](const MemoryLoadableDataAccess* const dataAccess) noexcept
			{
				delete dataAccess;
				accessCount.fetch_sub(1uz, std::memory_order::relaxed);
			});
		}
		catch (...)
		{
			delete access;
			accessCount.fetch_sub(1uz, std::memory_order::relaxed);
			throw;
		}
#else
		return std::make_shared<MemoryLoadableDataAccess>(*requestWorker, std::move(loadedData), offset, size);
#endif
	}

	std::shared_ptr<FileDataAccess> DataAccessFactory::CreateFileDataAccess(std::filesystem::path path, const std::size_t offset, const std::size_t size) const
	{
#ifndef NDEBUG
		const auto access = new FileDataAccess(std::move(path), offset, size);
		accessCount.fetch_add(1uz, std::memory_order::relaxed);
		try
		{
			return std::shared_ptr<FileDataAccess>(access, [this](const FileDataAccess* const dataAccess) noexcept
			{
				delete dataAccess;
				accessCount.fetch_sub(1uz, std::memory_order::relaxed);
			});
		}
		catch (...)
		{
			delete access;
			accessCount.fetch_sub(1uz, std::memory_order::relaxed);
			throw;
		}
#else
		return std::make_shared<FileDataAccess>(std::move(path), offset, size);
#endif
	}

	std::shared_ptr<MemoryDataAccess> DataAccessFactory::CreateMemoryDataAccess(std::shared_ptr<const std::byte[]> loadedData, 
		const std::size_t offset, const std::size_t size) const
	{
#ifndef NDEBUG
		const auto access = new MemoryDataAccess(std::move(loadedData), offset, size);
		accessCount.fetch_add(1uz, std::memory_order::relaxed);
		try
		{
			return std::shared_ptr<MemoryDataAccess>(access, [this](const MemoryDataAccess* const dataAccess) noexcept
			{
				delete dataAccess;
				accessCount.fetch_sub(1uz, std::memory_order::relaxed);
			});
		}
		catch (...)
		{
			delete access;
			accessCount.fetch_sub(1uz, std::memory_order::relaxed);
			throw;
		}
#else
		return std::make_shared<MemoryDataAccess>(std::move(loadedData), offset, size);
#endif
	}
}
