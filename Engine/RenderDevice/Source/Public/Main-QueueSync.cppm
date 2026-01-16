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

import :FenceValue;

export namespace PonyEngine::RenderDevice
{
	struct QueueSync final
	{
		std::span<const FenceValue> before;
		std::span<const FenceValue> after;
	};
}
