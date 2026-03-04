/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:DescriptorSetMeta;

import std;

import :SamplerDescriptorRange;
import :ShaderDataDescriptorRange;
import :StaticSamplerParams;

export namespace PonyEngine::RenderDevice
{
	/// @brief Descriptor set meta.
	struct DescriptorSetMeta final
	{
		std::span<const ShaderDataDescriptorRange> shaderDataRanges; ///< Shader data ranges.
		std::span<const SamplerDescriptorRange> samplerRanges; ///< Sampler ranges.
		std::span<const StaticSamplerParams> staticSamplers; ///< Static samplers.
		std::uint32_t setIndex = 0u; ///< Set index.
	};
}
