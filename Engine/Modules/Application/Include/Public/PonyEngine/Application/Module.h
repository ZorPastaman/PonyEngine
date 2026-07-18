/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

// Import PonyEngine.Application to use these macros.

#pragma once

#include "PonyEngine/Macro/Compiler.h"
#include "PonyEngine/Macro/Text.h"

/// @brief Creates an early module section name.
/// @param order Section order.
/// @note For internal use only.
#define PONY_EARLY_MODULE_SECTION_NAME(order) PONY_STRINGIFY_VALUE(PONY_CONCAT_VALUES(PonyModuleEarly$, order))
/// @brief Allocates an early module segment.
/// @param order Segment order.
/// @note For internal use only.
#define PONY_EARLY_MODULE_ALLOCATE(order) PONY_ALLOCATE(PONY_EARLY_MODULE_SECTION_NAME(order))
/// @brief Creates a normal module section name.
/// @param order Section order.
/// @note For internal use only.
#define PONY_NORMAL_MODULE_SECTION_NAME(order) PONY_STRINGIFY_VALUE(PONY_CONCAT_VALUES(PonyModuleNormal$, order))
/// @brief Allocates a normal module segment.
/// @param order Segment order.
/// @note For internal use only.
#define PONY_NORMAL_MODULE_ALLOCATE(order) PONY_ALLOCATE(PONY_NORMAL_MODULE_SECTION_NAME(order))
/// @brief Creates a late module section name.
/// @param order Section order.
/// @note For internal use only.
#define PONY_LATE_MODULE_SECTION_NAME(order) PONY_STRINGIFY_VALUE(PONY_CONCAT_VALUES(PonyModuleLate$, order))
/// @brief Allocates a late module segment.
/// @param order Segment order.
/// @note For internal use only.
#define PONY_LATE_MODULE_ALLOCATE(order) PONY_ALLOCATE(PONY_LATE_MODULE_SECTION_NAME(order))
/// @brief Creates a module interface name.
/// @param moduleName Target module name.
/// @note For internal use only.
#define PONY_MODULE_INTERFACE_NAME(moduleName) PONY_CONCAT_VALUES(PonyModule, moduleName)

/// @brief Used by the application to find a start point.
/// @note For internal use only.
#define PONY_MODULE_ORDER_BEGIN a
/// @brief Used by the application to find an end point.
/// @note For internal use only.
#define PONY_MODULE_ORDER_END z

/// @brief Begins an early section declaration.
/// @note For internal use only.
PONY_SECTION(PONY_EARLY_MODULE_SECTION_NAME(PONY_MODULE_ORDER_BEGIN))
/// @brief Ends an early section declaration.
/// @note For internal use only.
PONY_SECTION(PONY_EARLY_MODULE_SECTION_NAME(PONY_MODULE_ORDER_END))
/// @brief Begins a normal section declaration.
/// @note For internal use only.
PONY_SECTION(PONY_NORMAL_MODULE_SECTION_NAME(PONY_MODULE_ORDER_BEGIN))
/// @brief Ends a normal section declaration.
/// @note For internal use only.
PONY_SECTION(PONY_NORMAL_MODULE_SECTION_NAME(PONY_MODULE_ORDER_END))
/// @brief Begins a late section declaration.
/// @note For internal use only.
PONY_SECTION(PONY_LATE_MODULE_SECTION_NAME(PONY_MODULE_ORDER_BEGIN))
/// @brief Ends a late section declaration.
/// @note For internal use only.
PONY_SECTION(PONY_LATE_MODULE_SECTION_NAME(PONY_MODULE_ORDER_END))

/// @brief Adds the early module.
/// @param function Module getter function of type PonyEngine::Application::ModuleGetter. Must return a valid pointer to a module object. The returned object must be alive till the end of an application.
/// @param moduleName Module name. Must be unique across the whole application.
/// @param order Execution order. It may be any string of small letters but mustn't start with a or z.
#define PONY_EARLY_MODULE(function, moduleName, order) \
	PONY_SECTION(PONY_EARLY_MODULE_SECTION_NAME(order)) \
	extern "C" \
	{ \
		PONY_EARLY_MODULE_ALLOCATE(order) PonyEngine::Application::IModule* (*PONY_MODULE_INTERFACE_NAME(moduleName))() = function; \
		PONY_PRESERVE(PONY_MODULE_INTERFACE_NAME(moduleName)); \
	} \
/// @brief Adds the normal module.
/// @param function Module getter function of type PonyEngine::Application::ModuleGetter. Must return a valid pointer to a module object. The returned object must be alive till the end of an application.
/// @param moduleName Module name. Must be unique across the whole application.
/// @param order Execution order. It may be any string of small letters but mustn't start with a or z.
#define PONY_NORMAL_MODULE(function, moduleName, order) \
	PONY_SECTION(PONY_NORMAL_MODULE_SECTION_NAME(order)) \
	extern "C" \
	{ \
		PONY_NORMAL_MODULE_ALLOCATE(order) PonyEngine::Application::IModule* (*PONY_MODULE_INTERFACE_NAME(moduleName))() = function; \
		PONY_PRESERVE(PONY_MODULE_INTERFACE_NAME(moduleName)); \
	} \
/// @brief Adds the late module.
/// @param function Module getter function of type PonyEngine::Application::ModuleGetter. Must return a valid pointer to a module object. The returned object must be alive till the end of an application.
/// @param moduleName Module name. Must be unique across the whole application.
/// @param order Execution order. It may be any string of small letters but mustn't start with a or z.
#define PONY_LATE_MODULE(function, moduleName, order) \
	PONY_SECTION(PONY_LATE_MODULE_SECTION_NAME(order)) \
	extern "C" \
	{ \
		PONY_LATE_MODULE_ALLOCATE(order) PonyEngine::Application::IModule* (*PONY_MODULE_INTERFACE_NAME(moduleName))() = function; \
		PONY_PRESERVE(PONY_MODULE_INTERFACE_NAME(moduleName)); \
	} \

/// @brief Adds the normal module.
/// @param function Module getter function of type PonyEngine::Application::ModuleGetter. Must return a valid pointer to a module object. The returned object must be alive till the end of an application.
/// @param moduleName Module name. Must be unique across the whole application.
/// @param order Execution order. It may be any string of small letters but mustn't start with a or z.
#define PONY_LOG_MODULE(function, moduleName, order) PONY_EARLY_MODULE(function, moduleName, order)
/// @brief Adds the normal module.
/// @param function Module getter function of type PonyEngine::Application::ModuleGetter. Must return a valid pointer to a module object. The returned object must be alive till the end of an application.
/// @param moduleName Module name. Must be unique across the whole application.
/// @param order Execution order. It may be any string of small letters but mustn't start with a or z.
#define PONY_ENGINE_MODULE(function, moduleName, order) PONY_NORMAL_MODULE(function, moduleName, order)
/// @brief Adds the late module.
/// @param function Module getter function of type PonyEngine::Application::ModuleGetter. Must return a valid pointer to a module object. The returned object must be alive till the end of an application.
/// @param moduleName Module name. Must be unique across the whole application.
/// @param order Execution order. It may be any string of small letters but mustn't start with a or z.
#define PONY_PROJECT_MODULE(function, moduleName, order) PONY_LATE_MODULE(function, moduleName, order)
