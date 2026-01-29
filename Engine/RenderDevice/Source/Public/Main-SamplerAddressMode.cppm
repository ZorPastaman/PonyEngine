/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:SamplerAddressMode;

import std;

export namespace PonyEngine::RenderDevice
{
	enum class SamplerAddressMode : std::uint8_t
	{
		Wrap,
		Mirror,
		Clamp
	};
}
