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
		explicit Job(const std::shared_ptr<ITask>& task) noexcept;
		Job(const Job&) = delete;
		Job(Job&&) = delete;

		~Job() noexcept = default;

		[[nodiscard("Pure function")]] 
		virtual JobStatus Status() const noexcept override;

		[[nodiscard("Pure function")]] 
		virtual const std::exception_ptr& Exception() const noexcept override;

		void Wait() const noexcept;

		void Execute();

		void Status(JobStatus status) noexcept;
		void Status(JobStatus status, const std::exception_ptr& exception) noexcept;

		Job& operator =(const Job&) = delete;
		Job& operator =(Job&&) = delete;

	private:
		void UpdateStatus(JobStatus status) noexcept;

		inline static const std::exception_ptr NullptrException = nullptr;

		std::atomic<JobStatus> status;
		std::atomic_bool completed;
		std::exception_ptr exception;
		std::shared_ptr<ITask> task;

		static_assert(std::atomic<JobStatus>::is_always_lock_free, "JobStatus enum is not lock-free");
		static_assert(std::atomic_bool::is_always_lock_free, "Bool is not lock-free");
	};
}

namespace PonyEngine::Job
{
	Job::Job(const std::shared_ptr<ITask>& task) noexcept :
		status{JobStatus::Pending},
		completed{false},
		exception(nullptr),
		task(task)
	{
		assert(task && "The task is nullptr.");
	}

	JobStatus Job::Status() const noexcept
	{
		return status.load(std::memory_order::acquire);
	}

	const std::exception_ptr& Job::Exception() const noexcept
	{
		return status.load(std::memory_order::acquire) >= JobStatus::Failed ? exception : NullptrException;
	}

	void Job::Wait() const noexcept
	{
		while (!completed.load(std::memory_order::acquire))
		{
			completed.wait(false, std::memory_order::acquire);
		}
	}

	void Job::Execute()
	{
		assert(task && "The task is dropped.");
		assert(status.load(std::memory_order::relaxed) == JobStatus::Running && "The status is invalid for executing.");
		task->Execute();
	}

	void Job::Status(const JobStatus status) noexcept
	{
		assert(this->status.load(std::memory_order::relaxed) <= JobStatus::Running && "The status is invalid for changing status.");
		assert(status <= JobStatus::Completed && this->status.load(std::memory_order::relaxed) < status && "The new status is invalid.");
		
		UpdateStatus(status);
	}

	void Job::Status(const JobStatus status, const std::exception_ptr& exception) noexcept
	{
		assert(this->status.load(std::memory_order::relaxed) <= JobStatus::Running && "The status is invalid for changing status.");
		assert(status >= JobStatus::Failed && "The new status is invalid.");
		assert(exception && "The exception is nullptr.");
		this->exception = exception;

		UpdateStatus(status);
	}

	void Job::UpdateStatus(const JobStatus status) noexcept
	{
		this->status.store(status, std::memory_order::release);
		
		if (status >= JobStatus::Completed)
		{
			completed.store(true, std::memory_order::release);
			completed.notify_all();
		}
	}
}
