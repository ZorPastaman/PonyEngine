/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Job.Impl:JobID;

import std;

import PonyEngine.Job;

export namespace PonyEngine::Job
{
	/// @brief Job ID.
	struct JobID final
	{
		std::size_t poolIndex = std::numeric_limits<std::size_t>::max(); ///< Worker/Pool index.
		std::size_t jobIndex = std::numeric_limits<std::size_t>::max(); ///< Job index in the pool.

		/// @brief Checks if the job ID is valid.
		/// @return @a True if it's valid; @a false otherwise.
		[[nodiscard("Pure function")]]
		constexpr bool IsValid() const noexcept;

		[[nodiscard("Pure operator")]]
		constexpr bool operator ==(const JobID& other) const noexcept = default;
	};

	/// @brief Casts the job ID to a job handle.
	/// @param jobId Job ID.
	/// @param version Job handle version.
	/// @return Job handle.
	[[nodiscard("Pure function")]]
	constexpr JobHandle ToJobHandle(const JobID& jobId, std::size_t version) noexcept;
	/// @brief Casts the job handle to a job ID.
	/// @param handle Job handle.
	/// @return Job ID.
	[[nodiscard("Pure function")]]
	constexpr JobID ToJobID(const JobHandle& handle) noexcept;
}

namespace PonyEngine::Job
{
	constexpr bool JobID::IsValid() const noexcept
	{
		return *this != JobID{};
	}

	constexpr JobHandle ToJobHandle(const JobID& jobId, const std::size_t version) noexcept
	{
		return JobHandle{.id = jobId.poolIndex * PONY_ENGINE_JOB_POOL_SIZE + jobId.jobIndex, .version = version};
	}

	constexpr JobID ToJobID(const JobHandle& handle) noexcept
	{
		return JobID{.poolIndex = handle.id / PONY_ENGINE_JOB_POOL_SIZE, .jobIndex = handle.id % PONY_ENGINE_JOB_POOL_SIZE};
	}
}
