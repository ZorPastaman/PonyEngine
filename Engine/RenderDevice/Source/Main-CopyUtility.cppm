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

export module PonyEngine.RenderDevice:CopyUtility;

import std;

import :BufferRange;
import :CopyableFootprint;

export namespace PonyEngine::RenderDevice
{
	/// @brief Copies data.
	/// @param source Source.
	/// @param destination Destination.
	/// @param size Copied data size in bytes.
	void Copy(const void* source, void* destination, std::uint64_t size);
	/// @brief Copies data.
	/// @param source Source.
	/// @param sourceOffset Source offset in bytes.
	/// @param destination Destination.
	/// @param destinationOffset Destination offset in bytes.
	/// @param size Copied data size in bytes.
	void Copy(const void* source, std::uint64_t sourceOffset, void* destination, std::uint64_t destinationOffset, std::uint64_t size);
	/// @brief Copies data.
	/// @param source Source.
	/// @param destination Destination.
	/// @param range Copy range.
	void Copy(const void* source, void* destination, const CopyBufferRange& range);
	/// @brief Copies data.
	/// @param source Source.
	/// @param destination Destination.
	/// @param ranges Copy ranges.
	void Copy(const void* source, void* destination, std::span<const CopyBufferRange> ranges);
	/// @brief Copies data from a byte array to a texture buffer.
	/// @param source Source byte array.
	/// @param destination Destination texture buffer.
	/// @param footprints Copyable footprints.
	/// @note The function assumes that the source contains all the data in a row.
	void CopyToTextureBuffer(const void* source, void* destination, std::span<const CopyableFootprint> footprints);
	/// @brief Copies data from a byte array to a texture buffer.
	/// @param source Source byte array.
	/// @param sourceOffset Source offset in bytes.
	/// @param destination Destination texture buffer.
	/// @param destinationOffset Destination offset.
	/// @param footprints Copyable footprints.
	/// @note The function assumes that the source contains all the data in a row.
	void CopyToTextureBuffer(const void* source, std::uint64_t sourceOffset, void* destination, std::uint64_t destinationOffset,
		std::span<const CopyableFootprint> footprints);
	/// @brief Copies data from a texture buffer to a byte array.
	/// @param source Source texture buffer.
	/// @param destination Destination byte array.
	/// @param footprints Copyable footprints.
	/// @note The function writes all the data to the destination in a row.
	void CopyFromTextureBuffer(const void* source, void* destination, std::span<const CopyableFootprint> footprints);
	/// @brief Copies data from a texture buffer to a byte array.
	/// @param source Source texture buffer.
	/// @param sourceOffset Source offset in bytes.
	/// @param destination Destination byte array.
	/// @param destinationOffset Destination offset in bytes.
	/// @param footprints Copyable footprints.
	/// @note The function writes all the data to the destination in a row.
	void CopyFromTextureBuffer(const void* source, std::uint64_t sourceOffset, void* destination, std::uint64_t destinationOffset,
		std::span<const CopyableFootprint> footprints);
}

namespace PonyEngine::RenderDevice
{
	void Copy(const void* const source, void* const destination, const std::uint64_t size)
	{
		Copy(source, 0ull, destination, 0ull, size);
	}

	void Copy(const void* const source, const std::uint64_t sourceOffset, void* const destination, const std::uint64_t destinationOffset, const std::uint64_t size)
	{
		assert(size <= std::numeric_limits<std::size_t>::max() && "The size is too great.");
		std::memcpy(static_cast<std::byte*>(destination) + destinationOffset, static_cast<const std::byte*>(source) + sourceOffset, static_cast<std::size_t>(size));
	}

	void Copy(const void* const source, void* const destination, const CopyBufferRange& range)
	{
		Copy(source, range.sourceOffset, destination, range.destinationOffset, range.size);
	}

	void Copy(const void* const source, void* const destination, const std::span<const CopyBufferRange> ranges)
	{
		for (const CopyBufferRange& range : ranges)
		{
			Copy(source, destination, range);
		}
	}

	void CopyToTextureBuffer(const void* const source, void* const destination, const std::span<const CopyableFootprint> footprints)
	{
		CopyToTextureBuffer(source, 0ull, destination, 0ull, footprints);
	}

	void CopyToTextureBuffer(const void* const source, const std::uint64_t sourceOffset, void* const destination, const std::uint64_t destinationOffset, 
		const std::span<const CopyableFootprint> footprints)
	{
		const std::byte* src = static_cast<const std::byte*>(source) + sourceOffset;
		std::byte* const offsetDestination = static_cast<std::byte*>(destination) + destinationOffset;

		for (const CopyableFootprint& footprint : footprints)
		{
			assert(footprint.rowSize <= std::numeric_limits<std::size_t>::max() && "The size is too great.");

			std::byte* dst = offsetDestination + footprint.offset;

			for (std::uint32_t slice = 0u; slice < footprint.depth; ++slice)
			{
				for (std::uint32_t row = 0u; row < footprint.rowCount; ++row, src += footprint.rowSize, dst += footprint.rowPitch)
				{
					std::memcpy(dst, src, static_cast<std::size_t>(footprint.rowSize));
				}
			}
		}
	}

	void CopyFromTextureBuffer(const void* const source, void* const destination, const std::span<const CopyableFootprint> footprints)
	{
		CopyFromTextureBuffer(source, 0ull, destination, 0ull, footprints);
	}

	void CopyFromTextureBuffer(const void* const source, const std::uint64_t sourceOffset, void* const destination, const std::uint64_t destinationOffset, 
		const std::span<const CopyableFootprint> footprints)
	{
		const std::byte* const offsetSource = static_cast<const std::byte*>(source) + sourceOffset;
		std::byte* dst = static_cast<std::byte*>(destination) + destinationOffset;

		for (const CopyableFootprint& footprint : footprints)
		{
			assert(footprint.rowSize <= std::numeric_limits<std::size_t>::max() && "The size is too great.");

			const std::byte* src = offsetSource + footprint.offset;

			for (std::uint32_t slice = 0u; slice < footprint.depth; ++slice)
			{
				for (std::uint32_t row = 0u; row < footprint.rowCount; ++row, src += footprint.rowPitch, dst += footprint.rowSize)
				{
					std::memcpy(dst, src, static_cast<std::size_t>(footprint.rowSize));
				}
			}
		}
	}
}
