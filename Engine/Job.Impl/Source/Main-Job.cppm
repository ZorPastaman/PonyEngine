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

export namespace PonyEngine::Job
{
	class Job final : public IJob
	{
	public:
		[[nodiscard("Pure constructor")]]
		Job(const std::shared_ptr<ITask>& task, JobStatus status, std::size_t blockCount) noexcept;
		Job(const Job&) = delete;
		Job(Job&&) = delete;

		~Job() noexcept = default;

		[[nodiscard("Pure function")]] 
		virtual JobStatus Status() const noexcept override;
		void Status(JobStatus status) noexcept;

		void Wait() const noexcept;

		void Execute() noexcept;

		[[nodiscard("Must be used")]]
		bool Unblock() noexcept;
		[[nodiscard("Must be used")]]
		bool AddDependent(const std::shared_ptr<Job>& dependent) const;
		void RemoveDependent(const std::shared_ptr<Job>& dependent) const noexcept;
		void IterateDependents(const std::function<void(const std::shared_ptr<Job>&)>& func) const;

		Job& operator =(const Job&) = delete;
		Job& operator =(Job&&) = delete;

	private:
		inline static const std::exception_ptr NullptrException = nullptr;

		std::atomic<JobStatus> status;
		std::atomic_bool completed;
		std::shared_ptr<ITask> task;

		std::atomic_size_t blockCount;
		mutable std::vector<std::shared_ptr<Job>> dependents;
		mutable std::mutex dependencyMutex;

		static_assert(std::atomic<JobStatus>::is_always_lock_free, "JobStatus enum is not lock-free");
		static_assert(std::atomic_bool::is_always_lock_free, "Bool is not lock-free");
		static_assert(std::atomic_size_t::is_always_lock_free, "Size_t is not lock-free");
	};
}

namespace PonyEngine::Job
{
	Job::Job(const std::shared_ptr<ITask>& task, const JobStatus status, const std::size_t blockCount) noexcept :
		status{status},
		completed{false},
		task(task),
		blockCount{blockCount}
	{
		assert(this->task && "The task is nullptr.");
	}

	JobStatus Job::Status() const noexcept
	{
		return status.load(std::memory_order::acquire);
	}

	void Job::Status(const JobStatus status) noexcept
	{
		assert(status >= this->status.load(std::memory_order::relaxed) && "The new status is invalid.");

		this->status.store(status, std::memory_order::release);
		if (status >= JobStatus::Completed)
		{
			completed.store(true, std::memory_order::release);
			completed.notify_all();
		}
	}

	void Job::Wait() const noexcept
	{
		while (!completed.load(std::memory_order::acquire))
		{
			completed.wait(false, std::memory_order::acquire);
		}
	}

	void Job::Execute() noexcept
	{
		assert(status.load(std::memory_order::relaxed) == JobStatus::Running && "The status is invalid for executing.");
		task->Execute();
	}

	bool Job::Unblock() noexcept
	{
		const std::size_t prev = blockCount.fetch_sub(1uz, std::memory_order::relaxed);
		assert(prev > 0uz && "The block count is 0.");
		return prev == 1uz;
	}

	bool Job::AddDependent(const std::shared_ptr<Job>& dependent) const
	{
		assert(dependent && "The dependent is nullptr.");

		if (completed.load(std::memory_order::relaxed))
		{
			return false;
		}

		const auto lock = std::lock_guard(dependencyMutex);

		if (completed.load(std::memory_order::relaxed))
		{
			return false;
		}

		dependents.push_back(dependent);
		return true;
	}

	void Job::RemoveDependent(const std::shared_ptr<Job>& dependent) const noexcept
	{
		const auto lock = std::lock_guard(dependencyMutex);

		if (const auto position = std::ranges::find(dependents, dependent); position != dependents.cend()) [[likely]]
		{
			dependents.erase(position);
		}
	}

	void Job::IterateDependents(const std::function<void(const std::shared_ptr<Job>&)>& func) const
	{
		const auto lock = std::lock_guard(dependencyMutex);

		for (const std::shared_ptr<Job>& dependent : dependents)
		{
			func(dependent);
		}
	}
}
