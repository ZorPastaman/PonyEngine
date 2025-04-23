/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Core/Direct3D12/Framework.h"
#include "PonyBase/Utility/ObjectBody.h"

export module PonyEngine.Render.Direct3D12.Detail:ICopyPipeline;

import <optional>;
import <variant>;

import :Buffer;
import :Texture;

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief Direct3D12 copy pipeline.
	class ICopyPipeline
	{
		INTERFACE_BODY(ICopyPipeline)

		/// @brief Adds a buffer copy task.
		/// @param source Copy source.
		/// @param destination Copy destination.
		/// @note The buffers must be the same size.
		virtual void AddCopyTask(Buffer& source, Buffer& destination) = 0;
		/// @brief Adds a buffer region copy task.
		/// @param source Copy source.
		/// @param destination Copy destination.
		/// @param sourceOffset Source offset.
		/// @param destinationOffset Destination offset.
		/// @param size Copy size.
		virtual void AddCopyTask(Buffer& source, Buffer& destination, std::uint64_t sourceOffset, std::uint64_t destinationOffset, std::uint64_t size) = 0;

		/// @brief Adds a texture copy task.
		/// @param source Copy source.
		/// @param destination Copy destination.
		/// @note The textures must be compatible for copying.
		virtual void AddCopyTask(Texture& source, Texture& destination) = 0;
		/// @brief Adds a texture region copy task.
		/// @param source Copy source.
		/// @param destination Copy destination.
		/// @param sourceInfo Source footprint or subresource index.
		/// @param destinationInfo DestinationFootprint or subresource index. 
		/// @param destinationX Destination x-coordinate.
		/// @param destinationY Destination y-coordinate.
		/// @param destinationZ Destination z-coordinate.
		/// @param sourceBox Size of the source to copy.
		virtual void AddCopyTask(Texture& source, Texture& destination, 
			const std::variant<D3D12_PLACED_SUBRESOURCE_FOOTPRINT, UINT>& sourceInfo, const std::variant<D3D12_PLACED_SUBRESOURCE_FOOTPRINT, UINT>& destinationInfo,
			std::uint32_t destinationX, std::uint32_t destinationY, std::uint32_t destinationZ, const std::optional<D3D12_BOX>& sourceBox) = 0;
		// TODO: Last func in incorrect. D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT must use a buffer and UINT must use a texture.
	};
}
