/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

// Import PonyEngine.Core to use these macros.

#pragma once

#include "PonyEngine/Utility/Compiler.h"
#include "PonyEngine/Utility/Macro.h"

/// @brief Creates a module section name.
/// @param order Section order.
#define PONY_MODULE_SECTION_NAME(order) PONY_STRINGIFY_VALUE(PONY_CONCAT_VALUES(PonyModule$, order))
/// @brief Allocates a module segment.
/// @param order Segment order.
#define PONY_MODULE_ALLOCATE(order) PONY_ALLOCATE(PONY_MODULE_SECTION_NAME(order))
/// @brief Creates a module pointer name.
/// @param moduleName Target module name.
#define PONY_MODULE_POINTER_NAME(moduleName) PONY_CONCAT_VALUES(PonyPointer, moduleName)
/// @brief Creates a module interface name.
/// @param moduleName Target module name.
#define PONY_MODULE_INTERFACE_NAME(moduleName) PONY_CONCAT_VALUES(PonyInterface, moduleName)

/// @brief Used by the application to find a start point. Don't use in modules.
#define PONY_MODULE_ORDER_BEGIN a
/// @brief Used by the application to find an end point. Don't use in modules.
#define PONY_MODULE_ORDER_END z

/// @brief Begin section declaration.
PONY_SECTION(PONY_MODULE_SECTION_NAME(PONY_MODULE_ORDER_BEGIN))
/// @brief End section declaration.
PONY_SECTION(PONY_MODULE_SECTION_NAME(PONY_MODULE_ORDER_END))

/// @brief Adds the module.
/// @param function Module getter function of type PonyEngine::Application::ModuleGetter. Must return a valid pointer to a module object. The returned object's lifetime must match the module's lifetime.
/// @param moduleName Module name. Must be unique across the whole application.
/// @param order Execution order. It may be any string of letters but mustn't start with a or z.
#define PONY_MODULE(function, moduleName, order) \
	PONY_SECTION(PONY_MODULE_SECTION_NAME(order)) \
	extern "C" \
	{ \
		PONY_DLL_EXPORT PonyEngine::Application::IModule* PONY_MODULE_POINTER_NAME(moduleName) = function(); \
		PONY_MODULE_ALLOCATE(order) PonyEngine::Application::IModule** PONY_MODULE_INTERFACE_NAME(moduleName) = &PONY_MODULE_POINTER_NAME(moduleName); \
		PONY_PRESERVE(PONY_MODULE_POINTER_NAME(moduleName)); \
		PONY_PRESERVE(PONY_MODULE_INTERFACE_NAME(moduleName)); \
	}
