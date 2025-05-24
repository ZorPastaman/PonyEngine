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

import <cstdint>;
import <optional>;

import :Buffer;
import :Texture;

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief Direct3D12 copy pipeline.
	/// @note The same resource can't be used as a source and a destination in one tick.
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
		/// @param sourceSubresource Source subresource index.
		/// @param destinationSubresource Destination subresource index.
		/// @param destinationX Destination x-coordinate.
		/// @param destinationY Destination y-coordinate.
		/// @param destinationZ Destination z-coordinate.
		/// @param sourceBox Size of the source to copy.
		virtual void AddCopyTask(Texture& source, Texture& destination, 
			std::uint32_t sourceSubresource, std::uint32_t destinationSubresource,
			std::uint32_t destinationX, std::uint32_t destinationY, std::uint32_t destinationZ, const std::optional<D3D12_BOX>& sourceBox) = 0;
		/// @brief Adds a buffer to a texture copy task.
		/// @param source Copy source.
		/// @param destination Copy destination.
		/// @param sourceFootprint Source footprint.
		/// @param destinationSubresource Destination subresource index.
		/// @param destinationX Destination x-coordinate.
		/// @param destinationY Destination y-coordinate.
		/// @param destinationZ Destination z-coordinate.
		virtual void AddCopyTask(Buffer& source, Texture& destination,
			const D3D12_PLACED_SUBRESOURCE_FOOTPRINT& sourceFootprint, std::uint32_t destinationSubresource,
			std::uint32_t destinationX, std::uint32_t destinationY, std::uint32_t destinationZ) = 0;
		/// @brief Adds a texture to a buffer copy task.
		/// @param source Copy source.
		/// @param destination Copy destination.
		/// @param sourceSubresource Source subresource index.
		/// @param destinationFootprint Destination footprint.
		/// @param sourceBox Size of the source to copy.
		virtual void AddCopyTask(Texture& source, Buffer& destination,
			std::uint32_t sourceSubresource, const D3D12_PLACED_SUBRESOURCE_FOOTPRINT& destinationFootprint,
			const std::optional<D3D12_BOX>& sourceBox) = 0;
	};
}
