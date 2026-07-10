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
	/// @brief Descriptor set. Every descriptor is a separate space in hlsl.
	struct DescriptorSet final
	{
		std::variant<std::span<const ShaderDataDescriptorRange>, std::span<const SamplerDescriptorRange>> ranges; ///< Ranges.
		std::span<const StaticSamplerParams> staticSamplers; ///< Static samplers.
		std::uint32_t setIndex = 0u; ///< Set index. Space index in hlsl. Must be unique for a pipeline state.
	};
}
