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
	/// @brief Job service.
	class JobService final : public Application::IService, private IJobService
	{
	public:
		/// @brief Creates a job service.
		/// @param application Application context.
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
		[[nodiscard("Pure function")]]
		virtual bool IsCompleted(const JobHandle& job) const override;

	private:
		/// @brief Empty task. It's used in case of an error.
		class EmptyTask final : public ITask
		{
		public:
			virtual void Execute() noexcept override
			{
			}
		};

		/// @brief Adds the job to the worker queue.
		/// @param job Job to add.
		/// @param worker Worker.
		void AddJobToWorker(Job& job, Worker& worker);

		/// @brief Finishes the workers.
		/// @param count How many workers to finish.
		void Finish(std::size_t count) noexcept;

		/// @brief Casts the job from a handle to a native job.
		/// @param job Job from a handle.
		/// @return Native job.
		[[nodiscard("Pure function")]]
		static const Job* ToNativeJob(const void* job);

		Application::IApplicationContext* application; ///< Application context.

		std::vector<std::unique_ptr<Worker>> workers; ///< Workers.
		std::atomic_size_t targetWorkerIndex; ///< Target worker index. Used and incremented on scheduling a new job.

		std::atomic_size_t jobQueueVersion; ///< Job queue version. Must be incremented each time when a queue of a worker is modified.

		std::vector<std::unique_ptr<Job>> jobs; ///< Jobs. Used to keep all the jobs alive so that other parts of the code may use simple pointers.
		std::mutex jobsMutex; ///< Mutex that must be used on using the @p jobs.

		std::shared_ptr<EmptyTask> emptyTask; ///< Empty task.

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
		Worker& worker = *workers[workerIndex];
		const auto [job, isNew] = worker.AcquireJob();
		if (isNew)
		{
			const auto lock = std::lock_guard(jobsMutex);
			jobs.push_back(std::unique_ptr<Job>(job));
		}
		const std::size_t version = job->Version();
		job->Task(task);
		job->Block(dependencies.size());

		const auto handle = JobHandle(job, version);

		if (dependencies.empty())
		{
			AddJobToWorker(*job, worker);
		}
		else
		{
			for (std::size_t i = 0uz; i < dependencies.size(); ++i)
			{
				const JobHandle& dependency = dependencies[i];

				bool isAdded;
				try
				{
					isAdded = ToNativeJob(dependency.data)->AddDependent(*job, dependency.version);
				}
				catch (...)
				{
					job->Task(emptyTask); // Sets the empty task so that the job won't do anything but will be reused eventually.
					for (; i < dependencies.size(); ++i)
					{
						if (job->Unblock())
						{
							worker.ReleaseJob(*job); // It may throw. Unfortunately, it will keep the job alive but not reused. It may happen only on memory shortage.
						}
					}

					throw;
				}

				if (!isAdded && job->Unblock())
				{
					AddJobToWorker(*job, worker);
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

	bool JobService::IsCompleted(const JobHandle& job) const
	{
		if (ToNativeJob(job.data)->Version() == job.version)
		{
			return false;
		}

		std::atomic_thread_fence(std::memory_order::acquire);
		return true;
	}

	void JobService::AddJobToWorker(Job& job, Worker& worker)
	{
		try
		{
			worker.AddJob(job);
		}
		catch (...)
		{
			worker.ReleaseJob(job); // It may throw. Unfortunately, it will keep the job alive but not reused. It may happen only on memory shortage.
			throw;
		}
	}

	void JobService::Finish(const std::size_t count) noexcept
	{
		PONY_LOG(application->Logger(), Log::LogType::Info, "Destroying workers...");
		for (std::size_t i = count; i-- > 0uz; )
		{
			PONY_LOG(application->Logger(), Log::LogType::Info, "Stopping worker thread ID: '{}'.", workers[i]->ThreadID());
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
		PONY_LOG(application->Logger(), Log::LogType::Info, "Destroying workers done.");
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
