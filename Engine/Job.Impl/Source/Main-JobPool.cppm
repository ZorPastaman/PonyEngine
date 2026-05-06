/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Job.Impl:JobPool;

import std;

import :Job;

export namespace PonyEngine::Job
{
	class JobPool final
	{
	public:
		[[nodiscard("Pure constructor")]]
		JobPool() noexcept = default;
		JobPool(const JobPool&) = delete;
		JobPool(JobPool&&) = delete;

		~JobPool() noexcept = default;

		[[nodiscard("Must be used")]]
		std::pair<Job*, bool> Acquire();
		void Release(Job& job);
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
	std::pair<Job*, bool> JobPool::Acquire()
	{
		{
			const auto lock = std::lock_guard(poolMutex);
			if (!pool.empty())
			{
				Job* const job = pool.top();
				pool.pop();
				
				return std::pair(job, false);
			}
		}

		return std::pair(new Job(), true);
	}

	void JobPool::Release(Job& job)
	{
		const auto lock = std::lock_guard(poolMutex);
		ReleaseUnsafe(job);
	}

	void JobPool::ReleaseUnsafe(Job& job)
	{
		pool.push(&job);
	}
}
