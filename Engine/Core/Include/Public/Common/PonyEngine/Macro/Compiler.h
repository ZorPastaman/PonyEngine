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

// PONY_DLL_EXPORT sets a correct dll export attribute. If the build target isn't dll, it sets nothing.
#ifdef PONY_DLL
#ifdef _MSC_VER
#define PONY_DLL_EXPORT __declspec(dllexport)
#else
#error "Unsupported compiler!"
#endif
#else
#define PONY_DLL_EXPORT
#endif

// PONY_PRESERVE prevents a compiler from removing the symbol.
#ifdef _MSC_VER
#define PONY_PRESERVE(symbol) __pragma(comment(linker, "/include:" PONY_STRINGIFY(symbol)))
#else
#error "Unsupported compiler!"
#endif

#ifdef _MSC_VER
#define PONY_SECTION(name) __pragma(section(name, read))
#else
#error "Unsupported compiler!"
#endif

// PONY_ALLOCATE allocates a segment by its name.
#ifdef _MSC_VER
#define PONY_ALLOCATE(segment) __declspec(allocate(segment))
#else
#error "Unsupported compiler!"
#endif
