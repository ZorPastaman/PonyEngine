/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:TextureSupportResponse;

import std;

import PonyEngine.Math;

import :SampleCount;

export namespace PonyEngine::RenderDevice
{
	struct TextureSupportResponse final
	{
		Math::Vector3<std::uint32_t> maxSize = Math::Vector3<std::uint32_t>::Zero();
		std::uint16_t maxArraySize = 0u;
		std::uint8_t maxMipCount = 0u;
		SampleCountMask sampleCounts = SampleCountMask::None;
		bool supported = false;
	};
}
