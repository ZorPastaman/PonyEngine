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
	PONY_MODULE_ALLOCATE(PONY_MODULE_ORDER_BEGIN) const Module::ModuleInitializer FirstInitializer = nullptr; ///< First initializer. It's always nullptr. To get a real one, you have to add a size of an initializer.
	PONY_MODULE_ALLOCATE(PONY_MODULE_ORDER_END) const Module::ModuleInitializer LastInitializer = nullptr; ///< Last initializer. It's an end.

	void InitializeModules()
	{
		const std::uintptr_t begin = reinterpret_cast<std::uintptr_t>(&FirstInitializer) + sizeof(Module::ModuleInitializer);
		const std::uintptr_t end = reinterpret_cast<std::uintptr_t>(&LastInitializer);
		for (std::uintptr_t current = begin; current < end; current += sizeof(Module::ModuleInitializer))
		{
			if (const Module::ModuleInitializer initializer = *reinterpret_cast<const Module::ModuleInitializer*>(current))
			{
				initializer();
			}
		}
	}
}
