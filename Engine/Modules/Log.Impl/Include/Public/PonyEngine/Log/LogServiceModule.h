/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#pragma once

#include "PonyEngine/Application/Module.h"

import std;

import PonyEngine.Application;

namespace PonyEngine::Log
{
	/// @brief Creates a log service module.
	/// @return Log service module.
	[[nodiscard("Pure function")]]
	PONY_MODULE_FUNC std::shared_ptr<Application::IModule> CreateLogServiceModule();
}
