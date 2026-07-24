#pragma once

#include "PonyEngine/Macro/Compiler.h"

import std;

import PonyEngine.Application;

namespace Game
{
	// Module function. It must have PONY_DLL_EXPORT, return std::shared_ptr<PonyEngine::Application::IModule> and take no arguments.
	[[nodiscard("Pure function")]]
	PONY_DLL_EXPORT std::shared_ptr<PonyEngine::Application::IModule> GetGameModule();
}
