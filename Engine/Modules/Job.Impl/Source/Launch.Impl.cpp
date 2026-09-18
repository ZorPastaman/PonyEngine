/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/Job/JobServiceModule.h"

import PonyEngine.Job.Impl;

namespace PonyEngine::Job
{
	std::shared_ptr<Application::IModule> CreateJobServiceModule()
	{
		return std::make_shared<JobServiceModule>();
	}
}
