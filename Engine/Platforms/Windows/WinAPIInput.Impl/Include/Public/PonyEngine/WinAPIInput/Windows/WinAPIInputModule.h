/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#pragma once

#include "PonyCompiler.h"

import std;

import PonyEngine.Application;

namespace PonyEngine::WinAPIInput
{
	/// @brief Creates a WinAPI input module.
	/// @return WinAPI input module.
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT std::shared_ptr<Application::IModule> CreateWinAPIInputModule();
}
