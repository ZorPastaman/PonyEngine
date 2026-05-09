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

export module PonyEngine.Job.Impl:Worker;

import std;

import PonyEngine.Application.Ext;
import PonyEngine.Job;
import PonyEngine.Log;

import :Job;
import :JobPool;

export namespace PonyEngine::Job
{
	/// @brief Worker.
	class Worker final
	{
	public:
		/// @brief Creates a worker.
		/// @param application Application context.
		/// @param workers All workers.
		/// @param myIndex This worker index in the @p workers.
		/// @param jobQueueVersion Shared job queue version.
		[[nodiscard("Pure constructor")]]
		Worker(Application::IApplicationContext& application, std::span<const std::unique_ptr<Worker>> workers, std::size_t myIndex, std::atomic_size_t* jobQueueVersion) noexcept;
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

		/// @brief Acquires a job from the worker job pool.
		/// @return Job and a flag that tells if the job is newly created (if @a true).
		[[nodiscard("Pure function")]]
		std::pair<Job*, bool> AcquireJob();
		/// @brief Releases the job to the worker job pool.
		/// @param job Job to release.
		void ReleaseJob(Job& job);
		/// @brief Releases the job to the worker job pool without locking the pool.
		/// @param job Job to release.
		void ReleaseJobUnsafe(Job& job);
		/// @brief Adds the job to the worker queue.
		/// @param job Job to add.
		void AddJob(Job& job);

		Worker& operator =(const Worker&) = delete;
		Worker& operator =(Worker&&) = delete;

	private:
		/// @brief Worker main function.
		void Work() noexcept;
		/// @brief Executes the job.
		/// @param job Job to execute.
		void Execute(Job& job) noexcept;
		/// @brief Releases the job.
		/// @param job Job to release.
		void Release(Job& job) noexcept;

		/// @brief Finds a next job to execute.
		/// @return Next job.
		[[nodiscard("Must be used")]]
		Job* FindJob() noexcept;
		/// @brief Gets a job from the local queue.
		/// @return Next job.
		[[nodiscard("Must be used")]]
		Job* GetJob() noexcept;
		/// @brief Tries to steal a job from other workers.
		/// @return Next job.
		[[nodiscard("Must be used")]]
		Job* StealJob() const noexcept;
		/// @brief Tries to get a job from the local queue.
		/// @return Next job.
		[[nodiscard("Must be used")]]
		Job* GrabJob() noexcept;
		/// @brief Takes a job from the local queue.
		/// @return Next job.
		/// @note The function is unsafe.
		[[nodiscard("Must be used")]]
		Job* TakeJob() noexcept;

		/// @brief Increments the global job queue version.
		void IncrementJobQueueVersion() const noexcept;

		Application::IApplicationContext* application; ///< Application context.

		std::atomic_bool running; ///< Is the worker running?

		std::queue<Job*> jobQueue; ///< Job queue.
		std::mutex jobQueueMutex; ///< Mutex that must be used while working with the @p jobQueue.

		JobPool jobPool; ///< Job pool.

		std::span<const std::unique_ptr<Worker>> workers; ///< All workers list.
		std::size_t myIndex; ///< This worker index in the @p workers.

		std::atomic_size_t* jobQueueVersion; ///< Global job queue version.

		std::optional<std::thread> thread; ///< Worker thread.

		static_assert(std::atomic_bool::is_always_lock_free, "Bool is not lock-free");
		static_assert(std::atomic_size_t::is_always_lock_free, "Size_t is not lock-free");
	};
}

namespace PonyEngine::Job
{
	Worker::Worker(Application::IApplicationContext& application, const std::span<const std::unique_ptr<Worker>> workers, const std::size_t myIndex, 
		std::atomic_size_t* const jobQueueVersion) noexcept :
		application{&application},
		running{true},
		workers(workers),
		myIndex{myIndex},
		jobQueueVersion{jobQueueVersion}
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

	std::pair<Job*, bool> Worker::AcquireJob()
	{
		return jobPool.Acquire();
	}

	void Worker::ReleaseJob(Job& job)
	{
		jobPool.Release(job);
	}

	void Worker::ReleaseJobUnsafe(Job& job)
	{
		jobPool.ReleaseUnsafe(job);
	}

	void Worker::AddJob(Job& job)
	{
		assert(job.BlockCount() == 0uz && "The job is blocked.");

		{
			const auto lock = std::lock_guard(jobQueueMutex);
			jobQueue.push(&job);
		}
		
		IncrementJobQueueVersion();
	}

	void Worker::Work() noexcept
	{
		while (running.load(std::memory_order::relaxed))
		{
			const std::size_t initialJobQueueVersion = jobQueueVersion->load(std::memory_order::acquire);
			if (Job* const job = FindJob())
			{
				Execute(*job);
				Release(*job);
			}
			else
			{
				jobQueueVersion->wait(initialJobQueueVersion, std::memory_order::acquire);
			}
		}
	}

	void Worker::Execute(Job& job) noexcept
	{
		job.Execute();
		job.Task(nullptr);
		job.IncrementVersion();
		job.ProcessDependents([&](Job& dependent)
		{
			if (dependent.Unblock())
			{
				try
				{
					AddJob(dependent);
				}
				catch (...)
				{
					PONY_LOG_X(application->Logger(), std::current_exception(), "On adding job to worker queue. Worker thread: '{}'.", ThreadID());
					Execute(dependent); // Out of order execution because of memory shortage.
				}
			}
		});
	}

	void Worker::Release(Job& job) noexcept
	{
		try
		{
			jobPool.Release(job);
		}
		catch (...)
		{
			PONY_LOG_X(application->Logger(), std::current_exception(), "On adding job to job pool. Worker thread: '{}'.", ThreadID());
			// Unfortunately, the job will be kept alive but not used anymore. May happen on memory shortage.
		}
	}

	Job* Worker::FindJob() noexcept
	{
		Job* const job = GetJob();
		return job ? job : StealJob();
	}

	Job* Worker::GetJob() noexcept
	{
		Job* job;
		{
			const auto lock = std::lock_guard(jobQueueMutex);
			job = TakeJob();
		}

		if (job)
		{
			IncrementJobQueueVersion();
		}

		return job;
	}

	Job* Worker::StealJob() const noexcept
	{
		for (std::size_t i = 1uz; i < workers.size(); ++i)
		{
			const std::size_t workerIndex = (myIndex + i) % workers.size();
			if (Job* const job = workers[workerIndex]->GrabJob())
			{
				return job;
			}
		}

		return nullptr;
	}

	Job* Worker::GrabJob() noexcept
	{
		Job* job = nullptr;
		if (const auto lock = std::unique_lock(jobQueueMutex, std::try_to_lock))
		{
			job = TakeJob();
		}

		if (job)
		{
			IncrementJobQueueVersion();
		}

		return job;
	}

	Job* Worker::TakeJob() noexcept
	{
		if (jobQueue.empty())
		{
			return nullptr;
		}

		Job* const nextJob = jobQueue.front();
		jobQueue.pop();

		return nextJob;
	}

	void Worker::IncrementJobQueueVersion() const noexcept
	{
		jobQueueVersion->fetch_add(1uz, std::memory_order::release);
		jobQueueVersion->notify_one();
	}
}
