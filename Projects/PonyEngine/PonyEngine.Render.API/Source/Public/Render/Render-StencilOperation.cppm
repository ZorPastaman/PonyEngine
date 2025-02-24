/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render:StencilOperation;

import <cstdint>;

export namespace PonyEngine::Render
{
	enum class StencilOperation : std::uint8_t
	{
		Keep,
        Zero,
        Replace,
        Invert,
        Increment,
        Decrement,
        IncrementSaturated,
        DecrementSaturated
	};
}
