/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#pragma once

#ifdef PONY_DLL
 /// @brief Sets a dll export attribute if the build target has PONY_DLL defined; otherwise does nothing.
#define PONY_DLL_EXPORT __declspec(dllexport)
#else
 /// @brief Sets a dll export attribute if the build target has PONY_DLL defined; otherwise does nothing.
#define PONY_DLL_EXPORT
#endif

/// @brief Prevents a compiler from removing the symbol.
/// @param symbol Symbol to preserve.
#define PONY_PRESERVE(symbol) __pragma(comment(linker, "/include:" symbol))

/// @brief Section delimiter that is set between a section name and an order.
#define PONY_SECTION_DELIMITER $
/// @brief Declares a section.
/// @param name Section name.
#define PONY_SECTION(name) __pragma(section(name, read))
/// @brief Allocates a segment.
/// @param segment Segment name.
#define PONY_ALLOCATE(segment) __declspec(allocate(segment))
