/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#pragma once

#ifdef PONY_COMPILER_INCLUDE
#include PONY_COMPILER_INCLUDE
#else
#error "No compiler added!"
#endif

#ifndef PONY_DLL_EXPORT_IMPL
#error "PONY_DLL_EXPORT_IMPL macro not found!"
#endif

#ifndef PONY_PRESERVE_IMPL
#error "PONY_PRESERVE_IMPL macro not found!"
#endif
#ifndef PONY_SECTION_IMPL
#error "PONY_SECTION_IMPL macro not found!"
#endif
#ifndef PONY_ALLOCATE_IMPL
#error "PONY_ALLOCATE_IMPL macro not found!"
#endif

#ifdef PONY_DLL
/// @brief Sets a dll export attribute if the build target has PONY_DLL defined; otherwise does nothing.
#define PONY_DLL_EXPORT PONY_DLL_EXPORT_IMPL
#else
/// @brief Sets a dll export attribute if the build target has PONY_DLL defined; otherwise does nothing.
#define PONY_DLL_EXPORT
#endif

/// @brief Prevents a compiler from removing the symbol.
/// @param symbol Symbol to preserve.
#define PONY_PRESERVE(symbol) PONY_PRESERVE_IMPL(symbol)
/// @brief Declares a section.
/// @param name Section name.
#define PONY_SECTION(name) PONY_SECTION_IMPL(name)
/// @brief Allocates a segment.
/// @param segment Segment name.
#define PONY_ALLOCATE(segment) PONY_ALLOCATE_IMPL(segment)
