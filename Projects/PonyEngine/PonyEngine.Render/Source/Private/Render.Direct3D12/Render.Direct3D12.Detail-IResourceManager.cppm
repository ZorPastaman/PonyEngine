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

export module PonyEngine.Render.Direct3D12.Detail:IResourceManager;

import <memory>;
import <utility>;

import PonyMath.Color;

import :Buffer;
import :HeapType;
import :Texture;

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief Direct3D12 resource manager.
	class IResourceManager
	{
		INTERFACE_BODY(IResourceManager)

		/// @brief Creates a buffer.
		/// @param size Buffer size.
		/// @param heapType Heap type.
		/// @return Creates buffer.
		[[nodiscard("Redendant call")]]
		virtual std::shared_ptr<Buffer> CreateBuffer(std::uint64_t size, HeapType heapType) = 0;

		/// @brief Creates a 1D texture.
		/// @param width Width.
		/// @param format Format.
		/// @param sampleDesc Sample description.
		/// @param heapType Heap type.
		/// @return Texture.
		[[nodiscard("Redendant call")]]
		virtual std::shared_ptr<Texture> CreateTexture1D(std::uint64_t width, DXGI_FORMAT format, DXGI_SAMPLE_DESC sampleDesc, HeapType heapType) = 0;
		/// @brief Creates a 2D texture.
		/// @param width Width.
		/// @param height Height.
		/// @param format Format.
		/// @param sampleDesc Sample description.
		/// @param heapType Heap type.
		/// @return Texture.
		[[nodiscard("Redendant call")]]
		virtual std::shared_ptr<Texture> CreateTexture2D(std::uint64_t width, std::uint32_t height, DXGI_FORMAT format, DXGI_SAMPLE_DESC sampleDesc, HeapType heapType) = 0;
		/// @brief Creates a 3D texture.
		/// @param width Width.
		/// @param height Height.
		/// @param depth Depth.
		/// @param format Format.
		/// @param sampleDesc Sample description.
		/// @param heapType Heap type.
		/// @return Texture.
		[[nodiscard("Redendant call")]]
		virtual std::shared_ptr<Texture> CreateTexture3D(std::uint64_t width, std::uint32_t height, std::uint16_t depth, DXGI_FORMAT format, DXGI_SAMPLE_DESC sampleDesc, HeapType heapType) = 0;

		/// @brief Creates a buffer for texture copying operations.
		/// @param width Width.
		/// @param format Format.
		/// @param sampleDesc Sample description.
		/// @param heapType Heap type.
		/// @return Buffer and its footprint.
		[[nodiscard("Redendant call")]]
		virtual std::pair<std::shared_ptr<Buffer>, D3D12_PLACED_SUBRESOURCE_FOOTPRINT> CreateTextureBuffer1D(std::uint64_t width, DXGI_FORMAT format, DXGI_SAMPLE_DESC sampleDesc, HeapType heapType) = 0;
		/// @brief Creates a buffer for texture copying operations.
		/// @param width Width.
		/// @param height Height.
		/// @param format Format.
		/// @param sampleDesc Sample description.
		/// @param heapType Heap type.
		/// @return Buffer and its footprint.
		[[nodiscard("Redendant call")]]
		virtual std::pair<std::shared_ptr<Buffer>, D3D12_PLACED_SUBRESOURCE_FOOTPRINT> CreateTextureBuffer2D(std::uint64_t width, std::uint32_t height, DXGI_FORMAT format, DXGI_SAMPLE_DESC sampleDesc, HeapType heapType) = 0;
		/// @brief Creates a buffer for texture copying operations.
		/// @param width Width.
		/// @param height Height.
		/// @param depth Depth.
		/// @param format Format.
		/// @param sampleDesc Sample description.
		/// @param heapType Heap type.
		/// @return Buffer and its footprint.
		[[nodiscard("Redendant call")]]
		virtual std::pair<std::shared_ptr<Buffer>, D3D12_PLACED_SUBRESOURCE_FOOTPRINT> CreateTextureBuffer3D(std::uint64_t width, std::uint32_t height, std::uint16_t depth, DXGI_FORMAT format, DXGI_SAMPLE_DESC sampleDesc, HeapType heapType) = 0;

		/// @brief Creates a render target.
		/// @param width Width.
		/// @param height Height.
		/// @param format Format.
		/// @param sampleDesc Sample description.
		/// @param clearColor Clear color.
		/// @return Texture.
		[[nodiscard("Redendant call")]]
		virtual std::shared_ptr<Texture> CreateRenderTarget(std::uint64_t width, std::uint32_t height, DXGI_FORMAT format, DXGI_SAMPLE_DESC sampleDesc, const PonyMath::Color::RGBA<float>& clearColor) = 0;
		/// @brief Creates a depth stencil.
		/// @param width Width.
		/// @param height Height.
		/// @param format Format.
		/// @param sampleDesc Sample description.
		/// @param depthStencilValue Clear value.
		/// @return Texture.
		[[nodiscard("Redendant call")]]
		virtual std::shared_ptr<Texture> CreateDepthStencil(std::uint64_t width, std::uint32_t height, DXGI_FORMAT format, DXGI_SAMPLE_DESC sampleDesc, D3D12_DEPTH_STENCIL_VALUE depthStencilValue) = 0;
	};
}
