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
		/// @param task Job task. Must be valid till the job completes.
		/// @param dependency Job dependency.
		/// @return Job handle. May be used to wait for the job completion or as a dependency for other jobs.
		/// @note The function is thread-safe.
		JobHandle Schedule(std::move_only_function<void() noexcept> task, const JobHandle& dependency);
		/// @brief Schedules a job for execution.
		/// @param task Job task. Must be valid till the job completes.
		/// @param dependencies Job dependencies.
		/// @return Job handle. May be used to wait for the job completion or as a dependency for other jobs.
		/// @note The function is thread-safe.
		virtual JobHandle Schedule(std::move_only_function<void() noexcept> task, std::span<const JobHandle> dependencies = std::span<const JobHandle>()) = 0;

		/// @brief Puts a cpu thread the function is called on into a sleep till the job is completed.
		/// @param job Job to wait for.
		/// @note The function is thread-safe.
		void Wait(const JobHandle& job) const;
		/// @brief Puts a cpu thread the function is called on into a sleep till the jobs are completed.
		/// @param jobs Jobs to wait for.
		/// @note The function is thread-safe.
		virtual void Wait(std::span<const JobHandle> jobs) const = 0;
		/// @brief Checks if the job is completed.
		/// @param job Job to check.
		/// @return @a True if it's completed; @a false otherwise.
		/// @note The function is thread-safe.
		[[nodiscard("Pure function")]]
		virtual bool IsCompleted(const JobHandle& job) const = 0;
	};
}

namespace PonyEngine::Job
{
	JobHandle IJobService::Schedule(std::move_only_function<void() noexcept> task, const JobHandle& dependency)
	{
		return Schedule(std::move(task), std::span(&dependency, 1uz));
	}

	void IJobService::Wait(const JobHandle& job) const
	{
		Wait(std::span(&job, 1uz));
	}
}
