/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:CullMode;

import std;

export namespace PonyEngine::RenderDevice
{
	enum class CullMode : std::uint8_t
	{
		None,
		Front,
		Back
	};
}
