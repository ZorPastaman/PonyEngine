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

import :ITask;
import :JobHandle;

export namespace PonyEngine::Job
{
	class IJobService
	{
		PONY_INTERFACE_BODY(IJobService)

		[[nodiscard("Pure function")]]
		virtual std::size_t WorkerCount() const noexcept = 0;

		JobHandle Schedule(const std::shared_ptr<ITask>& task, const JobHandle& dependency);
		virtual JobHandle Schedule(const std::shared_ptr<ITask>& task, std::span<const JobHandle> dependencies = std::span<const JobHandle>()) = 0;

		void Wait(const JobHandle& job) const;
		virtual void Wait(std::span<const JobHandle> jobs) const = 0;
	};
}

namespace PonyEngine::Job
{
	JobHandle IJobService::Schedule(const std::shared_ptr<ITask>& task, const JobHandle& dependency)
	{
		return Schedule(task, std::span(&dependency, 1uz));
	}

	void IJobService::Wait(const JobHandle& job) const
	{
		Wait(std::span(&job, 1uz));
	}
}
