/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:ComponentSwizzle;

import std;

export namespace PonyEngine::RenderDevice
{
	enum class ComponentSwizzle : std::uint8_t
	{
		Red,
		Green,
		Blue,
		Alpha,
		Zero,
		One
	};
}
