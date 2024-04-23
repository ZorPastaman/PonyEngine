/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#pragma once

#if _MSC_VER && !__INTEL_COMPILER
#define PONY_DLL_EXPORT __declspec(dllexport)
#else
#error "Unsupported compiler!"
#endif
