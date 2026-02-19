/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:ResolveMode;

import std;

export namespace PonyEngine::RenderDevice
{
	enum class ResolveMode : std::uint8_t
	{
		Average,
		Minimum,
		Maximum
	};
}
