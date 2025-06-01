/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: cybercode.smith@pm.me                    *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <cstdint>
#include <iostream>

#include "PonyEngine/Module/API.h"

export module PonyEngine.Application:Bootstrap;

import PonyEngine.Module;

export namespace PonyEngine::Application
{
	/// @brief Initializes modules.
	void InitializeModules();
}

namespace PonyEngine::Application
{
	PONY_MODULE_ALLOCATE(PONY_MODULE_ORDER_BEGIN) const Module::ModuleInfo FirstInitializer{}; ///< First initializer. It's always nullptr. To get a real one, you have to add a size of an initializer.
	PONY_MODULE_ALLOCATE(PONY_MODULE_ORDER_END) const Module::ModuleInfo LastInitializer{}; ///< Last initializer. It's an end.

	void InitializeModules()
	{
		const std::uintptr_t begin = reinterpret_cast<std::uintptr_t>(&FirstInitializer) + sizeof(Module::ModuleInfo);
		const std::uintptr_t end = reinterpret_cast<std::uintptr_t>(&LastInitializer);
		std::uintptr_t current = begin;
		while (current < end)
		{
			if (const auto info = reinterpret_cast<const Module::ModuleInfo*>(current); info->initializer)
			{
				std::cout << info->name << "\n"; // TODO: Add correct log
				info->initializer();
				current += sizeof(Module::ModuleInfo);
			}
			else
			{
				current += alignof(Module::ModuleInfo);
			}
		}
	}
}
