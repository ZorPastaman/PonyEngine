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

import PonyEngine.Async;
import PonyEngine.File;
import PonyEngine.Job;
import PonyEngine.Math;

import :FileLoadableDataAccessRequest;
import :LoadableDataAccessRequest;

export namespace PonyEngine::Resource::Pack
{
	/// @brief Loadable data access request worker.
	class LoadableDataAccessRequestWorker final
	{
	public:
		/// @brief Creates a loadable data access request worker.
		/// @param jobService Job service.
		[[nodiscard("Pure constructor")]]
		explicit LoadableDataAccessRequestWorker(Job::IJobService& jobService);
		LoadableDataAccessRequestWorker(const LoadableDataAccessRequestWorker&) = delete;
		LoadableDataAccessRequestWorker(LoadableDataAccessRequestWorker&&) = delete;

		~LoadableDataAccessRequestWorker() noexcept;

		/// @brief Creates a file loadable data access request.
		/// @param dataFile Data file.
		/// @param fileSize Data file size.
		/// @param params Load parameters.
		/// @param callback Callback.
		/// @return File loadable data access request.
		[[nodiscard("Pure function")]]
		std::shared_ptr<FileLoadableDataAccessRequest> CreateRequest(File::IFile& dataFile, std::size_t fileSize, const LoadParams& params, 
			std::move_only_function<void(const ILoadableDataAccessRequest&) noexcept> callback) const;
		/// @brief Creates a memory loadable data access request.
		/// @param source Memory source.
		/// @param params Load parameters.
		/// @param callback Callback.
		/// @return Memory loadable data access request.
		[[nodiscard("Pure function")]]
		std::shared_ptr<LoadableDataAccessRequest> CreateRequest(std::span<const std::byte> source, const LoadParams& params, 
			std::move_only_function<void(const ILoadableDataAccessRequest&) noexcept> callback) const;

		LoadableDataAccessRequestWorker& operator =(const LoadableDataAccessRequestWorker&) = delete;
		LoadableDataAccessRequestWorker& operator =(LoadableDataAccessRequestWorker&&) = delete;

	private:
		/// @brief Adds the request.
		/// @param request Request to add.
		void AddRequest(const std::shared_ptr<LoadableDataAccessRequest>& request) const;
		/// @brief Removes the request.
		/// @param request Request to remove.
		/// @return Removed request.
		std::shared_ptr<LoadableDataAccessRequest> RemoveRequest(const LoadableDataAccessRequest* request) const noexcept;

		/// @brief Increment the ongoing request count.
		void IncrementOngoingRequestCount() const noexcept;
		/// @brief Decrement the ongoing request count.
		void DecrementOngoingRequestCount() const noexcept;
		/// @brief Wait till the ongoing request count reaches 0.
		void WaitForOngoingRequestCountToFinish() const noexcept;

		Job::IJobService* jobService; ///< Job service.

		std::pmr::synchronized_pool_resource requestResource; ///< Memory resource for requests.
		mutable std::pmr::polymorphic_allocator<std::byte> requestAllocator; ///< Allocator for requests.

		mutable std::unordered_map<const LoadableDataAccessRequest*, std::shared_ptr<LoadableDataAccessRequest>> ongoingRequests; ///< Ongoing requests.
		mutable std::mutex ongoingRequestMutex; ///< Ongoing request mutex.
		mutable std::atomic_size_t ongoingRequestCount; ///< Ongoing request count.

#ifndef NDEBUG
		mutable std::atomic_size_t requestCount; ///< Request count.
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
		requestAllocator(&requestResource),
		ongoingRequestCount(0uz)
	{
	}

	LoadableDataAccessRequestWorker::~LoadableDataAccessRequestWorker() noexcept
	{
		WaitForOngoingRequestCountToFinish();

#ifndef NDEBUG
		assert(requestCount.load(std::memory_order::relaxed) == 0uz && "Some file requests are still alive.");
#endif
	}

	std::shared_ptr<FileLoadableDataAccessRequest> LoadableDataAccessRequestWorker::CreateRequest(File::IFile& dataFile, const std::size_t fileSize, const LoadParams& params,
		std::move_only_function<void(const ILoadableDataAccessRequest&) noexcept> callback) const
	{
		if (!params.buffer.data()) [[unlikely]]
		{
			throw std::invalid_argument("Buffer is nullptr");
		}
		if (Math::SumClamp(params.buffer.size(), params.offset) > fileSize) [[unlikely]]
		{
			throw std::out_of_range("Out of range");
		}

#ifndef NDEBUG
		const auto rawRequest = requestAllocator.new_object<FileLoadableDataAccessRequest>(params, std::move(callback));
		requestCount.fetch_add(1uz, std::memory_order::relaxed);
		std::shared_ptr<FileLoadableDataAccessRequest> request;
		try
		{
			request = std::shared_ptr<FileLoadableDataAccessRequest>(rawRequest, [this](FileLoadableDataAccessRequest* const req)
			{
				requestAllocator.delete_object(req);
				requestCount.fetch_sub(1uz, std::memory_order::relaxed);
			}, requestAllocator);
		}
		catch (...)
		{
			requestAllocator.delete_object(rawRequest);
			requestCount.fetch_sub(1uz, std::memory_order::relaxed);
			throw;
		}
#else
		auto request = std::allocate_shared<FileLoadableDataAccessRequest>(requestAllocator, params, std::move(callback));
#endif
		IncrementOngoingRequestCount();
		AddRequest(request);

		try
		{
			const auto readParams = File::ReadParams{.buffer = params.buffer, .offset = params.offset};
			request->FileRequest(dataFile.Read(readParams, [this, req = request.get()](const File::IReadRequest& readRequest) noexcept
			{
				std::shared_ptr<LoadableDataAccessRequest> finishedRequest = RemoveRequest(req);
				switch (readRequest.Status())
				{
				case Async::RequestStatus::Success:
					finishedRequest->SetSuccess(readRequest.ByteCount());
					break;
				case Async::RequestStatus::Failure:
					finishedRequest->SetFailed(readRequest.Exception());
					break;
				case Async::RequestStatus::Canceled:
					finishedRequest->SetCanceled();
					break;
				default: [[unlikely]]
					assert(false && "Unexpected file request status.");
					break;
				}

				finishedRequest.reset();
				DecrementOngoingRequestCount();
			}));
		}
		catch (...)
		{
			RemoveRequest(request.get());
			DecrementOngoingRequestCount();
			throw;
		}

		return request;
	}

	std::shared_ptr<LoadableDataAccessRequest> LoadableDataAccessRequestWorker::CreateRequest(const std::span<const std::byte> source, const LoadParams& params,
		std::move_only_function<void(const ILoadableDataAccessRequest&) noexcept> callback) const
	{
		if (!params.buffer.data()) [[unlikely]]
		{
			throw std::invalid_argument("Buffer is nullptr");
		}
		if (Math::SumClamp(params.buffer.size(), params.offset) > source.size()) [[unlikely]]
		{
			throw std::out_of_range("Out of range");
		}

#ifndef NDEBUG
		const auto memoryRequest = requestAllocator.new_object<LoadableDataAccessRequest>(params, std::move(callback));
		requestCount.fetch_add(1uz, std::memory_order::relaxed);
		std::shared_ptr<LoadableDataAccessRequest> request;
		try
		{
			request = std::shared_ptr<LoadableDataAccessRequest>(memoryRequest, [this](LoadableDataAccessRequest* const req)
			{
				requestAllocator.delete_object(req);
				requestCount.fetch_sub(1uz, std::memory_order::relaxed);
			}, requestAllocator);
		}
		catch (...)
		{
			requestAllocator.delete_object(memoryRequest);
			requestCount.fetch_sub(1uz, std::memory_order::relaxed);
			throw;
		}
#else
		auto request = std::allocate_shared<LoadableDataAccessRequest>(requestAllocator, params, std::move(callback));
#endif
		IncrementOngoingRequestCount();
		AddRequest(request);

		try
		{
			jobService->Schedule([this, req = request.get(), src = source.data() + params.offset, dst = params.buffer.data(), count = params.buffer.size()]() noexcept
			{
				std::memcpy(dst, src, count);
				
				std::shared_ptr<LoadableDataAccessRequest> finishedRequest = RemoveRequest(req);
				finishedRequest->SetSuccess(count);

				finishedRequest.reset();
				DecrementOngoingRequestCount();
			});
		}
		catch (...)
		{
			RemoveRequest(request.get());
			DecrementOngoingRequestCount();
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

	void LoadableDataAccessRequestWorker::IncrementOngoingRequestCount() const noexcept
	{
		ongoingRequestCount.fetch_add(1uz, std::memory_order::release);
	}

	void LoadableDataAccessRequestWorker::DecrementOngoingRequestCount() const noexcept
	{
		ongoingRequestCount.fetch_sub(1uz, std::memory_order::release);
		ongoingRequestCount.notify_one();
	}

	void LoadableDataAccessRequestWorker::WaitForOngoingRequestCountToFinish() const noexcept
	{
		for (std::size_t requestCount = ongoingRequestCount.load(std::memory_order::acquire);
			requestCount > 0uz;
			requestCount = ongoingRequestCount.load(std::memory_order::acquire))
		{
			ongoingRequestCount.wait(requestCount, std::memory_order::acquire);
		}
	}
}
