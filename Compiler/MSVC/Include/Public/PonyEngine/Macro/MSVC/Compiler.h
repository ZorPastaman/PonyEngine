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

#define PONY_DLL_EXPORT_IMPL __declspec(dllexport)

#define PONY_PRESERVE_IMPL(symbol) __pragma(comment(linker, "/include:" PONY_STRINGIFY(symbol)))
#define PONY_SECTION_IMPL(name) __pragma(section(name, read))
#define PONY_ALLOCATE_IMPL(segment) __declspec(allocate(segment))
