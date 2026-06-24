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
	/// @note All the resources bound to the command list must be kept alive till the finish of the command list execution.
	class ICopyCommandList : public ICommandList
	{
		PONY_INTERFACE_BODY(ICopyCommandList)

		/// @brief Sets the barrier.
		/// @param bufferBarrier Buffer barrier.
		void Barrier(const BufferBarrier& bufferBarrier);
		/// @brief Sets the barriers.
		/// @param bufferBarriers Buffer barriers.
		void Barrier(std::span<const BufferBarrier> bufferBarriers);
		/// @brief Sets the barrier.
		/// @param textureBarrier Texture barrier.
		void Barrier(const TextureBarrier& textureBarrier);
		/// @brief Sets the barriers.
		/// @param textureBarriers Texture barriers.
		void Barrier(std::span<const TextureBarrier> textureBarriers);
		/// @brief Sets the barriers.
		/// @param bufferBarriers Buffer barriers.
		/// @param textureBarrier Texture barrier.
		void Barrier(std::span<const BufferBarrier> bufferBarriers, const TextureBarrier& textureBarrier);
		/// @brief Sets the barriers.
		/// @param bufferBarrier Buffer barrier.
		/// @param textureBarriers Texture barriers.
		void Barrier(const BufferBarrier& bufferBarrier, std::span<const TextureBarrier> textureBarriers);
		/// @brief Sets the barriers.
		/// @param bufferBarriers Buffer barriers.
		/// @param textureBarriers Texture barriers.
		virtual void Barrier(std::span<const BufferBarrier> bufferBarriers, std::span<const TextureBarrier> textureBarriers) = 0;

		/// @brief Copies from the buffer to the other buffer.
		/// @param source Source buffer.
		/// @param destination Destination buffer.
		/// @note The buffers must have the same size.
		virtual void Copy(const IBuffer& source, IBuffer& destination) = 0;
		/// @brief Copies from the buffer to the other buffer.
		/// @param source Source buffer.
		/// @param destination Destination buffer.
		/// @param range Copy range.
		void Copy(const IBuffer& source, IBuffer& destination, const CopyBufferRange& range);
		/// @brief Copies from the buffer to the other buffer.
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
		/// @param subTexture Sub-texture to copy.
		/// @note The texture must have compatible layouts.
		void Copy(const ITexture& source, ITexture& destination, const CopySubTextureIndex& subTexture);
		/// @brief Copies from the texture to the other texture.
		/// @param source Source texture.
		/// @param destination Destination texture.
		/// @param subTextures Sub-textures to copy.
		/// @note The texture must have compatible layouts.
		virtual void Copy(const ITexture& source, ITexture& destination, std::span<const CopySubTextureIndex> subTextures) = 0;
		/// @brief Copies from the texture to the other texture.
		/// @param source Source texture.
		/// @param destination Destination texture.
		/// @param subTexture Sub-texture to copy.
		/// @param box Copy box.
		/// @note The texture must have compatible layouts.
		void Copy(const ITexture& source, ITexture& destination, const CopySubTextureIndex& subTexture, const CopySubTextureBox& box);
		/// @brief Copies from the texture to the other texture.
		/// @param source Source texture.
		/// @param destination Destination texture.
		/// @param subTextures Sub-textures to copy.
		/// @param boxes Copy boxes. Its count must be equal @p subTextures count.
		/// @note The texture must have compatible layouts.
		virtual void Copy(const ITexture& source, ITexture& destination, std::span<const CopySubTextureIndex> subTextures, std::span<const CopySubTextureBox> boxes) = 0;
		/// @brief Copies from the texture buffer to the texture.
		/// @param source Source texture buffer.
		/// @param destination Destination texture.
		/// @param footprint Copyable footprint. Must be valid for the both @p source and @p destination.
		void Copy(const IBuffer& source, ITexture& destination, const CopyableFootprint& footprint);
		/// @brief Copies from the texture buffer to the texture.
		/// @param source Source texture buffer.
		/// @param destination Destination texture.
		/// @param footprints Copyable footprints. Must be valid for the both @p source and @p destination.
		virtual void Copy(const IBuffer& source, ITexture& destination, std::span<const CopyableFootprint> footprints) = 0;
		/// @brief Copies from the texture buffer to the texture.
		/// @param source Source texture buffer.
		/// @param destination Destination texture.
		/// @param footprint Copyable footprint. Must be valid for the both @p source and @p destination.
		/// @param box Copy box. Its count must be equal @p subTextures count.
		void Copy(const IBuffer& source, ITexture& destination, const CopyableFootprint& footprint, const CopySubTextureBox& box);
		/// @brief Copies from the texture buffer to the texture.
		/// @param source Source texture buffer.
		/// @param destination Destination texture.
		/// @param footprints Copyable footprints. Must be valid for the both @p source and @p destination.
		/// @param boxes Copy boxes. Its count must be equal @p subTextures count.
		virtual void Copy(const IBuffer& source, ITexture& destination, std::span<const CopyableFootprint> footprints, std::span<const CopySubTextureBox> boxes) = 0;
		/// @brief Copies from the texture to the texture buffer.
		/// @param source Source texture.
		/// @param destination Destination texture buffer.
		/// @param footprint Copyable footprint. Must be valid for the both @p source and @p destination.
		void Copy(const ITexture& source, IBuffer& destination, const CopyableFootprint& footprint);
		/// @brief Copies from the texture to the texture buffer.
		/// @param source Source texture.
		/// @param destination Destination texture buffer.
		/// @param footprints Copyable footprints. Must be valid for the both @p source and @p destination.
		virtual void Copy(const ITexture& source, IBuffer& destination, std::span<const CopyableFootprint> footprints) = 0;
		/// @brief Copies from the texture to the texture buffer.
		/// @param source Source texture.
		/// @param destination Destination texture buffer.
		/// @param footprint Copyable footprint. Must be valid for the both @p source and @p destination.
		/// @param box Copy box. Its count must be equal @p subTextures count.
		void Copy(const ITexture& source, IBuffer& destination, const CopyableFootprint& footprint, const CopySubTextureBox& box);
		/// @brief Copies from the texture to the texture buffer.
		/// @param source Source texture.
		/// @param destination Destination texture buffer.
		/// @param footprints Copyable footprints. Must be valid for the both @p source and @p destination.
		/// @param boxes Copy boxes. Its count must be equal @p subTextures count.
		virtual void Copy(const ITexture& source, IBuffer& destination, std::span<const CopyableFootprint> footprints, std::span<const CopySubTextureBox> boxes) = 0;
	};
}

namespace PonyEngine::RenderDevice
{
	void ICopyCommandList::Barrier(const BufferBarrier& bufferBarrier)
	{
		Barrier(std::span(&bufferBarrier, 1uz));
	}

	void ICopyCommandList::Barrier(const std::span<const BufferBarrier> bufferBarriers)
	{
		Barrier(bufferBarriers, std::span<const TextureBarrier>());
	}

	void ICopyCommandList::Barrier(const TextureBarrier& textureBarrier)
	{
		Barrier(std::span(&textureBarrier, 1uz));
	}

	void ICopyCommandList::Barrier(const std::span<const TextureBarrier> textureBarriers)
	{
		Barrier(std::span<const BufferBarrier>(), textureBarriers);
	}

	void ICopyCommandList::Barrier(const std::span<const BufferBarrier> bufferBarriers, const TextureBarrier& textureBarrier)
	{
		Barrier(bufferBarriers, std::span(&textureBarrier, 1uz));
	}

	void ICopyCommandList::Barrier(const BufferBarrier& bufferBarrier, const std::span<const TextureBarrier> textureBarriers)
	{
		Barrier(std::span(&bufferBarrier, 1uz), textureBarriers);
	}

	void ICopyCommandList::Copy(const IBuffer& source, IBuffer& destination, const CopyBufferRange& range)
	{
		Copy(source, destination, std::span(&range, 1uz));
	}

	void ICopyCommandList::Copy(const ITexture& source, ITexture& destination, const CopySubTextureIndex& subTexture)
	{
		Copy(source, destination, std::span(&subTexture, 1uz));
	}

	void ICopyCommandList::Copy(const ITexture& source, ITexture& destination, const CopySubTextureIndex& subTexture, const CopySubTextureBox& box)
	{
		Copy(source, destination, std::span(&subTexture, 1uz), std::span(&box, 1uz));
	}

	void ICopyCommandList::Copy(const IBuffer& source, ITexture& destination, const CopyableFootprint& footprint)
	{
		Copy(source, destination, std::span(&footprint, 1uz));
	}

	void ICopyCommandList::Copy(const IBuffer& source, ITexture& destination, const CopyableFootprint& footprint, const CopySubTextureBox& box)
	{
		Copy(source, destination, std::span(&footprint, 1uz), std::span(&box, 1uz));
	}

	void ICopyCommandList::Copy(const ITexture& source, IBuffer& destination, const CopyableFootprint& footprint)
	{
		Copy(source, destination, std::span(&footprint, 1uz));
	}

	void ICopyCommandList::Copy(const ITexture& source, IBuffer& destination, const CopyableFootprint& footprint, const CopySubTextureBox& box)
	{
		Copy(source, destination, std::span(&footprint, 1uz), std::span(&box, 1uz));
	}
}
