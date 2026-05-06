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
	class Worker final
	{
	public:
		[[nodiscard("Pure constructor")]]
		Worker(Application::IApplicationContext& application, std::span<const std::unique_ptr<Worker>> workers, std::size_t myIndex, std::atomic_size_t* jobQueueVersion) noexcept;
		Worker(const Worker&) = delete;
		Worker(Worker&&) = delete;

		~Worker() noexcept = default;

		[[nodiscard("Pure function")]]
		std::thread::id ThreadID() const noexcept;
		void Start();
		void Stop() noexcept;
		void Join() noexcept;

		[[nodiscard("Pure function")]]
		std::pair<Job*, bool> AcquireJob();
		void ReleaseJob(Job& job);
		void ReleaseJobUnsafe(Job& job);
		void AddJob(Job& job);

		Worker& operator =(const Worker&) = delete;
		Worker& operator =(Worker&&) = delete;

	private:
		void Work() noexcept;
		void Execute(Job& job) noexcept;
		void Release(Job& job) noexcept;

		[[nodiscard("Must be used")]]
		Job* FindJob() noexcept;
		[[nodiscard("Must be used")]]
		Job* GetJob() noexcept;
		[[nodiscard("Must be used")]]
		Job* StealJob() const noexcept;
		[[nodiscard("Must be used")]]
		Job* GrabJob() noexcept;
		[[nodiscard("Must be used")]]
		Job* TakeJob() noexcept;

		void IncrementJobQueueVersion() const noexcept;

		Application::IApplicationContext* application;

		std::atomic_bool running;

		std::queue<Job*> jobQueue;
		std::mutex jobQueueMutex;

		JobPool jobPool;

		std::span<const std::unique_ptr<Worker>> workers;
		std::size_t myIndex;

		std::atomic_size_t* jobQueueVersion;

		std::optional<std::thread> thread;

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
		Release(job);
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
