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
		explicit Worker(Application::IApplicationContext& application);
		Worker(const Worker&) = delete;
		Worker(Worker&&) = delete;

		~Worker() noexcept;

		void AddJob(const std::shared_ptr<Job>& job);

		[[nodiscard("Pure function")]]
		std::thread::id ThreadID() const noexcept;
		void Start();
		void Stop() noexcept;

		Worker& operator =(const Worker&) = delete;
		Worker& operator =(Worker&&) = delete;

	private:
		void Work() noexcept;

		[[nodiscard("Must be used")]]
		std::shared_ptr<Job> NextJob() noexcept;

		Application::IApplicationContext* application;

		std::atomic_bool running;
		std::queue<std::shared_ptr<Job>> jobQueue;
		std::mutex jobQueueMutex;
		std::optional<std::thread> thread;
	};
}

namespace PonyEngine::Job
{
	Worker::Worker(Application::IApplicationContext& application) :
		application{&application},
		running{true}
	{
	}

	Worker::~Worker() noexcept
	{
		Stop();

		if (thread) [[likely]]
		{
			thread->join();
		}
	}

	void Worker::AddJob(const std::shared_ptr<Job>& job)
	{
		assert(job && "The job is nullptr.");
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
		assert(running.load(std::memory_order::relaxed) && "The worder is stopped.");
		thread = std::thread(&Worker::Work, this);
	}

	void Worker::Stop() noexcept
	{
		running.store(false, std::memory_order::relaxed);
	}

	void Worker::Work() noexcept
	{
		while (running.load(std::memory_order::relaxed))
		{
			if (const std::shared_ptr<Job> job = NextJob())
			{
				job->Status(JobStatus::Running);
				try
				{
					job->Execute();
				}
				catch (...)
				{
					const std::exception_ptr exception = std::current_exception();
					PONY_LOG_X(application->Logger(), exception, "On executing job. Address: '0x{:X}'.", reinterpret_cast<std::uintptr_t>(static_cast<IJob*>(job.get())));
					job->Status(JobStatus::Failed, exception);
					continue;
				}
				job->Status(JobStatus::Completed);
			}
		}
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
}
