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

export module PonyEngine.Job.Impl:JobService;

import std;

import PonyEngine.Application.Ext;
import PonyEngine.Job;
import PonyEngine.Log;
import PonyEngine.Math;

import :Job;
import :Worker;

export namespace PonyEngine::Job
{
	class JobService final : public Application::IService, private IJobService
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit JobService(Application::IApplicationContext& application);
		JobService(const JobService&) = delete;
		JobService(JobService&&) = delete;

		~JobService() noexcept;

		virtual void Begin() override;
		virtual void End() override;

		virtual void AddInterfaces(Application::IServiceInterfaceAdder& adder) override;

		[[nodiscard("Pure function")]]
		virtual std::size_t WorkerCount() const noexcept override;

		virtual JobHandle Schedule(const std::shared_ptr<ITask>& task, std::span<const JobHandle> dependencies) override;

		virtual void Wait(std::span<const JobHandle> jobs) const override;

	private:
		class EmptyTask final : public ITask
		{
		public:
			virtual void Execute() noexcept override
			{
			}
		};

		void AddJobToWorker(Job& job, std::size_t workerIndex);

		void Finish(std::size_t count) noexcept;

		[[nodiscard("Pure function")]]
		static const Job* ToNativeJob(const void* job);

		Application::IApplicationContext* application;

		std::vector<std::unique_ptr<Worker>> workers;
		std::atomic_size_t targetWorkerIndex;

		std::atomic_size_t jobQueueVersion;

		std::vector<std::unique_ptr<Job>> jobs;
		std::mutex jobsMutex;

		std::shared_ptr<EmptyTask> emptyTask;

		static_assert(std::atomic_size_t::is_always_lock_free, "Size_t is not lock-free");
	};
}

namespace PonyEngine::Job
{
	JobService::JobService(Application::IApplicationContext& application) :
		application{&application},
		targetWorkerIndex{0uz},
		jobQueueVersion{0uz},
		emptyTask(std::make_shared<EmptyTask>())
	{
		constexpr std::size_t jobReserveCount = 64uz;

		const std::size_t concurrency = std::thread::hardware_concurrency();
		const std::size_t threadCount = std::max(Math::DifferenceClamp(concurrency, std::size_t{PONY_ENGINE_JOB_RESERVED_THREAD_COUNT}), std::size_t{PONY_ENGINE_JOB_MIN_THREAD_COUNT});

		PONY_LOG(this->application->Logger(), Log::LogType::Info, "Creating workers... Thread count: '{}'; Hardware concurrency: '{}'.", threadCount, concurrency);
		workers.resize(threadCount);
		jobs.reserve(threadCount * jobReserveCount);

		for (std::size_t i = 0uz; i < threadCount; ++i)
		{
			workers[i] = std::make_unique<Worker>(*this->application, workers, i, &jobQueueVersion);
		}

		for (std::size_t i = 0uz; i < threadCount; ++i)
		{
			for (std::size_t j = 0uz; j < jobReserveCount; ++j)
			{
				const auto job = new Job();
				jobs.push_back(std::unique_ptr<Job>(job));
				workers[i]->ReleaseJobUnsafe(*job);
			}
		}

		for (std::size_t i = 0uz; i < threadCount; ++i)
		{
			try
			{
				const std::unique_ptr<Worker>& worker = workers[i];
				worker->Start();
				PONY_LOG(this->application->Logger(), Log::LogType::Info, "Worker thread started. ID: '{}'.", worker->ThreadID());
			}
			catch (...)
			{
				PONY_LOG_X(this->application->Logger(), std::current_exception(), "On starting worker thread.");
				Finish(i);
				throw;
			}
		}
		PONY_LOG(this->application->Logger(), Log::LogType::Info, "Creating workers done.");
	}

	JobService::~JobService() noexcept
	{
		Finish(workers.size());
	}

	void JobService::Begin()
	{
	}

	void JobService::End()
	{
	}

	void JobService::AddInterfaces(Application::IServiceInterfaceAdder& adder)
	{
		adder.AddInterface<IJobService>(*this);
	}

	std::size_t JobService::WorkerCount() const noexcept
	{
		return workers.size();
	}

	JobHandle JobService::Schedule(const std::shared_ptr<ITask>& task, const std::span<const JobHandle> dependencies)
	{
#ifndef NDEBUG
		if (!task) [[unlikely]]
		{
			throw std::invalid_argument("Task is nullptr");
		}
#endif

		const std::size_t workerIndex = targetWorkerIndex.fetch_add(1uz, std::memory_order::relaxed) % workers.size();
		const auto [job, isNew] = workers[workerIndex]->AcquireJob();
		if (isNew)
		{
			const auto lock = std::lock_guard(jobsMutex);
			jobs.push_back(std::unique_ptr<Job>(job));
		}
		job->Task(task);
		job->Block(dependencies.size());

		const auto handle = JobHandle(job, job->Version());

		if (dependencies.empty())
		{
			AddJobToWorker(*job, workerIndex);
		}
		else
		{
			for (std::size_t i = 0uz; i < dependencies.size(); ++i)
			{
				const JobHandle& dependency = dependencies[i];

				try
				{
					if (!ToNativeJob(dependency.data)->AddDependent(*job, dependency.version) && job->Unblock())
					{
						AddJobToWorker(*job, workerIndex);
					}
				}
				catch (...)
				{
					job->Task(emptyTask);
					for (; i < dependencies.size(); ++i)
					{
						if (job->Unblock())
						{
							workers[workerIndex]->ReleaseJob(*job);
						}
					}

					throw;
				}
			}
		}

		return handle;
	}

	void JobService::Wait(const std::span<const JobHandle> jobs) const
	{
		for (const JobHandle& job : jobs)
		{
			ToNativeJob(job.data)->Wait(job.version);
		}
	}

	void JobService::AddJobToWorker(Job& job, const std::size_t workerIndex)
	{
		try
		{
			workers[workerIndex]->AddJob(job);
		}
		catch (...)
		{
			workers[workerIndex]->ReleaseJob(job);
			throw;
		}
	}

	void JobService::Finish(const std::size_t count) noexcept
	{
		PONY_LOG(this->application->Logger(), Log::LogType::Info, "Destroying workers...");
		for (std::size_t i = count; i-- > 0uz; )
		{
			PONY_LOG(this->application->Logger(), Log::LogType::Info, "Stopping worker thread ID: '{}'.", workers[i]->ThreadID());
			workers[i]->Stop();
		}

		jobQueueVersion.fetch_add(1uz, std::memory_order::release);
		jobQueueVersion.notify_all();

		for (std::size_t i = count; i-- > 0uz; )
		{
			workers[i]->Join();
		}

		for (std::size_t i = count; i-- > 0uz; )
		{
			workers[i].reset();
		}
		PONY_LOG(this->application->Logger(), Log::LogType::Info, "Destroying workers done.");
	}

	const Job* JobService::ToNativeJob(const void* const job)
	{
#ifndef NDEBUG
		if (!job) [[unlikely]]
		{
			throw std::invalid_argument("Invalid job");
		}
#endif

		return static_cast<const Job*>(job);
	}
}
