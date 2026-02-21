/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:SamplerBinding;

import std;

export namespace PonyEngine::RenderDevice
{
	struct SamplerBinding final
	{
		std::uint32_t layoutSetIndex = 0u;
		std::uint32_t containerIndex = 0u;
	};
}
