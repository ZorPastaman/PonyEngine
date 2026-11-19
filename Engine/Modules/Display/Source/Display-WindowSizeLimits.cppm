/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Display:WindowSizeLimits;

import std;

import PonyEngine.Math;

export namespace PonyEngine::Display
{
	struct WindowSizeLimits final
	{
		Math::Vector2<std::uint32_t> min;
		Math::Vector2<std::uint32_t> max;
	};
}
