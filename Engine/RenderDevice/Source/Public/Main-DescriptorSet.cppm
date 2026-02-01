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

import :DescriptorRange;
import :StaticSamplerParams;

export namespace PonyEngine::RenderDevice
{
	struct DescriptorSet final
	{
		std::span<const DescriptorRange> ranges;
		std::span<const StaticSamplerParams> staticSamplers;
	};
}
