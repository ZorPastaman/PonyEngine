/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#pragma once

#if _MSC_VER
/// @brief Dll export macro.
#define PONY_DLL_EXPORT __declspec(dllexport)
#else
#error "Unsupported compiler!"
#endif
