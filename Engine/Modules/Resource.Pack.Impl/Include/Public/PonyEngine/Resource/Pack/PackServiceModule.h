/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#pragma once

#include "PonyEngine/Macro/Compiler.h"

import std;

import PonyEngine.Application;

namespace PonyEngine::Resource::Pack
{
	/// @brief Creates the pack service module.
	/// @return Pack service module.
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT std::shared_ptr<Application::IModule> CreatePackServiceModule();
}
