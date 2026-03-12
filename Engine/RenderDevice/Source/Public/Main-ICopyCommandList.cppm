/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Object/Body.h"

export module PonyEngine.RenderDevice:ICopyCommandList;

import std;

import :BufferBarrier;
import :CopyableFootprint;
import :IBuffer;
import :ICommandList;
import :ITexture;
import :SubTextureRange;
import :TextureBarrier;

export namespace PonyEngine::RenderDevice
{
	/// @brief Copy command list.
	class ICopyCommandList : public ICommandList
	{
		PONY_INTERFACE_BODY(ICopyCommandList)

		/// @brief Sets the barriers.
		/// @param bufferBarriers Buffer barriers.
		void Barrier(std::span<const BufferBarrier> bufferBarriers);
		/// @brief Sets the barriers.
		/// @param textureBarriers Texture barriers.
		void Barrier(std::span<const TextureBarrier> textureBarriers);
		/// @brief Sets the barriers.
		/// @param bufferBarriers Buffer barriers.
		/// @param textureBarriers Texture barriers.
		virtual void Barrier(std::span<const BufferBarrier> bufferBarriers, std::span<const TextureBarrier> textureBarriers) = 0;

		/// @brief Copies from the buffer to the other buffer.
		/// @param source Source buffer.
		/// @param destination Destination buffer.
		/// @note The buffers must have the same size.
		virtual void Copy(const IBuffer& source, IBuffer& destination) = 0;
		/// @brief Copies from the buffer region to the other buffer.
		/// @param source Source buffer.
		/// @param destination Destination buffer.
		/// @param ranges Copy ranges.
		virtual void Copy(const IBuffer& source, IBuffer& destination, std::span<const CopyBufferRange> ranges) = 0;
		/// @brief Copies from the texture to the other texture.
		/// @param source Source texture.
		/// @param destination Destination texture.
		/// @note The textures must have the same layout.
		virtual void Copy(const ITexture& source, ITexture& destination) = 0;
		/// @brief Copies from the texture to the other texture.
		/// @param source Source texture.
		/// @param destination Destination texture.
		/// @param range Sub-texture range.
		/// @note The texture must have compatible layouts.
		virtual void Copy(const ITexture& source, ITexture& destination, const CopySubTextureRange& range) = 0;
		/// @brief Copies from the texture to the other texture.
		/// @param source Source texture.
		/// @param destination Destination texture.
		/// @param range Sub-texture range with a box description.
		/// @note The texture must have compatible layouts.
		virtual void Copy(const ITexture& source, ITexture& destination, const BoxCopySubTextureRange& range) = 0;
		/// @brief Copies from the texture buffer to the texture.
		/// @param source Source texture buffer.
		/// @param destination Destination texture.
		/// @param footprints Copyable footprints. Must be valid for the both @p source and @p destination.
		virtual void Copy(const IBuffer& source, ITexture& destination, std::span<const CopyableFootprint> footprints) = 0;
		/// @brief Copies from the texture buffer to the texture.
		/// @param source Source texture buffer.
		/// @param destination Destination texture.
		/// @param footprints Copyable footprints. Must be valid for the both @p source and @p destination.
		/// @param range Sub-texture range.
		virtual void Copy(const IBuffer& source, ITexture& destination, std::span<const CopyableFootprint> footprints, const FootprintedCopySubTextureRange& range) = 0;
		/// @brief Copies from the texture buffer to the texture.
		/// @param source Source texture buffer.
		/// @param destination Destination texture.
		/// @param footprints Copyable footprints. Must be valid for the both @p source and @p destination.
		/// @param range Sub-texture range with a box description.
		virtual void Copy(const IBuffer& source, ITexture& destination, std::span<const CopyableFootprint> footprints, const FootprintedBoxCopySubTextureRange& range) = 0;
		/// @brief Copies from the texture to the texture buffer.
		/// @param source Source texture.
		/// @param destination Destination texture buffer.
		/// @param footprints Copyable footprints. Must be valid for the both @p source and @p destination.
		virtual void Copy(const ITexture& source, IBuffer& destination, std::span<const CopyableFootprint> footprints) = 0;
		/// @brief Copies from the texture to the texture buffer.
		/// @param source Source texture.
		/// @param destination Destination texture buffer.
		/// @param footprints Copyable footprints. Must be valid for the both @p source and @p destination.
		/// @param range Sub-texture range.
		virtual void Copy(const ITexture& source, IBuffer& destination, std::span<const CopyableFootprint> footprints, const FootprintedCopySubTextureRange& range) = 0;
		/// @brief Copies from the texture to the texture buffer.
		/// @param source Source texture.
		/// @param destination Destination texture buffer.
		/// @param footprints Copyable footprints. Must be valid for the both @p source and @p destination.
		/// @param range Sub-texture range with a box description.
		virtual void Copy(const ITexture& source, IBuffer& destination, std::span<const CopyableFootprint> footprints, const FootprintedBoxCopySubTextureRange& range) = 0;
	};
}

namespace PonyEngine::RenderDevice
{
	void ICopyCommandList::Barrier(const std::span<const BufferBarrier> bufferBarriers)
	{
		Barrier(bufferBarriers, std::span<const TextureBarrier>());
	}

	void ICopyCommandList::Barrier(const std::span<const TextureBarrier> textureBarriers)
	{
		Barrier(std::span<const BufferBarrier>(), textureBarriers);
	}
}
