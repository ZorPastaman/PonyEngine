/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

// Import std and PonyEngine.Application to use these macros.

#pragma once

#include "PonyCompiler.h"

#include "PonyEngine/Macro/Text.h"

/// @brief Creates an early module section name.
/// @param order Section order.
/// @note For internal use only.
#define PONY_EARLY_MODULE_SECTION_NAME(order) PONY_STRINGIFY_VALUE(PONY_CONCAT_VALUES(PONY_CONCAT_VALUES(PonyModuleEarly, PONY_SECTION_DELIMITER), order))
/// @brief Allocates an early module segment.
/// @param order Segment order.
/// @note For internal use only.
#define PONY_EARLY_MODULE_ALLOCATE(order) PONY_ALLOCATE(PONY_EARLY_MODULE_SECTION_NAME(order))
/// @brief Creates a normal module section name.
/// @param order Section order.
/// @note For internal use only.
#define PONY_NORMAL_MODULE_SECTION_NAME(order) PONY_STRINGIFY_VALUE(PONY_CONCAT_VALUES(PONY_CONCAT_VALUES(PonyModuleNormal, PONY_SECTION_DELIMITER), order))
/// @brief Allocates a normal module segment.
/// @param order Segment order.
/// @note For internal use only.
#define PONY_NORMAL_MODULE_ALLOCATE(order) PONY_ALLOCATE(PONY_NORMAL_MODULE_SECTION_NAME(order))
/// @brief Creates a late module section name.
/// @param order Section order.
/// @note For internal use only.
#define PONY_LATE_MODULE_SECTION_NAME(order) PONY_STRINGIFY_VALUE(PONY_CONCAT_VALUES(PONY_CONCAT_VALUES(PonyModuleLate, PONY_SECTION_DELIMITER), order))
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

/// @brief Adds the module
/// @param function Module getter function of type PonyEngine::Application::ModuleGetter. Must return a valid pointer to a module object. The returned object must be alive till the end of an application.
/// @param moduleName Module name. Must be unique across the whole application.
/// @param order Execution order. It may be any string of small letters but mustn't start with a or z.
/// @param sectionName Section name.
#define PONY_MODULE(function, moduleName, order, sectionName) \
	PONY_SECTION(sectionName) \
	extern "C" \
	{ \
		PONY_ALLOCATE(sectionName) std::shared_ptr<PonyEngine::Application::IModule> (*PONY_MODULE_INTERFACE_NAME(moduleName))() = function; \
		PONY_PRESERVE(PONY_STRINGIFY_VALUE(PONY_MODULE_INTERFACE_NAME(moduleName))); \
	} \

/// @brief Adds the early module.
/// @param function Module getter function of type PonyEngine::Application::ModuleGetter. Must return a valid pointer to a module object. The returned object must be alive till the end of an application.
/// @param moduleName Module name. Must be unique across the whole application.
/// @param order Execution order. It may be any string of small letters but mustn't start with a or z.
#define PONY_EARLY_MODULE(function, moduleName, order) PONY_MODULE(function, moduleName, order, PONY_EARLY_MODULE_SECTION_NAME(order))
/// @brief Adds the normal module.
/// @param function Module getter function of type PonyEngine::Application::ModuleGetter. Must return a valid pointer to a module object. The returned object must be alive till the end of an application.
/// @param moduleName Module name. Must be unique across the whole application.
/// @param order Execution order. It may be any string of small letters but mustn't start with a or z.
#define PONY_NORMAL_MODULE(function, moduleName, order) PONY_MODULE(function, moduleName, order, PONY_NORMAL_MODULE_SECTION_NAME(order))
/// @brief Adds the late module.
/// @param function Module getter function of type PonyEngine::Application::ModuleGetter. Must return a valid pointer to a module object. The returned object must be alive till the end of an application.
/// @param moduleName Module name. Must be unique across the whole application.
/// @param order Execution order. It may be any string of small letters but mustn't start with a or z.
#define PONY_LATE_MODULE(function, moduleName, order) PONY_MODULE(function, moduleName, order, PONY_LATE_MODULE_SECTION_NAME(order))

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
