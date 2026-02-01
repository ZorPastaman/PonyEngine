/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:DescriptorRangeMeta;

import std;

import :DescriptorRange;
import :ShaderType;

export namespace PonyEngine::RenderDevice
{
	struct DescriptorRangeMeta final
	{
		DescriptorRange range;
		std::size_t descriptorSetIndex = 0u;
	};
}
