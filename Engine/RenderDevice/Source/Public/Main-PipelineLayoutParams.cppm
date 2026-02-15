/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:PipelineLayoutParams;

import std;

import :DescriptorSet;

export namespace PonyEngine::RenderDevice
{
	struct PipelineLayoutParams final
	{
		std::span<const DescriptorSet> descriptorSets;
	};
}
