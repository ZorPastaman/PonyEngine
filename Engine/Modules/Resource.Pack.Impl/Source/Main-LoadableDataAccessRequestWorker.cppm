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

import :FileLoadableDataAccessRequest;
import :LoadableDataAccessRequest;
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

		~LoadableDataAccessRequestWorker() noexcept = default;

		[[nodiscard("Pure function")]]
		std::shared_ptr<LoadableDataAccessRequest> CreateRequest(File::IFile& dataFile, std::size_t offset, 
			std::span<std::byte> buffer, std::move_only_function<void(const ILoadableDataAccessRequest&) noexcept> callback) const;
		[[nodiscard("Pure function")]]
		std::shared_ptr<LoadableDataAccessRequest> CreateRequest(std::span<const std::byte> source, std::span<std::byte> destination, 
			std::move_only_function<void(const ILoadableDataAccessRequest&) noexcept> callback) const;

		LoadableDataAccessRequestWorker& operator =(const LoadableDataAccessRequestWorker&) = delete;
		LoadableDataAccessRequestWorker& operator =(LoadableDataAccessRequestWorker&&) = delete;

	private:
		void AddRequest(const std::shared_ptr<LoadableDataAccessRequest>& request) const;
		std::shared_ptr<LoadableDataAccessRequest> RemoveRequest(const LoadableDataAccessRequest* request) const;

		Job::IJobService* jobService;

		std::pmr::synchronized_pool_resource resource;
		std::pmr::polymorphic_allocator<std::byte> allocator;

		mutable std::unordered_map<const LoadableDataAccessRequest*, std::shared_ptr<LoadableDataAccessRequest>> ongoingRequests; ///< Ongoing requests.
		mutable std::mutex ongoingRequestMutex; ///< Ongoing request mutex.
	};
}

namespace PonyEngine::Resource::Pack
{
	LoadableDataAccessRequestWorker::LoadableDataAccessRequestWorker(Job::IJobService& jobService) :
		jobService{&jobService},
		allocator(&resource)
	{
	}

	std::shared_ptr<LoadableDataAccessRequest> LoadableDataAccessRequestWorker::CreateRequest(File::IFile& dataFile, const std::size_t offset, 
		const std::span<std::byte> buffer, std::move_only_function<void(const ILoadableDataAccessRequest&) noexcept> callback) const
	{
		auto request = std::allocate_shared<FileLoadableDataAccessRequest>(allocator, std::move(callback));
		AddRequest(request);

		try
		{
			const auto readParams = File::ReadParams{.buffer = buffer, .offset = offset};
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

	std::shared_ptr<LoadableDataAccessRequest> LoadableDataAccessRequestWorker::CreateRequest(const std::span<const std::byte> source, const std::span<std::byte> destination, 
		std::move_only_function<void(const ILoadableDataAccessRequest&) noexcept> callback) const
	{
		assert(source.size() == destination.size() && "Source and destination sizes mismatched.");

		auto request = std::allocate_shared<LoadableDataAccessRequest>(allocator, std::move(callback));
		AddRequest(request);

		try
		{
			jobService->Schedule([this, req = request.get(), src = source.data(), dst = destination.data(), count = source.size()]() noexcept
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

	std::shared_ptr<LoadableDataAccessRequest> LoadableDataAccessRequestWorker::RemoveRequest(const LoadableDataAccessRequest* const request) const
	{
		const auto lock = std::lock_guard(ongoingRequestMutex);

		const auto position = ongoingRequests.find(request);
		assert(position != ongoingRequests.cend() && "Request not found.");
		std::shared_ptr<LoadableDataAccessRequest> req = std::move(position->second);
		ongoingRequests.erase(position);

		return req;
	}
}
