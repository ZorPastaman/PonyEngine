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

export module PonyEngine.Resource.Pack.Impl:DataAccessWorker;

import std;

import :FileLoadableDataAccess;
import :FileDataAccess;
import :LoadableDataAccessRequestWorker;
import :MemoryDataAccess;
import :MemoryLoadableDataAccess;

export namespace PonyEngine::Resource::Pack
{
	class DataAccessWorker final
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit DataAccessWorker(LoadableDataAccessRequestWorker& requestWorker) noexcept;
		DataAccessWorker(const DataAccessWorker&) = delete;
		DataAccessWorker(DataAccessWorker&&) = delete;

		~DataAccessWorker() noexcept;

		[[nodiscard("Pure function")]]
		std::shared_ptr<FileLoadableDataAccess> CreateFileLoadableDataAccess(std::shared_ptr<File::IFile> dataFile, std::size_t offset, std::size_t size) const;
		[[nodiscard("Pure function")]]
		std::shared_ptr<MemoryLoadableDataAccess> CreateMemoryLoadableDataAccess(std::shared_ptr<const std::byte[]> loadedData, std::size_t offset, std::size_t size) const;
		[[nodiscard("Pure function")]]
		std::shared_ptr<FileDataAccess> CreateFileDataAccess(std::filesystem::path path, std::size_t offset, std::size_t size) const;
		[[nodiscard("Pure function")]]
		std::shared_ptr<MemoryDataAccess> CreateMemoryDataAccess(std::shared_ptr<const std::byte[]> loadedData, std::size_t offset, std::size_t size) const;

		DataAccessWorker& operator =(const DataAccessWorker&) = delete;
		DataAccessWorker& operator =(DataAccessWorker&&) = delete;

	private:
		LoadableDataAccessRequestWorker* requestWorker;

#ifndef NDEBUG
		mutable std::atomic_size_t accessCount;
#endif
	};
}

namespace PonyEngine::Resource::Pack
{
	DataAccessWorker::DataAccessWorker(LoadableDataAccessRequestWorker& requestWorker) noexcept :
#ifndef NDEBUG
		accessCount(0uz),
#endif
		requestWorker{&requestWorker}
	{
	}

	DataAccessWorker::~DataAccessWorker() noexcept
	{
#ifndef NDEBUG
		assert(accessCount.load(std::memory_order::relaxed) == 0uz && "Some pack data accesses are still alive.");
#endif
	}

	std::shared_ptr<FileLoadableDataAccess> DataAccessWorker::CreateFileLoadableDataAccess(std::shared_ptr<File::IFile> dataFile,
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

	std::shared_ptr<MemoryLoadableDataAccess> DataAccessWorker::CreateMemoryLoadableDataAccess(std::shared_ptr<const std::byte[]> loadedData, 
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

	std::shared_ptr<FileDataAccess> DataAccessWorker::CreateFileDataAccess(std::filesystem::path path, const std::size_t offset, const std::size_t size) const
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

	std::shared_ptr<MemoryDataAccess> DataAccessWorker::CreateMemoryDataAccess(std::shared_ptr<const std::byte[]> loadedData, 
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
