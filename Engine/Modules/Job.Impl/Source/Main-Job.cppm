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

export module PonyEngine.Job.Impl:Job;

import std;

import PonyEngine.Job;

import :JobID;

export namespace PonyEngine::Job
{
	/// @brief Job.
	class Job final
	{
	public:
		/// @brief Creates a job.
		[[nodiscard("Pure constructor")]]
		Job() noexcept;
		Job(const Job&) = delete;
		Job(Job&&) = delete;

		~Job() noexcept = default;

		/// @brief Gets the version.
		/// @return Version.
		[[nodiscard("Pure function")]]
		std::size_t Version() const noexcept;
		/// @brief Increments the version.
		void IncrementVersion() noexcept;

		/// @brief Waits for the version change.
		/// @param waitedVersion Waited version. The function returns if the current version is different.
		void Wait(std::size_t waitedVersion) const noexcept;

		/// @brief Checks if the job has a task.
		/// @return @a True if it has a task; @a false otherwise.
		[[nodiscard("Pure function")]]
		bool HasTask() const noexcept;
		/// @brief Sets the task.
		/// @param task Task to set. Can be nullptr.
		void Task(ITask* task) noexcept;
		/// @brief Executes a current task.
		/// @note The job must have a task, otherwise the call is not allowed.
		void Execute() const noexcept;

		/// @brief Decrements the block count.
		/// @return @a True if the job is fully unlocked (block count has reached 0); @a false otherwise.
		[[nodiscard("Must be used")]]
		bool Unblock() noexcept;
		/// @brief Gets the block count.
		/// @return Block count.
		[[nodiscard("Pure function")]]
		std::size_t BlockCount() const noexcept;
		/// @brief Sets the block count.
		/// @param blockCount Block count to set.
		void Block(std::size_t blockCount) noexcept;

		/// @brief Adds the dependent.
		/// @param dependent Dependent to add.
		/// @param version Waited version of this job.
		/// @return @a True if the dependent was added; @a false otherwise - the job has a different version.
		[[nodiscard("Must be used")]]
		bool AddDependent(const JobID& dependent, std::size_t version) noexcept;
		/// @brief Process dependents.
		/// @tparam F Invocable type.
		/// @param func Process function.
		/// @note The function clears the dependent list after processing.
		template<std::invocable<const JobID&> F>
		void ProcessDependents(F&& func);

		Job& operator =(const Job&) = delete;
		Job& operator =(Job&&) = delete;

	private:
		std::atomic_size_t version; ///< Job version.
		ITask* task; ///< Job task.

		std::atomic_size_t blockCount; ///< Block count. How many dependencies must be completed before starting this job.
		std::vector<JobID> dependents; ///< Dependents.
		std::mutex dependentMutex; ///< Mutex that must be used while working with the @p dependents.

		static_assert(std::atomic_size_t::is_always_lock_free, "Size_t is not lock-free");
	};
}

namespace PonyEngine::Job
{
	Job::Job() noexcept :
		version{0uz}, 
		task{nullptr},
		blockCount{0uz}
	{
	}

	std::size_t Job::Version() const noexcept
	{
		return version.load(std::memory_order::acquire);
	}

	void Job::IncrementVersion() noexcept
	{
		version.fetch_add(1uz, std::memory_order::release);
		version.notify_all();
	}

	void Job::Wait(const std::size_t waitedVersion) const noexcept
	{
		while (version.load(std::memory_order::acquire) == waitedVersion)
		{
			version.wait(waitedVersion, std::memory_order::acquire);
		}
	}

	bool Job::HasTask() const noexcept
	{
		return task;
	}

	void Job::Task(ITask* const task) noexcept
	{
		this->task = task;
	}

	void Job::Execute() const noexcept
	{
		assert(task && "The task is nullptr.");
		task->Execute();
	}

	bool Job::Unblock() noexcept
	{
		const std::size_t prev = blockCount.fetch_sub(1uz, std::memory_order::release);
		assert(prev > 0uz && "The block count is 0.");

		if (prev == 1uz)
		{
			std::atomic_thread_fence(std::memory_order::acquire);
			return true;
		}

		return false;
	}

	std::size_t Job::BlockCount() const noexcept
	{
		return blockCount.load(std::memory_order::acquire);
	}

	void Job::Block(const std::size_t blockCount) noexcept
	{
		this->blockCount.store(blockCount, std::memory_order::release);
	}

	bool Job::AddDependent(const JobID& dependent, const std::size_t version) noexcept // It may throw, but it's intentionally noexcept to fail the program
	{
		if (Version() != version)
		{
			return false;
		}

		const auto lock = std::lock_guard(dependentMutex);

		if (Version() != version)
		{
			return false;
		}

		dependents.push_back(dependent);
		return true;
	}

	template<std::invocable<const JobID&> F>
	void Job::ProcessDependents(F&& func)
	{
		const auto lock = std::lock_guard(dependentMutex);

		for (const JobID& dependent : dependents)
		{
			std::invoke(std::forward<F>(func), dependent);
		}

		dependents.clear();
	}
}
