/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Resource.Pack.Impl:LoadableDataAccessRequestBuffer;

import std;

import PonyEngine.Job;

import :FileLoadableDataAccessRequest;
import :MemoryLoadableDataAccessRequest;

export namespace PonyEngine::Resource::Pack
{
	class LoadableDataAccessRequestBuffer final
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit LoadableDataAccessRequestBuffer(Job::IJobService& jobService);
		LoadableDataAccessRequestBuffer(const LoadableDataAccessRequestBuffer&) = delete;
		LoadableDataAccessRequestBuffer(LoadableDataAccessRequestBuffer&&) = delete;

		~LoadableDataAccessRequestBuffer() noexcept = default;

		[[nodiscard("Pure function")]]
		std::shared_ptr<FileLoadableDataAccessRequest> CreateRequest(File::IFile& dataFile, std::size_t offset, 
			std::span<std::byte> buffer, ILoadableDataAccessRequestObserver* observer);
		[[nodiscard("Pure function")]]
		std::shared_ptr<MemoryLoadableDataAccessRequest> CreateRequest(const std::shared_ptr<const std::byte[]>& loadedData, std::span<const std::byte> source, std::span<std::byte> destination,
			ILoadableDataAccessRequestObserver* observer);

		LoadableDataAccessRequestBuffer& operator =(const LoadableDataAccessRequestBuffer&) = delete;
		LoadableDataAccessRequestBuffer& operator =(LoadableDataAccessRequestBuffer&&) = delete;

	private:
		Job::IJobService* jobService;

		std::pmr::synchronized_pool_resource resource;
		std::pmr::polymorphic_allocator<std::byte> allocator;
	};
}

namespace PonyEngine::Resource::Pack
{
	LoadableDataAccessRequestBuffer::LoadableDataAccessRequestBuffer(Job::IJobService& jobService) :
		jobService{&jobService},
		allocator(&resource)
	{
	}

	std::shared_ptr<FileLoadableDataAccessRequest> LoadableDataAccessRequestBuffer::CreateRequest(File::IFile& dataFile, const std::size_t offset, 
		const std::span<std::byte> buffer, ILoadableDataAccessRequestObserver* const observer)
	{
		return std::allocate_shared<FileLoadableDataAccessRequest>(allocator, dataFile, offset, buffer, observer);
	}

	std::shared_ptr<MemoryLoadableDataAccessRequest> LoadableDataAccessRequestBuffer::CreateRequest(const std::shared_ptr<const std::byte[]>& loadedData, 
		const std::span<const std::byte> source, const std::span<std::byte> destination, ILoadableDataAccessRequestObserver* const observer)
	{
		return std::allocate_shared<MemoryLoadableDataAccessRequest>(allocator, *jobService, loadedData, source, destination, observer);
	}
}
