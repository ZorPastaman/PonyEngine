/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:DescriptorSet;

import std;

import :SamplerDescriptorRange;
import :ShaderDataDescriptorRange;
import :StaticSamplerParams;

export namespace PonyEngine::RenderDevice
{
	struct DescriptorSet final
	{
		std::variant<std::span<const ShaderDataDescriptorRange>, std::span<const SamplerDescriptorRange>> ranges;
		std::span<const StaticSamplerParams> staticSamplers;
		std::uint32_t setIndex = 0u;
	};
}
