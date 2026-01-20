/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include <cassert>

export module PonyEngine.RenderDevice:Utility;

import std;

import :CopyableFootprint;

export namespace PonyEngine::RenderDevice
{
	void Copy(const void* source, std::uint64_t sourceOffset, void* destination, std::uint64_t destinationOffset, std::uint64_t size);
	void Copy(const void* source, std::uint64_t sourceOffset, void* destination, std::uint64_t destinationOffset,
		std::span<const CopyableFootprint> footprints);
}

namespace PonyEngine::RenderDevice
{
	void Copy(const void* const source, const std::uint64_t sourceOffset, void* const destination, const std::uint64_t destinationOffset, const std::uint64_t size)
	{
		assert(size <= std::numeric_limits<std::size_t>::max() && "The size is too great.");
		std::memcpy(static_cast<std::byte*>(destination) + destinationOffset, static_cast<const std::byte*>(source) + sourceOffset, static_cast<std::size_t>(size));
	}

	void Copy(const void* const source, const std::uint64_t sourceOffset, void* const destination, const std::uint64_t destinationOffset, 
		const std::span<const CopyableFootprint> footprints)
	{
		for (const CopyableFootprint& footprint : footprints)
		{
			assert(footprint.rowSize <= std::numeric_limits<std::size_t>::max() && "The size is too great.");
		}

		const std::byte* src = static_cast<const std::byte*>(source) + sourceOffset;
		std::byte* const offsetDestination = static_cast<std::byte*>(destination) + destinationOffset;

		for (const CopyableFootprint& footprint : footprints)
		{
			std::byte* dst = offsetDestination + footprint.offset;

			for (std::uint32_t slice = 0u; slice < footprint.sliceCount; ++slice)
			{
				for (std::uint32_t row = 0u; row < footprint.rowCount; ++row, src += footprint.rowSize, dst += footprint.rowPitch)
				{
					std::memcpy(dst, src, static_cast<std::size_t>(footprint.rowSize));
				}
			}
		}
	}
}
