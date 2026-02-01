/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:StaticSamplerMeta;

import std;

import :ShaderType;
import :StaticSamplerParams;

export namespace PonyEngine::RenderDevice
{
	struct StaticSamplerMeta final
	{
		StaticSamplerParams samplerParams;
		std::size_t descriptorSetIndex = 0u;
	};
}
