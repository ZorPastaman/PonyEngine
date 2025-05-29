/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: cybercode.smith@pm.me                    *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <iostream>

#include "PonyEngine/Module/API.h"
#include "PonyEngine/Utility/Compiler.h"

export module PonyEngine.Core;

import PonyEngine.Module;

extern "C" void PONY_DLL_EXPORT InitializeModule();
PONY_MODULE_INITIALIZER_DEFAULT(InitializeModule);

void InitializeModule()
{
	std::cout << "Module!\n";
}
