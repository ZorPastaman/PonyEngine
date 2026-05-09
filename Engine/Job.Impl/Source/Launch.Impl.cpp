/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/Job/JobServiceModule.h"

import PonyEngine.Application.Ext;
import PonyEngine.Job.Impl;

namespace PonyEngine::Job
{
	Application::IModule* GetJobServiceModule()
	{
		static JobServiceModule jobServiceModule;
		return &jobServiceModule;
	}
}
