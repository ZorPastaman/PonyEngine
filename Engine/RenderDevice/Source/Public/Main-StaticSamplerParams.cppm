/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:StaticSamplerParams;

import std;

import :SamplerParams;

export namespace PonyEngine::RenderDevice
{
	struct StaticSamplerParams final
	{
		SamplerParams samplerParams;
		std::uint32_t shaderRegister = 0u;
	};
}
