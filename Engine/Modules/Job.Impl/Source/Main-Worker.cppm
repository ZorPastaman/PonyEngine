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

export module PonyEngine.Job.Impl:Worker;

import std;

import PonyEngine.Job;

import :Job;
import :JobID;
import :JobPool;

export namespace PonyEngine::Job
{
	/// @brief Worker.
	class Worker final
	{
	public:
		/// @brief Creates a worker.
		/// @param workers All workers.
		/// @param myIndex This worker index in the @p workers.
		/// @param jobQueueVersion Shared job queue version.
		[[nodiscard("Pure constructor")]]
		Worker(std::span<const std::unique_ptr<Worker>> workers, std::size_t myIndex, std::atomic_size_t* jobQueueVersion);
		Worker(const Worker&) = delete;
		Worker(Worker&&) = delete;

		~Worker() noexcept = default;

		/// @brief Gets the thread ID.
		/// @return Thread ID.
		/// @note The worker must be started before calling this.
		[[nodiscard("Pure function")]]
		std::thread::id ThreadID() const noexcept;
		/// @brief Starts the worker.
		/// @note The worker mustn't be started or stopped before calling this.
		void Start();
		/// @brief Stops the worker.
		void Stop() noexcept;
		/// @brief Joins the worker thread.
		/// @note The thread must be started and then stopped before calling this.
		void Join() noexcept;

		/// @brief Tries to acquire a job.
		/// @return Job ID. May be invalid.
		[[nodiscard("Must be used")]]
		JobID AcquireJob() noexcept;
		/// @brief Gets a job.
		/// @param index Job index.
		/// @return Job.
		[[nodiscard("Pure function")]]
		Job& GetJob(std::size_t index) noexcept;
		/// @brief Adds a job to a queue.
		/// @param jobId Job ID. Must be a job acquired from this worker.
		void AddToQueue(const JobID& jobId) noexcept;

		Worker& operator =(const Worker&) = delete;
		Worker& operator =(Worker&&) = delete;

	private:
		/// @brief Worker main function.
		void Work() noexcept;

		/// @brief Finds a next job to execute.
		/// @return Next job.
		[[nodiscard("Must be used")]]
		JobID FindJob() noexcept;
		/// @brief Gets a job from the local queue.
		/// @return Next job.
		[[nodiscard("Must be used")]]
		JobID GetJob() noexcept;
		/// @brief Tries to steal a job from other workers.
		/// @return Next job.
		[[nodiscard("Must be used")]]
		JobID StealJob() const noexcept;
		/// @brief Tries to get a job from the local queue.
		/// @return Next job.
		[[nodiscard("Must be used")]]
		JobID GrabJob() noexcept;
		/// @brief Takes a job from the local queue.
		/// @return Next job.
		/// @note The function is unsafe.
		[[nodiscard("Must be used")]]
		JobID TakeJob() noexcept;

		/// @brief Increments the global job queue version.
		void IncrementJobQueueVersion() const noexcept;

		std::unique_ptr<JobPool> jobPool; ///< Job pool.
		std::queue<JobID> jobQueue; ///< Job queue.
		std::mutex jobQueueMutex; ///< Mutex that must be used while working with the @p jobQueue.
		std::atomic_size_t* jobQueueVersion; ///< Global job queue version.

		std::span<const std::unique_ptr<Worker>> workers; ///< All workers list.
		std::size_t myIndex; ///< This worker index in the @p workers.

		std::optional<std::thread> thread; ///< Worker thread.
		std::atomic_bool running; ///< Is the worker running?

		static_assert(std::atomic_bool::is_always_lock_free, "Bool is not lock-free");
		static_assert(std::atomic_size_t::is_always_lock_free, "Size_t is not lock-free");
	};
}

namespace PonyEngine::Job
{
	Worker::Worker(const std::span<const std::unique_ptr<Worker>> workers, const std::size_t myIndex, std::atomic_size_t* const jobQueueVersion) :
		jobPool(std::make_unique<JobPool>()),
		jobQueueVersion{jobQueueVersion},
		workers(workers),
		myIndex{myIndex},
		running{true}
	{
		assert(this->myIndex < this->workers.size() && "Wrong worker index.");
		assert(this->jobQueueVersion && "The job queue version is nullptr.");
	}

	std::thread::id Worker::ThreadID() const noexcept
	{
		assert(thread && "The thread wasn't created.");
		return thread->get_id();
	}

	void Worker::Start()
	{
		assert(!thread && "The thread was already started.");
		assert(running.load(std::memory_order::relaxed) && "The worker is stopped.");
		thread = std::thread(&Worker::Work, this);
	}

	void Worker::Stop() noexcept
	{
		running.store(false, std::memory_order::relaxed);
	}

	void Worker::Join() noexcept
	{
		assert(thread && "The thread wasn't created.");
		assert(!running.load(std::memory_order::relaxed) && "The worker wasn't stopped.");
		thread->join();
	}

	JobID Worker::AcquireJob() noexcept
	{
		const std::optional<std::size_t> jobIndex = jobPool->AcquireJob();
		return jobIndex ? JobID{.poolIndex = myIndex, .jobIndex = *jobIndex} : JobID{};
	}

	Job& Worker::GetJob(const std::size_t index) noexcept
	{
		return jobPool->GetJob(index);
	}

	void Worker::AddToQueue(const JobID& jobId) noexcept // It may throw, but it's intentionally noexcept to fail the program
	{
		assert(jobId.poolIndex == myIndex && "Wrong pool index.");

		{
			const auto lock = std::lock_guard(jobQueueMutex);
			jobQueue.push(jobId);
		}

		IncrementJobQueueVersion();
	}

	void Worker::Work() noexcept
	{
		while (running.load(std::memory_order::relaxed))
		{
			const std::size_t initialJobQueueVersion = jobQueueVersion->load(std::memory_order::acquire);
			if (const JobID jobId = FindJob(); jobId.IsValid())
			{
				JobPool& executedJobPool = *workers[jobId.poolIndex]->jobPool;
				Job& job = executedJobPool.GetJob(jobId.jobIndex);
				job.Execute();
				job.Task(nullptr);
				job.IncrementVersion();
				job.ProcessDependents([&](const JobID& dependentId)
				{
					Worker& dependentWorker = *workers[dependentId.poolIndex];
					if (Job& dependent = dependentWorker.jobPool->GetJob(dependentId.jobIndex); dependent.Unblock())
					{
						dependentWorker.AddToQueue(dependentId);
					}
				});
				executedJobPool.ReleaseJob(jobId.jobIndex);
			}
			else
			{
				jobQueueVersion->wait(initialJobQueueVersion, std::memory_order::relaxed);
			}
		}
	}

	JobID Worker::FindJob() noexcept
	{
		const JobID job = GetJob();
		return job.IsValid() ? job : StealJob();
	}

	JobID Worker::GetJob() noexcept
	{
		JobID job;
		{
			const auto lock = std::lock_guard(jobQueueMutex);
			job = TakeJob();
		}

		if (job.IsValid())
		{
			IncrementJobQueueVersion();
		}

		return job;
	}

	JobID Worker::StealJob() const noexcept
	{
		for (std::size_t i = 1uz; i < workers.size(); ++i)
		{
			const std::size_t workerIndex = (myIndex + i) % workers.size();
			if (const JobID job = workers[workerIndex]->GrabJob(); job.IsValid())
			{
				return job;
			}
		}

		return JobID{};
	}

	JobID Worker::GrabJob() noexcept
	{
		auto job = JobID{};
		if (const auto lock = std::unique_lock(jobQueueMutex, std::try_to_lock))
		{
			job = TakeJob();
		}

		if (job.IsValid())
		{
			IncrementJobQueueVersion();
		}

		return job;
	}

	JobID Worker::TakeJob() noexcept
	{
		if (jobQueue.empty())
		{
			return JobID{};
		}

		const JobID nextJob = jobQueue.front();
		jobQueue.pop();

		return nextJob;
	}

	void Worker::IncrementJobQueueVersion() const noexcept
	{
		jobQueueVersion->fetch_add(1uz, std::memory_order::release);
		jobQueueVersion->notify_one();
	}
}
