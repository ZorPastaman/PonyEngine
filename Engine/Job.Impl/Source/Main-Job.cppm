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
	class Job final
	{
	public:
		[[nodiscard("Pure constructor")]]
		Job() noexcept;
		Job(const Job&) = delete;
		Job(Job&&) = delete;

		~Job() noexcept = default;

		[[nodiscard("Pure function")]]
		std::size_t Version() const noexcept;
		void IncrementVersion() noexcept;

		void Wait(std::size_t waitedVersion) const noexcept;

		[[nodiscard("Pure function")]]
		bool HasTask() const noexcept;
		void Task(const std::shared_ptr<ITask>& task) noexcept;
		void Execute() noexcept;

		[[nodiscard("Must be used")]]
		bool Unblock() noexcept;
		void Block(std::size_t blockCount) noexcept;

		[[nodiscard("Must be used")]]
		bool AddDependent(Job& dependent, std::size_t version) const;
		void ProcessDependents(const std::function<void(Job&)>& func);

		Job& operator =(const Job&) = delete;
		Job& operator =(Job&&) = delete;

	private:
		inline static const std::exception_ptr NullptrException = nullptr;

		std::atomic_size_t version;
		std::shared_ptr<ITask> task;

		std::atomic_size_t blockCount;
		mutable std::vector<Job*> dependents;
		mutable std::mutex dependencyMutex;

		static_assert(std::atomic_size_t::is_always_lock_free, "Size_t is not lock-free");
	};
}

namespace PonyEngine::Job
{
	Job::Job() noexcept :
		version{0uz},
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
		return task.get();
	}

	void Job::Task(const std::shared_ptr<ITask>& task) noexcept
	{
		this->task = task;
	}

	void Job::Execute() noexcept
	{
		assert(task && "The task is nullptr.");
		task->Execute();
	}

	bool Job::Unblock() noexcept
	{
		const std::size_t prev = blockCount.fetch_sub(1uz, std::memory_order::acq_rel);
		assert(prev > 0uz && "The block count is 0.");
		return prev == 1uz;
	}

	void Job::Block(const std::size_t blockCount) noexcept
	{
		this->blockCount.store(blockCount, std::memory_order::release);
	}

	bool Job::AddDependent(Job& dependent, const std::size_t version) const
	{
		if (Version() != version)
		{
			return false;
		}

		const auto lock = std::lock_guard(dependencyMutex);

		if (Version() != version)
		{
			return false;
		}

		dependents.push_back(&dependent);
		return true;
	}

	void Job::ProcessDependents(const std::function<void(Job&)>& func)
	{
		const auto lock = std::lock_guard(dependencyMutex);

		for (Job* const dependent : dependents)
		{
			func(*dependent);
		}

		dependents.clear();
	}
}
