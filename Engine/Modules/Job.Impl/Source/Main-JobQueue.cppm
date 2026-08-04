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

export module PonyEngine.Job.Impl:JobQueue;

import std;

import :Job;

export namespace PonyEngine::Job
{
	/// @brief Job queue.
	class JobQueue final
	{
	public:
		[[nodiscard("Pure constructor")]]
		JobQueue() noexcept;
		JobQueue(const JobQueue&) = delete;
		JobQueue(JobQueue&&) = delete;

		~JobQueue() noexcept = default;

		/// @brief Gets a next job.
		/// @return Next job.
		[[nodiscard("Must be used")]]
		JobID GetJob() noexcept;
		/// @brief Tries to steal a next job.
		/// @return Next job.
		[[nodiscard("Must be used")]]
		JobID StealJob() noexcept;

		/// @brief Adds the job.
		/// @param job Job to add.
		void AddJob(const JobID& job) noexcept;

		JobQueue& operator =(const JobQueue&) = delete;
		JobQueue& operator =(JobQueue&&) = delete;

	private:
		/// @brief Gets a next job.
		/// @return Next job.
		[[nodiscard("Must be used")]]
		JobID TakeJob() noexcept;

		std::array<JobID, PONY_ENGINE_JOB_POOL_SIZE> queue; ///< Job queue.
		std::size_t head; ///< Job queue head.
		std::size_t tail; ///< Job queue tail.
		std::mutex mutex; ///< Mutex.
	};
}

namespace PonyEngine::Job
{
	JobQueue::JobQueue() noexcept :
		head{0uz},
		tail{0uz}
	{
	}

	JobID JobQueue::GetJob() noexcept
	{
		const auto lock = std::lock_guard(mutex);
		return TakeJob();
	}

	JobID JobQueue::StealJob() noexcept
	{
		if (const auto lock = std::unique_lock(mutex, std::try_to_lock))
		{
			return TakeJob();
		}

		return JobID{};
	}

	void JobQueue::AddJob(const JobID& job) noexcept
	{
		const auto lock = std::lock_guard(mutex);
		queue[tail++] = job;
		tail %= PONY_ENGINE_JOB_POOL_SIZE;
	}

	JobID JobQueue::TakeJob() noexcept
	{
		if (head == tail)
		{
			return JobID{};
		}

		const JobID job = queue[head++];
		head %= PONY_ENGINE_JOB_POOL_SIZE;

		return job;
	}
}
