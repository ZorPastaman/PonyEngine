/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: cybercode.smith@pm.me                    *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#pragma once

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
