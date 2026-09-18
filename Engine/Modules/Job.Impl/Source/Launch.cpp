/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#include "PonyEngine/Application/Module.h"
#include "PonyEngine/Job/JobServiceModule.h"

PONY_ENGINE_MODULE(PonyEngine::Job::CreateJobServiceModule, PonyEngineJobService, PONY_ENGINE_JOB_ORDER);
