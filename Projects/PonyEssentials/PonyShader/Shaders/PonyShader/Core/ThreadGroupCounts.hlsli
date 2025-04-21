/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

/// @brief Thread group counts. It corresponds to @p PonyShader::Core::ThreadGroupCounts on the C++ side.
struct Pony_ThreadGroupCounts
{
	uint3 counts; ///< Thread group counts. The order is x, y, z.
};
