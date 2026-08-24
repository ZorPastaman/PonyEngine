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

export module PonyEngine.Resource.Pack.Impl:LoadableDataAccessRequestWorker;

import std;

import PonyEngine.File;
import PonyEngine.Job;
import PonyEngine.Math;

import :FileLoadableDataAccessRequest;
import :MemoryLoadableDataAccessRequest;

export namespace PonyEngine::Resource::Pack
{
	class LoadableDataAccessRequestWorker final
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit LoadableDataAccessRequestWorker(Job::IJobService& jobService);
		LoadableDataAccessRequestWorker(const LoadableDataAccessRequestWorker&) = delete;
		LoadableDataAccessRequestWorker(LoadableDataAccessRequestWorker&&) = delete;

		~LoadableDataAccessRequestWorker() noexcept;

		[[nodiscard("Pure function")]]
		std::shared_ptr<FileLoadableDataAccessRequest> CreateRequest(File::IFile& dataFile, std::size_t fileSize, const LoadParams& params, 
			std::move_only_function<void(const ILoadableDataAccessRequest&) noexcept> callback) const;
		[[nodiscard("Pure function")]]
		std::shared_ptr<MemoryLoadableDataAccessRequest> CreateRequest(const std::shared_ptr<const std::byte[]>& loadedData,
			std::span<const std::byte> source, const LoadParams& params, std::move_only_function<void(const ILoadableDataAccessRequest&) noexcept> callback) const;

		LoadableDataAccessRequestWorker& operator =(const LoadableDataAccessRequestWorker&) = delete;
		LoadableDataAccessRequestWorker& operator =(LoadableDataAccessRequestWorker&&) = delete;

	private:
		void AddRequest(const std::shared_ptr<LoadableDataAccessRequest>& request) const;
		std::shared_ptr<LoadableDataAccessRequest> RemoveRequest(const LoadableDataAccessRequest* request) const noexcept;

		Job::IJobService* jobService;

		std::pmr::synchronized_pool_resource resource;
		mutable std::pmr::polymorphic_allocator<std::byte> allocator;

		mutable std::unordered_map<const LoadableDataAccessRequest*, std::shared_ptr<LoadableDataAccessRequest>> ongoingRequests; ///< Ongoing requests.
		mutable std::mutex ongoingRequestMutex; ///< Ongoing request mutex.

#ifndef NDEBUG
		mutable std::atomic_size_t requestCount;
#endif

		static_assert(std::atomic_size_t::is_always_lock_free, "std::size_t isn't lock-free.");
	};
}

namespace PonyEngine::Resource::Pack
{
	LoadableDataAccessRequestWorker::LoadableDataAccessRequestWorker(Job::IJobService& jobService) :
#ifndef NDEBUG
		requestCount(0uz),
#endif
		jobService{&jobService},
		allocator(&resource)
	{
	}

	LoadableDataAccessRequestWorker::~LoadableDataAccessRequestWorker() noexcept
	{
#ifndef NDEBUG
		assert(requestCount.load(std::memory_order::relaxed) == 0uz && "Some file requests are still alive.");
#endif
	}

	std::shared_ptr<FileLoadableDataAccessRequest> LoadableDataAccessRequestWorker::CreateRequest(File::IFile& dataFile, const std::size_t fileSize, const LoadParams& params,
		std::move_only_function<void(const ILoadableDataAccessRequest&) noexcept> callback) const
	{
		if (Math::SumClamp(params.buffer.size(), params.offset) > fileSize) [[unlikely]]
		{
			throw std::out_of_range("Out of range");
		}

#ifndef NDEBUG
		const auto fileRequest = allocator.new_object<FileLoadableDataAccessRequest>(params, std::move(callback));
		requestCount.fetch_add(1uz, std::memory_order::relaxed);
		std::shared_ptr<FileLoadableDataAccessRequest> request;
		try
		{
			request = std::shared_ptr<FileLoadableDataAccessRequest>(fileRequest, [this](FileLoadableDataAccessRequest* const req)
			{
				allocator.delete_object(req);
				requestCount.fetch_sub(1uz, std::memory_order::relaxed);
			}, allocator);
		}
		catch (...)
		{
			allocator.delete_object(fileRequest);
			requestCount.fetch_sub(1uz, std::memory_order::relaxed);
			throw;
		}
#else
		const auto request = std::allocate_shared<FileLoadableDataAccessRequest>(allocator, params, std::move(callback));
#endif
		AddRequest(request);

		try
		{
			const auto readParams = File::ReadParams{.buffer = params.buffer, .offset = params.offset};
			std::shared_ptr<File::IReadRequest> fileRequest = dataFile.Read(readParams, [this, req = request.get()](const File::IReadRequest& readRequest) noexcept
			{
				const std::shared_ptr<LoadableDataAccessRequest> finishedRequest = RemoveRequest(req);
				switch (readRequest.Status())
				{
				case File::FileRequestStatus::Success:
					finishedRequest->SetSuccess(readRequest.ByteCount());
					break;
				case File::FileRequestStatus::Failure:
					finishedRequest->SetFailed(readRequest.Exception());
					break;
				case File::FileRequestStatus::Canceled:
					finishedRequest->SetCanceled();
					break;
				default: [[unlikely]]
					assert(false && "Unexpected file request status.");
					break;
				}
			});

			request->FileRequest(std::move(fileRequest));
		}
		catch (...)
		{
			RemoveRequest(request.get());
			throw;
		}

		return request;
	}

	std::shared_ptr<MemoryLoadableDataAccessRequest> LoadableDataAccessRequestWorker::CreateRequest(const std::shared_ptr<const std::byte[]>& loadedData, 
		std::span<const std::byte> source, const LoadParams& params, std::move_only_function<void(const ILoadableDataAccessRequest&) noexcept> callback) const
	{
		if (Math::SumClamp(params.buffer.size(), params.offset) > source.size()) [[unlikely]]
		{
			throw std::out_of_range("Out of range");
		}

#ifndef NDEBUG
		const auto memoryRequest = allocator.new_object<MemoryLoadableDataAccessRequest>(loadedData, params, std::move(callback));
		requestCount.fetch_add(1uz, std::memory_order::relaxed);
		std::shared_ptr<MemoryLoadableDataAccessRequest> request;
		try
		{
			request = std::shared_ptr<MemoryLoadableDataAccessRequest>(memoryRequest, [this](MemoryLoadableDataAccessRequest* const req)
			{
				allocator.delete_object(req);
				requestCount.fetch_sub(1uz, std::memory_order::relaxed);
			}, allocator);
		}
		catch (...)
		{
			allocator.delete_object(memoryRequest);
			requestCount.fetch_sub(1uz, std::memory_order::relaxed);
			throw;
		}
#else
		const auto request = std::allocate_shared<MemoryLoadableDataAccessRequest>(allocator, loadedData, params, std::move(callback));
#endif
		AddRequest(request);

		try
		{
			jobService->Schedule([this, req = request.get(), src = source.data() + params.offset, dst = params.buffer.data(), count = params.buffer.size()]() noexcept
			{
				std::memcpy(dst, src, count);
				
				const std::shared_ptr<LoadableDataAccessRequest> finishedRequest = RemoveRequest(req);
				finishedRequest->SetSuccess(count);
			});
		}
		catch (...)
		{
			RemoveRequest(request.get());
			throw;
		}

		return request;
	}

	void LoadableDataAccessRequestWorker::AddRequest(const std::shared_ptr<LoadableDataAccessRequest>& request) const
	{
		const auto lock = std::lock_guard(ongoingRequestMutex);
		assert(!ongoingRequests.contains(request.get()) && "Double request addition.");

		ongoingRequests[request.get()] = request;
	}

	std::shared_ptr<LoadableDataAccessRequest> LoadableDataAccessRequestWorker::RemoveRequest(const LoadableDataAccessRequest* const request) const noexcept
	{
		const auto lock = std::lock_guard(ongoingRequestMutex);

		const auto position = ongoingRequests.find(request);
		assert(position != ongoingRequests.cend() && "Request not found.");
		std::shared_ptr<LoadableDataAccessRequest> req = std::move(position->second);
		ongoingRequests.erase(position);

		return req;
	}
}
