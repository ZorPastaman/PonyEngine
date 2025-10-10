#pragma once

#include "PonyEngine/Macro/Compiler.h"

import PonyEngine.Application.Extension;

namespace Game
{
	// Module function. It must have PONY_DLL_EXPORT, return PonyEngine::Application::IModule* and take no arguments.
	PONY_DLL_EXPORT PonyEngine::Application::IModule* GetGameModule();
}
