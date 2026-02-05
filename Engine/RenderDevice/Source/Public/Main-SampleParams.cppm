/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:SampleParams;

import std;

import :SampleCount;

export namespace PonyEngine::RenderDevice
{
	struct SampleParams final
	{
		std::uint32_t sampleMask = std::numeric_limits<std::uint32_t>::max();
		SampleCount sampleCount = SampleCount::X1;
		bool alphaToCoverage = false;
	};
}
