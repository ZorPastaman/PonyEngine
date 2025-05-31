/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: cybercode.smith@pm.me                    *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

#pragma once

/// @brief Stringifies the parameter.
/// @param x Parameter to stringify.
#define PONY_STRINGIFY(x) #x
/// @brief Stringifies the parameter value.
/// @param x Parameter to stringify.
#define PONY_STRINGIFY_VALUE(x) PONY_STRINGIFY(x)
/// @brief Concatenates the parameters.
/// @param a Left parameter.
/// @param b Right parameter.
#define PONY_CONCAT(a, b) a##b
/// @brief Concatenates the parameter values.
/// @param a Left parameter.
/// @param b Right parameter.
#define PONY_CONCAT_VALUES(a, b) PONY_CONCAT(a, b)
