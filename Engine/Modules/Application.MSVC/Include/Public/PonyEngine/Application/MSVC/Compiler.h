/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#pragma once

#include "PonyEngine/Macro/Text.h"

/// @brief Begin order of a section.
#define PONY_MSVC_SECTION_BEGIN_ORDER a
/// @brief End order of a section.
#define PONY_MSVC_SECTION_END_ORDER z
/// @brief Section delimiter.
#define PONY_MSVC_SECTION_DELIMITER $
/// @brief Makes a full section name.
/// @param sectionName Section name.
/// @param order Section order.
#define PONY_MSVC_MODULE_SECTION_NAME(sectionName, order) PONY_STRINGIFY_VALUE(PONY_CONCAT_VALUES(PONY_CONCAT_VALUES(sectionName, PONY_MSVC_SECTION_DELIMITER), order))

/// @brief Adds the module.
/// @param function Module getter function of type PonyEngine::Application::ModuleGetter. 
///                 Must return a valid pointer to a module object. The returned object must be alive till the end of an application.
/// @param moduleName Module name. Must be unique across the whole application.
/// @param order Execution order. It may be any string of small letters but mustn't start with a or z.
/// @param sectionName Section name.
#define PONY_MODULE(function, moduleName, order, sectionName) \
	__pragma(section(PONY_MSVC_MODULE_SECTION_NAME(sectionName, order), read)) \
	extern "C" \
	{ \
		__declspec(allocate(PONY_MSVC_MODULE_SECTION_NAME(sectionName, order))) \
		std::shared_ptr<PonyEngine::Application::IModule> (*moduleName)() = function; \
		__pragma(comment(linker, "/include:" PONY_STRINGIFY(moduleName))) \
	} \

/// @brief Makes a variable that points to a section begin.
/// @param sectionName Section name.
/// @param variableName Variable name.
#define PONY_MODULE_BEGIN(sectionName, variableName) \
	__pragma(section(PONY_MSVC_MODULE_SECTION_NAME(sectionName, PONY_MSVC_SECTION_BEGIN_ORDER), read)) \
	__declspec(allocate(PONY_MSVC_MODULE_SECTION_NAME(sectionName, PONY_MSVC_SECTION_BEGIN_ORDER))) \
	inline static std::shared_ptr<PonyEngine::Application::IModule>(* const variableName)() = nullptr; \

/// @brief Makes a variable that points to a section end.
/// @param sectionName Section name.
/// @param variableName Variable name.
#define PONY_MODULE_END(sectionName, variableName) \
	__pragma(section(PONY_MSVC_MODULE_SECTION_NAME(sectionName, PONY_MSVC_SECTION_END_ORDER), read)) \
	__declspec(allocate(PONY_MSVC_MODULE_SECTION_NAME(sectionName, PONY_MSVC_SECTION_END_ORDER))) \
	inline static std::shared_ptr<PonyEngine::Application::IModule>(* const variableName)() = nullptr; \
