/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Object/Body.h"

export module PonyEngine.Job:IJobService;

import std;

import :ITask;
import :JobHandle;

export namespace PonyEngine::Job
{
	/// @brief Job service.
	class IJobService
	{
		PONY_INTERFACE_BODY(IJobService)

		/// @brief Gets a worker count.
		/// @return Worker count.
		[[nodiscard("Pure function")]]
		virtual std::size_t WorkerCount() const noexcept = 0;

		/// @brief Schedules a job for execution.
		/// @param task Job task. May be reused but mustn't be scheduled concurrently.
		/// @param dependency Job dependency.
		/// @return Job handle. May be used to wait for the job completion or as a dependency for other jobs.
		JobHandle Schedule(const std::shared_ptr<ITask>& task, const JobHandle& dependency);
		/// @brief Schedules a job for execution.
		/// @param task Job task. May be reused but mustn't be scheduled concurrently.
		/// @param dependencies Job dependencies.
		/// @return Job handle. May be used to wait for the job completion or as a dependency for other jobs.
		virtual JobHandle Schedule(const std::shared_ptr<ITask>& task, std::span<const JobHandle> dependencies = std::span<const JobHandle>()) = 0;

		/// @brief Puts a cpu thread the function is called on into a sleep till the job is completed.
		/// @param job Job to wait for.
		void Wait(const JobHandle& job) const;
		/// @brief Puts a cpu thread the function is called on into a sleep till the jobs are completed.
		/// @param jobs Jobs to wait for.
		virtual void Wait(std::span<const JobHandle> jobs) const = 0;
	};
}

namespace PonyEngine::Job
{
	JobHandle IJobService::Schedule(const std::shared_ptr<ITask>& task, const JobHandle& dependency)
	{
		return Schedule(task, std::span(&dependency, 1uz));
	}

	void IJobService::Wait(const JobHandle& job) const
	{
		Wait(std::span(&job, 1uz));
	}
}
