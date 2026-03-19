/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:FenceSupport;

import std;

export namespace PonyEngine::RenderDevice
{
	/// @brief Fence support.
	struct FenceSupport final
	{
		std::uint32_t simultaneousWaitedFences; ///< How many fences may one waiter wait for in one execution?
	};
}
