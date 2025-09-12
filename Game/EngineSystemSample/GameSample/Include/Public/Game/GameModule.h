#pragma once

#include "PonyEngine/Utility/Compiler.h"

import PonyEngine.Application;

namespace Game
{
	// Module function. It must have PONY_DLL_EXPORT, return PonyEngine::Application::IModule* and take no arguments.
	PONY_DLL_EXPORT PonyEngine::Application::IModule* GetGameModule();
}
