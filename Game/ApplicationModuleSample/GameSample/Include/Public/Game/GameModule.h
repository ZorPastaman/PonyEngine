#pragma once

#include "PonyEngine/Utility/Compiler.h"

import PonyEngine.Core;

namespace Game
{
	// Module function. It must have PONY_DLL_EXPORT, return PonyEngine::Core::IModule* and take no arguments.
	PONY_DLL_EXPORT PonyEngine::Core::IModule* GetGameModule();
}
