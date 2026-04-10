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
	/// @brief Sample parameters.
	struct SampleParams final
	{
		std::uint32_t sampleMask = std::numeric_limits<std::uint32_t>::max(); ///< Sample mask.
		SampleCount sampleCount = SampleCount::X1; ///< Sample count.
		bool alphaToCoverage = false; ///< Is alpha to coverage enable?
	};
}
