/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:FenceValue;

import std;

import :IFence;

export namespace PonyEngine::RenderDevice
{
	struct FenceValue final
	{
		const IFence* fence;
		std::uint64_t value;
	};
}
