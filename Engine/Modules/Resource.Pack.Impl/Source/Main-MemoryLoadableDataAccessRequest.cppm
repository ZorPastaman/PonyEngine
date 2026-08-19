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

export module PonyEngine.Resource.Pack.Impl:MemoryLoadableDataAccessRequest;

import std;

import PonyEngine.Job;
import PonyEngine.Resource.Ext;

export namespace PonyEngine::Resource::Pack
{
	class MemoryLoadableDataAccessRequest final : public ILoadableDataAccessRequest
	{
	public:
		[[nodiscard("Pure constructor")]]
		MemoryLoadableDataAccessRequest(Job::IJobService& jobService, const std::shared_ptr<const std::byte[]>& loadedData,
			std::span<const std::byte> source, std::span<std::byte> destination, ILoadableDataAccessRequestObserver* observer);
		MemoryLoadableDataAccessRequest(const MemoryLoadableDataAccessRequest&) = delete;
		MemoryLoadableDataAccessRequest(MemoryLoadableDataAccessRequest&&) = delete;

		~MemoryLoadableDataAccessRequest() noexcept = default;

		[[nodiscard("Pure function")]] 
		virtual LoadableRequestStatus Status() const noexcept override;
		[[nodiscard("Pure function")]] 
		virtual std::size_t ByteCount() const override;
		[[nodiscard("Pure function")]] 
		virtual const std::exception_ptr& Exception() const override;

		virtual void Cancel() override;

		virtual void Wait() const noexcept override;

		MemoryLoadableDataAccessRequest& operator =(const MemoryLoadableDataAccessRequest&) = delete;
		MemoryLoadableDataAccessRequest& operator =(MemoryLoadableDataAccessRequest&&) = delete;

	private:
		class CopyTask final : public Job::ITask
		{
		public:
			[[nodiscard("Pure constructor")]]
			explicit CopyTask(std::span<const std::byte> source, std::span<std::byte> destination, ILoadableDataAccessRequestObserver* observer) noexcept;
			CopyTask(const CopyTask&) = delete;
			CopyTask(CopyTask&&) = delete;

			~CopyTask() noexcept = default;

			[[nodiscard("Pure function")]]
			LoadableRequestStatus Status() const noexcept;
			[[nodiscard("Pure function")]]
			std::size_t ByteCount() const noexcept;

			virtual void Execute() noexcept override;

			CopyTask& operator =(const CopyTask&) = delete;
			CopyTask& operator =(CopyTask&&) = delete;

		private:
			const std::byte* source;
			std::byte* destination;
			ILoadableDataAccessRequestObserver* observer;

			std::size_t byteCount;
			std::atomic<LoadableRequestStatus> status;
		};

		Job::IJobService* jobService;
		std::shared_ptr<const std::byte[]> loadedData;

		CopyTask task;
		Job::JobHandle job;
	};
}

namespace PonyEngine::Resource::Pack
{
	MemoryLoadableDataAccessRequest::MemoryLoadableDataAccessRequest(Job::IJobService& jobService, const std::shared_ptr<const std::byte[]>& loadedData,
		const std::span<const std::byte> source, const std::span<std::byte> destination, ILoadableDataAccessRequestObserver* const observer) :
		jobService{&jobService},
		loadedData(loadedData),
		task(source, destination, observer),
		job(this->jobService->Schedule(task))
	{
		assert(this->loadedData && "Loaded data is nullptr.");
	}

	LoadableRequestStatus MemoryLoadableDataAccessRequest::Status() const noexcept
	{
		return task.Status();
	}

	std::size_t MemoryLoadableDataAccessRequest::ByteCount() const
	{
		if (task.Status() != LoadableRequestStatus::Success)
		{
			throw std::logic_error("Invalid status");
		}

		return task.ByteCount();
	}

	const std::exception_ptr& MemoryLoadableDataAccessRequest::Exception() const
	{
		throw std::logic_error("Invalid status");
	}

	void MemoryLoadableDataAccessRequest::Cancel()
	{
	}

	void MemoryLoadableDataAccessRequest::Wait() const noexcept
	{
		jobService->Wait(job);
	}

	MemoryLoadableDataAccessRequest::CopyTask::CopyTask(const std::span<const std::byte> source, const std::span<std::byte> destination, 
		ILoadableDataAccessRequestObserver* const observer) noexcept :
		source{source.data()},
		destination{destination.data()},
		observer{observer},
		byteCount{std::min(source.size(), destination.size())},
		status(LoadableRequestStatus::Pending)
	{
		assert(this->source && "Source is nullptr.");
		assert(this->destination && "Destination is nullptr.");
	}

	LoadableRequestStatus MemoryLoadableDataAccessRequest::CopyTask::Status() const noexcept
	{
		return status.load(std::memory_order::acquire);
	}

	std::size_t MemoryLoadableDataAccessRequest::CopyTask::ByteCount() const noexcept
	{
		return byteCount;
	}

	void MemoryLoadableDataAccessRequest::CopyTask::Execute() noexcept
	{
		std::memcpy(destination, source, byteCount);
		status.store(LoadableRequestStatus::Success, std::memory_order::release);
		status.notify_all();

		if (observer)
		{
			observer->OnSuccess(byteCount);
		}
	}
}
