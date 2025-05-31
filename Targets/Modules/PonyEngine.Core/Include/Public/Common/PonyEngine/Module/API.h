/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: cybercode.smith@pm.me                    *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

// Import PonyEngine.Module to use these macros.

#pragma once

#include "PonyEngine/Utility/Compiler.h"
#include "PonyEngine/Utility/Macro.h"

/// @brief Creates a module section name.
/// @param order Section order.
#define PONY_MODULE_SECTION_NAME(order) PONY_STRINGIFY_VALUE(PONY_CONCAT_VALUES(PonyModule$, order))
/// @brief Allocates a module segment.
/// @param order Segment order.
#define PONY_MODULE_ALLOCATE(order) PONY_ALLOCATE(PONY_MODULE_SECTION_NAME(order))
/// @brief Creates a module function name.
/// @param function Target function name.
#define PONY_MODULE_FUNCTION_NAME(function) PONY_CONCAT_VALUES(PonyInitializerFunc, function)
/// @brief Creates a module field name.
/// @param function Target function name.
#define PONY_MODULE_FIELD_NAME(function) PONY_CONCAT_VALUES(PonyInitializerField, function)

// Order list. The order of execution is Begin -> Earliest -> Earlier -> Early -> Default -> Late -> Later -> Latest -> End
// Don't use Begin and End. They are special marks.
#define PONY_MODULE_ORDER_BEGIN a
#define PONY_MODULE_ORDER_EARLIEST b
#define PONY_MODULE_ORDER_EARLIER e
#define PONY_MODULE_ORDER_EARLY i
#define PONY_MODULE_ORDER_DEFAULT m
#define PONY_MODULE_ORDER_LATE q
#define PONY_MODULE_ORDER_LATER u
#define PONY_MODULE_ORDER_LATEST y
#define PONY_MODULE_ORDER_END z

// Section declaration.
PONY_SECTION(PONY_MODULE_SECTION_NAME(PONY_MODULE_ORDER_BEGIN))
PONY_SECTION(PONY_MODULE_SECTION_NAME(PONY_MODULE_ORDER_EARLIEST))
PONY_SECTION(PONY_MODULE_SECTION_NAME(PONY_MODULE_ORDER_EARLIER))
PONY_SECTION(PONY_MODULE_SECTION_NAME(PONY_MODULE_ORDER_EARLY))
PONY_SECTION(PONY_MODULE_SECTION_NAME(PONY_MODULE_ORDER_DEFAULT))
PONY_SECTION(PONY_MODULE_SECTION_NAME(PONY_MODULE_ORDER_LATE))
PONY_SECTION(PONY_MODULE_SECTION_NAME(PONY_MODULE_ORDER_LATER))
PONY_SECTION(PONY_MODULE_SECTION_NAME(PONY_MODULE_ORDER_LATEST))
PONY_SECTION(PONY_MODULE_SECTION_NAME(PONY_MODULE_ORDER_END))

/// @brief Adds a module initialization function.
/// @note The function name must be unique across the whole application.
/// @param function Function to add. It must satisfy PonyEngine::Module::ModuleInitializer using. In a dll, it must have PONY_DLL_EXPORT as well.
/// @param order Execution order. Must be one of PONY_MODULE_ORDER except Begin and End.
#define PONY_MODULE_INITIALIZER(function, order) \
	extern "C" void PONY_MODULE_FUNCTION_NAME(function)() \
	{ \
		function(); \
	} \
	extern "C" PONY_MODULE_ALLOCATE(order) const PonyEngine::Module::ModuleInitializer PONY_MODULE_FIELD_NAME(function) = &PONY_MODULE_FUNCTION_NAME(function); \
	PONY_PRESERVE(PONY_MODULE_FUNCTION_NAME(function)); \
	PONY_PRESERVE(PONY_MODULE_FIELD_NAME(function));

/// @brief Adds a module initialization function and sets the earliest order.
/// @param function Function to add. It must satisfy PonyEngine::Module::ModuleInitializer using, have extern "C" mark and be in a global namespace.
#define PONY_MODULE_INITIALIZER_EARLIEST(function) PONY_MODULE_INITIALIZER(function, PONY_MODULE_ORDER_EARLIEST)
/// @brief Adds a module initialization function and sets the earlier order.
/// @param function Function to add. It must satisfy PonyEngine::Module::ModuleInitializer using, have extern "C" mark and be in a global namespace.
#define PONY_MODULE_INITIALIZER_EARLIER(function) PONY_MODULE_INITIALIZER(function, PONY_MODULE_ORDER_EARLIER)
/// @brief Adds a module initialization function and sets the early order.
/// @param function Function to add. It must satisfy PonyEngine::Module::ModuleInitializer using, have extern "C" mark and be in a global namespace.
#define PONY_MODULE_INITIALIZER_EARLY(function) PONY_MODULE_INITIALIZER(function, PONY_MODULE_ORDER_EARLY)
/// @brief Adds a module initialization function and sets the default order.
/// @param function Function to add. It must satisfy PonyEngine::Module::ModuleInitializer using, have extern "C" mark and be in a global namespace.
#define PONY_MODULE_INITIALIZER_DEFAULT(function) PONY_MODULE_INITIALIZER(function, PONY_MODULE_ORDER_DEFAULT)
/// @brief Adds a module initialization function and sets the late order.
/// @param function Function to add. It must satisfy PonyEngine::Module::ModuleInitializer using, have extern "C" mark and be in a global namespace.
#define PONY_MODULE_INITIALIZER_LATE(function) PONY_MODULE_INITIALIZER(function, PONY_MODULE_ORDER_LATE)
/// @brief Adds a module initialization function and sets the later order.
/// @param function Function to add. It must satisfy PonyEngine::Module::ModuleInitializer using, have extern "C" mark and be in a global namespace.
#define PONY_MODULE_INITIALIZER_LATER(function) PONY_MODULE_INITIALIZER(function, PONY_MODULE_ORDER_LATER)
/// @brief Adds a module initialization function and sets the latest order.
/// @param function Function to add. It must satisfy PonyEngine::Module::ModuleInitializer using, have extern "C" mark and be in a global namespace.
#define PONY_MODULE_INITIALIZER_LATEST(function) PONY_MODULE_INITIALIZER(function, PONY_MODULE_ORDER_LATEST)
