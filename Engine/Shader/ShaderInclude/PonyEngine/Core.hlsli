/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

/// @brief Makes a binding register.
/// @param set Set index.
/// @param index Binding index.
/// @param literal Register literal (b, t, u, s).
#define PONY_REGISTER(set, index, literal) register(literal##index, space##set)
/// @brief Makes a CBV binding register.
/// @param set Set index.
/// @param index Binding index.
#define PONY_CBV_REGISTER(set, index) PONY_REGISTER(set, index, b)
/// @brief Makes an SRV binding register.
/// @param set Set index.
/// @param index Binding index.
#define PONY_SRV_REGISTER(set, index) PONY_REGISTER(set, index, t)
/// @brief Makes a UAV binding register.
/// @param set Set index.
/// @param index Binding index.
#define PONY_UAV_REGISTER(set, index) PONY_REGISTER(set, index, u)
/// @brief Makes a sampler binding register.
/// @param set Set index.
/// @param index Binding index.
#define PONY_SAMPLER_REGISTER(set, index) PONY_REGISTER(set, index, s)
