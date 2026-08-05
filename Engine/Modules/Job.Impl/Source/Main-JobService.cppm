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

#include "PonyEngine/Log/Log.h"
#include "PonyEngine/Macro/Text.h"

export module PonyEngine.Job.Impl:JobService;

import std;

import PonyEngine.Application;
import PonyEngine.Job;
import PonyEngine.Log;
import PonyEngine.Math;

import :Job;
import :JobID;
import :Worker;

export namespace PonyEngine::Job
{
	/// @brief Job service.
	class JobService final : public IJobService
	{
	public:
		/// @brief Creates a job service.
		/// @param application Application.
		[[nodiscard("Pure constructor")]]
		explicit JobService(Application::IApplication& application);
		JobService(const JobService&) = delete;
		JobService(JobService&&) = delete;

		~JobService() noexcept;

	private:
		[[nodiscard("Pure function")]]
		virtual std::size_t WorkerCount() const noexcept override;

		virtual JobHandle Schedule(ITask& task, std::span<const JobHandle> dependencies) override;

		virtual void Wait(std::span<const JobHandle> handles) const override;
		[[nodiscard("Pure function")]]
		virtual bool IsCompleted(const JobHandle& handle) const override;

		/// @brief Finishes workers.
		/// @param count How many workers to finish.
		void Finish(std::size_t count) noexcept;

		/// @brief Gets a free job.
		/// @param initialPoolIndex Initial pool index.
		/// @return Job ID.
		[[nodiscard("Must be used")]]
		JobID GetFreeJob(std::size_t initialPoolIndex) const noexcept;
		/// @brief Gets a job.
		/// @param id Job ID.
		/// @return Job.
		[[nodiscard("Must be used")]]
		Job& GetJob(const JobID& id) const noexcept;

		const Log::ILogService* logService; ///< Log service.

		std::vector<std::unique_ptr<Worker>> workers; ///< Workers.
		std::atomic_size_t targetWorkerIndex; ///< Target worker index. Used and incremented on scheduling a new job.

		std::atomic_size_t jobQueueVersion; ///< Job queue version. Must be incremented each time when a queue of a worker is modified.

		static_assert(std::atomic_size_t::is_always_lock_free, "Size_t is not lock-free");
	};
}

namespace PonyEngine::Job
{
	JobService::JobService(Application::IApplication& application) :
		logService{application.FindInterface<Log::ILogService>()},
		targetWorkerIndex{0uz},
		jobQueueVersion{0uz}
	{
		const std::size_t concurrency = std::thread::hardware_concurrency();
		const std::size_t threadCount = std::max(Math::DifferenceClamp(concurrency, std::size_t{PONY_ENGINE_JOB_RESERVED_THREAD_COUNT}), std::size_t{PONY_ENGINE_JOB_MIN_THREAD_COUNT});

		PONY_LOG(logService, Log::LogType::Info, "Creating workers... Thread count: '{}'; Hardware concurrency: '{}'; Role: '{}'.", threadCount, concurrency,
			PONY_STRINGIFY_VALUE(PONY_ENGINE_JOB_THREAD_ROLE));
		workers.resize(threadCount);

		for (std::size_t i = 0uz; i < threadCount; ++i)
		{
			workers[i] = std::make_unique<Worker>(workers, i, &jobQueueVersion);
		}

		for (std::size_t i = 0uz; i < threadCount; ++i)
		{
			try
			{
				const std::unique_ptr<Worker>& worker = workers[i];
				worker->Start(application);
				PONY_LOG(logService, Log::LogType::Info, "Worker thread started. ID: '{}'.", worker->ThreadID());
			}
			catch (...)
			{
				PONY_LOG(logService, Log::LogType::Error, std::current_exception(), "On starting worker thread.");
				Finish(i);
				throw;
			}
		}
		PONY_LOG(logService, Log::LogType::Info, "Creating workers done.");
	}

	JobService::~JobService() noexcept
	{
		Finish(workers.size());
	}

	std::size_t JobService::WorkerCount() const noexcept
	{
		return workers.size();
	}

	JobHandle JobService::Schedule(ITask& task, const std::span<const JobHandle> dependencies)
	{
		const std::size_t workerIndex = targetWorkerIndex.fetch_add(1uz, std::memory_order::relaxed) % workers.size();
		const JobID jobId = GetFreeJob(workerIndex);
		Worker& worker = *workers[jobId.poolIndex];
		Job& job = worker.GetJob(jobId.jobIndex);
		const std::size_t version = job.Version();
		job.Task(&task);
		job.Block(dependencies.size());

		const auto handle = ToJobHandle(jobId, version);

		if (dependencies.empty())
		{
			worker.AddToQueue(jobId);
		}
		else
		{
			for (std::size_t i = 0uz; i < dependencies.size(); ++i)
			{
				const JobHandle& dependency = dependencies[i];
				const JobID dependencyId = ToJobID(dependency);
				assert(dependencyId.poolIndex < workers.size() && dependencyId.jobIndex < PONY_ENGINE_JOB_POOL_SIZE && "Invalid dependency handle");
				const bool isAdded = GetJob(dependencyId).AddDependent(jobId, dependency.version);

				if (!isAdded && job.Unblock())
				{
					worker.AddToQueue(jobId);
				}
			}
		}

		return handle;
	}

	void JobService::Wait(const std::span<const JobHandle> handles) const
	{
		for (const JobHandle& handle : handles)
		{
			const JobID id = ToJobID(handle);
			assert(id.poolIndex < workers.size() && id.jobIndex < PONY_ENGINE_JOB_POOL_SIZE && "Invalid job handle");
			GetJob(id).Wait(handle.version);
		}
	}

	bool JobService::IsCompleted(const JobHandle& handle) const
	{
		const JobID id = ToJobID(handle);
		assert(id.poolIndex < workers.size() && id.jobIndex < PONY_ENGINE_JOB_POOL_SIZE && "Invalid job handle");
		Job& job = GetJob(id);

		if (job.Version() == handle.version)
		{
			return false;
		}

		std::atomic_thread_fence(std::memory_order::acquire);
		return true;
	}

	void JobService::Finish(const std::size_t count) noexcept
	{
		PONY_LOG(logService, Log::LogType::Info, "Destroying workers...");
		for (std::size_t i = count; i-- > 0uz; )
		{
			PONY_LOG(logService, Log::LogType::Info, "Stopping worker thread ID: '{}'.", workers[i]->ThreadID());
			workers[i]->Stop();
		}

		jobQueueVersion.fetch_add(1uz, std::memory_order::release);
		jobQueueVersion.notify_all();

		for (std::size_t i = count; i-- > 0uz; )
		{
			workers[i]->Join();
		}
		PONY_LOG(logService, Log::LogType::Info, "Destroying workers done.");
	}

	JobID JobService::GetFreeJob(const std::size_t initialPoolIndex) const noexcept
	{
		auto job = JobID{};
		for (std::size_t i = initialPoolIndex; !job.IsValid(); i = (i + 1uz) % workers.size())
		{
			job = workers[i]->AcquireJob();
		}

		return job;
	}

	Job& JobService::GetJob(const JobID& id) const noexcept
	{
		return workers[id.poolIndex]->GetJob(id.jobIndex);
	}
}
