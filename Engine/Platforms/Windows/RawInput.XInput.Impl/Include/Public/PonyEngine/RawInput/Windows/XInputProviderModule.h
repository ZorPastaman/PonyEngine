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

namespace PonyEngine::RawInput::XInput::Windows
{
	/// @brief Creates the XInput provider module.
	/// @return XInput provider module.
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT std::shared_ptr<Application::IModule> CreateXInputProviderModule();
}
