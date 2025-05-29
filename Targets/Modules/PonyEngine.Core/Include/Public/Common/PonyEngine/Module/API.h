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

#include "PonyEngine/Utility/Macro.h"

/// @brief Creates a module section name.
/// @param order Section order.
#define PONY_MODULE_SECTION_NAME(order) PONY_STRINGIFY_VALUE(PONY_CONCAT_VALUES(PonyModule$, order))

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

// PONY_MODULE_ALLOCATE allocates a linker section.
// PONY_MODULE_INCLUDE Forces a linker to include a function.
#ifdef _MSC_VER
#pragma section(PONY_MODULE_SECTION_NAME(PONY_MODULE_ORDER_BEGIN), read)
#pragma section(PONY_MODULE_SECTION_NAME(PONY_MODULE_ORDER_EARLIEST), read)
#pragma section(PONY_MODULE_SECTION_NAME(PONY_MODULE_ORDER_EARLIER), read)
#pragma section(PONY_MODULE_SECTION_NAME(PONY_MODULE_ORDER_EARLY), read)
#pragma section(PONY_MODULE_SECTION_NAME(PONY_MODULE_ORDER_DEFAULT), read)
#pragma section(PONY_MODULE_SECTION_NAME(PONY_MODULE_ORDER_LATE), read)
#pragma section(PONY_MODULE_SECTION_NAME(PONY_MODULE_ORDER_LATER), read)
#pragma section(PONY_MODULE_SECTION_NAME(PONY_MODULE_ORDER_LATEST), read)
#pragma section(PONY_MODULE_SECTION_NAME(PONY_MODULE_ORDER_END), read)
#define PONY_MODULE_ALLOCATE(order) __declspec(allocate(PONY_MODULE_SECTION_NAME(order)))
#define PONY_MODULE_INCLUDE(function) __pragma(comment(linker, PONY_STRINGIFY_VALUE(PONY_CONCAT_VALUES(/include:, function))))
#else
#error "Unsupported compiler!"
#endif

/// @brief Adds a module initialization function.
/// @param function Function to add. It must satisfy PonyEngine::Module::ModuleInitializer using, have extern "C" mark and be in a global namespace.
/// @param order Execution order. Must be one of PONY_MODULE_ORDER except Begin and End.
#define PONY_MODULE_INITIALIZER(function, order) \
	PONY_MODULE_ALLOCATE(order) const PonyEngine::Module::ModuleInitializer PONY_CONCAT_VALUES(PonyInitializer, function) = function; \
	PONY_MODULE_INCLUDE(function);

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
