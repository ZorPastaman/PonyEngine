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
/// @brief Creates a module field name.
/// @param moduleName Target module name.
#define PONY_MODULE_FIELD_NAME(moduleName) PONY_CONCAT_VALUES(PonyField, moduleName)
/// @brief Creates a module pointer name.
/// @param moduleName Target module name.
#define PONY_MODULE_POINTER_NAME(moduleName) PONY_CONCAT_VALUES(PonyPointer, moduleName)

/// @brief Used by the application to find a start point. Don't use in modules.
#define PONY_MODULE_ORDER_BEGIN a
/// @brief Order for log modules.
#define PONY_MODULE_ORDER_LOG d
/// @brief Used by the application to find an end point of log modules. Don't use in modules.
#define PONY_MODULE_ORDER_LOG_CHECKPOINT e
/// @brief Order for engine modules.
#define PONY_MODULE_ORDER_ENGINE m
/// @brief Used by the application to find an end point. Don't use in modules.
#define PONY_MODULE_ORDER_END z

// Section declaration.
PONY_SECTION(PONY_MODULE_SECTION_NAME(PONY_MODULE_ORDER_BEGIN))
PONY_SECTION(PONY_MODULE_SECTION_NAME(PONY_MODULE_ORDER_LOG))
PONY_SECTION(PONY_MODULE_SECTION_NAME(PONY_MODULE_ORDER_LOG_CHECKPOINT))
PONY_SECTION(PONY_MODULE_SECTION_NAME(PONY_MODULE_ORDER_ENGINE))
PONY_SECTION(PONY_MODULE_SECTION_NAME(PONY_MODULE_ORDER_END))

/// @brief Adds the module.
/// @param module Module. Must be a default constructible class inheriting PonyEngine::Core::IModule.
/// @param moduleName Module name. Must be unique across the whole application.
/// @param order Execution order. Must be one of PONY_MODULE_ORDER except special ones.
#define PONY_MODULE(module, moduleName, order) \
	extern "C" \
	{ \
		PONY_DLL_EXPORT module PONY_MODULE_FIELD_NAME(moduleName); \
		PONY_MODULE_ALLOCATE(order) PonyEngine::Core::IModule* const PONY_MODULE_POINTER_NAME(moduleName) = &PONY_MODULE_FIELD_NAME(moduleName); \
		PONY_PRESERVE(PONY_MODULE_FIELD_NAME(moduleName)); \
		PONY_PRESERVE(PONY_MODULE_POINTER_NAME(moduleName)); \
	}

/// @brief Adds the log module.
/// @param module Module. Must be a default constructible class inheriting PonyEngine::Core::IModule.
/// @param moduleName Module name. Must be unique across the whole application.
#define PONY_MODULE_LOG(module, moduleName) PONY_MODULE(module, moduleName, PONY_MODULE_ORDER_LOG)
/// @brief Adds the engine module.
/// @param module Module. Must be a default constructible class inheriting PonyEngine::Core::IModule.
/// @param moduleName Module name. Must be unique across the whole application.
#define PONY_MODULE_ENGINE(module, moduleName) PONY_MODULE(module, moduleName, PONY_MODULE_ORDER_ENGINE)
