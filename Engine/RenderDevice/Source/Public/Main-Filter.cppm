/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:Filter;

import std;

export namespace PonyEngine::RenderDevice
{
	enum class Filter : std::uint8_t
	{
		Nearest,
		Linear
	};
}
