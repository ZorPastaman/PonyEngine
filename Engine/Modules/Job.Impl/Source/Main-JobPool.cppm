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
		/// @brief Creates a job pool
		[[nodiscard("Pure constructor")]]
		JobPool();
		JobPool(const JobPool&) = delete;
		JobPool(JobPool&&) = delete;

		~JobPool() noexcept = default;

		/// @brief Tries to acquire a job.
		/// @return Job index or std::nullopt if the pool is empty.
		[[nodiscard("Must be used")]]
		std::optional<std::size_t> AcquireJob() noexcept;
		/// @brief Releases a job.
		/// @param index Job index.
		void ReleaseJob(std::size_t index) noexcept;

		/// @brief Gets a job.
		/// @param index Job index.
		/// @return Job.
		[[nodiscard("Pure function")]]
		Job& GetJob(std::size_t index) noexcept;

		JobPool& operator =(const JobPool&) = delete;
		JobPool& operator =(JobPool&&) = delete;

	private:
		/// @brief Checks if a job at @p index is free.
		/// @param index Job index.
		/// @return @a True if it's free; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool IsFree(std::size_t index) const noexcept;

		std::array<Job, PONY_ENGINE_JOB_POOL_SIZE> jobs; ///< Jobs.
		std::array<std::size_t, PONY_ENGINE_JOB_POOL_SIZE> freeJobs; ///< Indices of free jobs.
		std::size_t freeJobCount; ///< Free job count.
		std::mutex poolMutex; ///< Pool mutex.
	};
}

namespace PonyEngine::Job
{
	JobPool::JobPool() :
		freeJobCount{PONY_ENGINE_JOB_POOL_SIZE}
	{
		std::ranges::iota(freeJobs, 0uz);
	}

	std::optional<std::size_t> JobPool::AcquireJob() noexcept
	{
		if (const auto lock = std::unique_lock(poolMutex, std::try_to_lock))
		{
			return freeJobCount > 0uz ? std::optional(freeJobs[--freeJobCount]) : std::nullopt;
		}

		return std::nullopt;
	}

	void JobPool::ReleaseJob(const std::size_t index) noexcept
	{
		const auto lock = std::lock_guard(poolMutex);
		assert(!IsFree(index) && "Tried to release invalid job.");
		freeJobs[freeJobCount++] = index;
	}

	Job& JobPool::GetJob(const std::size_t index) noexcept
	{
		return jobs[index];
	}

	bool JobPool::IsFree(const std::size_t index) const noexcept
	{
		for (std::size_t i = 0uz; i < freeJobCount; ++i)
		{
			if (freeJobs[i] == index)
			{
				return true;
			}
		}

		return false;
	}
}
