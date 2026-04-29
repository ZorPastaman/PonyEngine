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

import :IJob;
import :ITask;

export namespace PonyEngine::Job
{
	class IJobService
	{
		PONY_INTERFACE_BODY(IJobService)

		std::shared_ptr<IJob> Schedule(const std::shared_ptr<ITask>& task, const IJob& dependency);
		virtual std::shared_ptr<IJob> Schedule(const std::shared_ptr<ITask>& task, std::span<const IJob* const> dependencies = std::span<const IJob* const>()) = 0;

		void Wait(const IJob& job) const;
		virtual void Wait(std::span<const IJob* const> jobs) const = 0;
	};
}

namespace PonyEngine::Job
{
	std::shared_ptr<IJob> IJobService::Schedule(const std::shared_ptr<ITask>& task, const IJob& dependency)
	{
		const IJob* const dep = &dependency;
		return Schedule(task, std::span(&dep, 1uz));
	}

	void IJobService::Wait(const IJob& job) const
	{
		const IJob* const wait = &job;
		Wait(std::span(&wait, 1uz));
	}
}
