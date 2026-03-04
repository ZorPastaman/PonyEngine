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
	struct QueueSync final
	{
		std::span<const std::pair<const IFence*, std::uint64_t>> before;
		std::span<const std::pair<IFence*, std::uint64_t>> after;
	};
}
