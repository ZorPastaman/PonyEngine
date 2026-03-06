/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:QueueSync;

import std;

import :IFence;

export namespace PonyEngine::RenderDevice
{
	/// @brief Command queue sync.
	struct QueueSync final
	{
		std::span<const std::pair<const IFence*, std::uint64_t>> before; ///< What fence values a command queue should wait for till it starts an execution. All the fences must be valid.
		std::span<const std::pair<IFence*, std::uint64_t>> after; ///< What fence values a command queue should signal after it finishes an execution. All the fences must be valid.
	};
}
