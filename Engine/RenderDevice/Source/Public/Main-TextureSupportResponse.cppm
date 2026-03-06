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
	/// @brief Texture support response.
	struct TextureSupportResponse final
	{
		Math::Vector3<std::uint32_t> maxSize = Math::Vector3<std::uint32_t>::Zero(); ///< Texture max size.
		std::uint16_t maxArraySize = 0u; ///< Max array size.
		std::uint8_t maxMipCount = 0u; ///< Max mip count.
		SampleCountMask sampleCounts = SampleCountMask::None; ///< Supported sample counts.
		bool supported = false; ///< May the current backend create such a texture at all?
	};
}
