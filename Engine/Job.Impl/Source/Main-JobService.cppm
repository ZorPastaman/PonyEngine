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

		virtual std::shared_ptr<IJob> Schedule(const std::shared_ptr<ITask>& task, std::span<const IJob* const> dependencies) override;

		virtual void Wait(std::span<const IJob* const> jobs) const override;

	private:
		Application::IApplicationContext* application;

		std::vector<std::unique_ptr<Worker>> workers;
		std::atomic_size_t targetWorkerIndex;

		static_assert(std::atomic_size_t::is_always_lock_free, "Size_t is not lock-free");
	};
}

namespace PonyEngine::Job
{
	JobService::JobService(Application::IApplicationContext& application) :
		application{&application},
		targetWorkerIndex(0uz)
	{
		const std::size_t concurrency = std::thread::hardware_concurrency();
		const std::size_t threadCount = std::max(Math::DifferenceClamp(concurrency, std::size_t{PONY_ENGINE_JOB_RESERVED_THREAD_COUNT}), std::size_t{PONY_ENGINE_JOB_MIN_THREAD_COUNT});

		PONY_LOG(this->application->Logger(), Log::LogType::Info, "Creating workers... Thread count: '{}'; Hardware concurrency: '{}'.", threadCount, concurrency);
		workers.reserve(threadCount);
		for (std::size_t i = 0uz; i < threadCount; ++i)
		{
			workers.push_back(std::make_unique<Worker>(*this->application));
		}
		for (const std::unique_ptr<Worker>& worker : workers)
		{
			worker->Start();
			PONY_LOG(this->application->Logger(), Log::LogType::Info, "Worker thread started. ID: '{}'.", worker->ThreadID());
		}
		PONY_LOG(this->application->Logger(), Log::LogType::Info, "Creating workers done.");
	}

	JobService::~JobService() noexcept
	{
		PONY_LOG(this->application->Logger(), Log::LogType::Info, "Destroying workers...");
		for (std::size_t i = workers.size(); i-- > 0uz; )
		{
			PONY_LOG(this->application->Logger(), Log::LogType::Info, "Stopping worker thread ID: '{}'.", workers[i]->ThreadID());
			workers[i]->Stop();
		}
		for (std::size_t i = workers.size(); i-- > 0uz; )
		{
			workers[i].reset();
		}
		PONY_LOG(this->application->Logger(), Log::LogType::Info, "Destroying workers done.");
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

	std::shared_ptr<IJob> JobService::Schedule(const std::shared_ptr<ITask>& task, const std::span<const IJob* const> dependencies)
	{
		if (dependencies.empty())
		{
			const std::size_t workerIndex = targetWorkerIndex.fetch_add(1uz, std::memory_order::relaxed) % workers.size();
			const auto job = std::make_shared<Job>(task);
			workers[workerIndex]->AddJob(job);

			return job;
		}
		else
		{
			// TODO: Add dependency support
			throw std::invalid_argument("Not supported");
		}
	}

	void JobService::Wait(const std::span<const IJob* const> jobs) const
	{
		// TODO: Implement
	}
}
