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

export module PonyEngine.Job.Impl:JobPool;

import std;

import :Job;

export namespace PonyEngine::Job
{
	/// @brief Job pool.
	class JobPool final
	{
	public:
		[[nodiscard("Pure constructor")]]
		JobPool() noexcept = default;
		JobPool(const JobPool&) = delete;
		JobPool(JobPool&&) = delete;

		~JobPool() noexcept = default;

		/// @brief Acquires a job.
		/// @return Job and a flag that tells if the job is newly created (if @a true).
		[[nodiscard("Must be used")]]
		Job* Acquire();
		/// @brief Releases the job.
		/// @param job Job to release.
		void Release(Job& job);
		/// @brief Releases the job without locking the pool.
		/// @param job Job to release.
		void ReleaseUnsafe(Job& job);

		JobPool& operator =(const JobPool&) = delete;
		JobPool& operator =(JobPool&&) = delete;

	private:
		std::stack<Job*> pool;
		std::mutex poolMutex;
	};
}

namespace PonyEngine::Job
{
	Job* JobPool::Acquire()
	{
		if (const auto lock = std::unique_lock(poolMutex, std::try_to_lock))
		{
			if (!pool.empty())
			{
				Job* const job = pool.top();
				pool.pop();

				return job;
			}
		}

		return nullptr;
	}

	void JobPool::Release(Job& job)
	{
		const auto lock = std::lock_guard(poolMutex);
		ReleaseUnsafe(job);
	}

	void JobPool::ReleaseUnsafe(Job& job)
	{
		assert(!job.HasTask() && "The job has a task.");
		pool.push(&job);
	}
}
