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

export namespace PonyEngine::Job
{
	class Worker final
	{
	public:
		[[nodiscard("Pure constructor")]]
		Worker(Application::IApplicationContext& application, std::span<const std::unique_ptr<Worker>> workers, std::size_t myIndex);
		Worker(const Worker&) = delete;
		Worker(Worker&&) = delete;

		~Worker() noexcept = default;

		void AddJob(const std::shared_ptr<Job>& job);

		[[nodiscard("Pure function")]]
		std::thread::id ThreadID() const noexcept;
		void Start();
		void Stop() noexcept;
		void Join() noexcept;

		Worker& operator =(const Worker&) = delete;
		Worker& operator =(Worker&&) = delete;

	private:
		void Work() noexcept;
		void Execute(Job& job) noexcept;

		[[nodiscard("Must be used")]]
		std::shared_ptr<Job> FindJob() noexcept;
		[[nodiscard("Must be used")]]
		std::shared_ptr<Job> NextJob() noexcept;
		[[nodiscard("Must be used")]]
		std::shared_ptr<Job> StealJob() const noexcept;

		Application::IApplicationContext* application;

		std::atomic_bool running;
		std::queue<std::shared_ptr<Job>> jobQueue;
		std::span<const std::unique_ptr<Worker>> workers;
		std::size_t myIndex;
		std::mutex jobQueueMutex;
		std::optional<std::thread> thread;
	};
}

namespace PonyEngine::Job
{
	Worker::Worker(Application::IApplicationContext& application, const std::span<const std::unique_ptr<Worker>> workers, const std::size_t myIndex) :
		application{&application},
		running{true},
		workers(workers),
		myIndex{myIndex}
	{
		assert(this->myIndex < this->workers.size() && "Wrong worker index.");
	}

	void Worker::AddJob(const std::shared_ptr<Job>& job)
	{
		assert(job && "The job is nullptr.");
		assert(job->Status() == JobStatus::Pending && "The job has wrong status.");
		const auto lock = std::lock_guard(jobQueueMutex);
		jobQueue.push(job);
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

	void Worker::Work() noexcept
	{
		while (running.load(std::memory_order::relaxed))
		{
			if (const std::shared_ptr<Job> job = FindJob())
			{
				Execute(*job);
			}
		}
	}

	void Worker::Execute(Job& job) noexcept
	{
		assert(job.Status() == JobStatus::Pending && "The job has wrong status.");
		job.Status(JobStatus::Running);
		job.Execute();
		job.Status(JobStatus::Completed);

		job.IterateDependents([&](const std::shared_ptr<Job>& dependent)
		{
			if (dependent->Unblock())
			{
				dependent->Status(JobStatus::Pending);
				try
				{
					AddJob(dependent);
				}
				catch (...)
				{
					PONY_LOG_X(application->Logger(), std::current_exception(), "On adding job to worker queue. Worker thread: '{}'.", ThreadID());
					Execute(*dependent); // Out of order execution because of memory shortage.
				}
			}
		});
	}

	std::shared_ptr<Job> Worker::FindJob() noexcept
	{
		const std::shared_ptr<Job> job = NextJob();
		return job ? job : StealJob();
	}

	std::shared_ptr<Job> Worker::NextJob() noexcept
	{
		const auto lock = std::lock_guard(jobQueueMutex);
		
		if (jobQueue.empty())
		{
			return nullptr;
		}

		const std::shared_ptr<Job> nextJob = jobQueue.front();
		jobQueue.pop();

		return nextJob;
	}

	std::shared_ptr<Job> Worker::StealJob() const noexcept
	{
		for (std::size_t i = 1uz; i < workers.size(); ++i)
		{
			const std::size_t workerIndex = (myIndex + i) % workers.size();
			if (const std::shared_ptr<Job> job = workers[workerIndex]->NextJob())
			{
				return job;
			}
		}

		return nullptr;
	}
}
