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

#include "PonyEngine/Macro/Compiler.h"

#ifdef PONY_ENGINE_APPLICATION_COMPILER_INCLUDE
#include PONY_ENGINE_APPLICATION_COMPILER_INCLUDE
#else
#error "No compiler added!"
#endif

#ifdef PONY_MODULE_DLL
/// @brief Marks the function for an export as a module function.
#define PONY_MODULE_FUNC PONY_DLL_EXPORT
#else
/// @brief Marks the function for an export as a module function.
#define PONY_MODULE_FUNC
#endif

/// @brief Early module section name.
#define PONY_MODULE_EARLY_SECTION PonyModuleEarly
/// @brief Normal module section name.
#define PONY_MODULE_NORMAL_SECTION PonyModuleNormal
/// @brief Late module section name.
#define PONY_MODULE_LATE_SECTION PonyModuleLate

/// @brief Adds the early module.
/// @param function Module getter function of type PonyEngine::Application::ModuleGetter. Must return a valid pointer to a module object. The returned object must be alive till the end of an application.
/// @param moduleName Module name. Must be unique across the whole application.
/// @param order Execution order. It may be any string of small letters but mustn't start with a or z.
#define PONY_EARLY_MODULE(function, moduleName, order) PONY_MODULE(function, moduleName, order, PONY_MODULE_EARLY_SECTION)
/// @brief Adds the normal module.
/// @param function Module getter function of type PonyEngine::Application::ModuleGetter. Must return a valid pointer to a module object. The returned object must be alive till the end of an application.
/// @param moduleName Module name. Must be unique across the whole application.
/// @param order Execution order. It may be any string of small letters but mustn't start with a or z.
#define PONY_NORMAL_MODULE(function, moduleName, order) PONY_MODULE(function, moduleName, order, PONY_MODULE_NORMAL_SECTION)
/// @brief Adds the late module.
/// @param function Module getter function of type PonyEngine::Application::ModuleGetter. Must return a valid pointer to a module object. The returned object must be alive till the end of an application.
/// @param moduleName Module name. Must be unique across the whole application.
/// @param order Execution order. It may be any string of small letters but mustn't start with a or z.
#define PONY_LATE_MODULE(function, moduleName, order) PONY_MODULE(function, moduleName, order, PONY_MODULE_LATE_SECTION)

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
