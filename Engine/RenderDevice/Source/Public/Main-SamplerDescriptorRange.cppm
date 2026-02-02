/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:SamplerDescriptorRange;

import std;

export namespace PonyEngine::RenderDevice
{
	struct SamplerDescriptorRange final
	{
		std::uint32_t baseShaderRegister = 0u;
		std::uint32_t count = 1u;
	};
}
