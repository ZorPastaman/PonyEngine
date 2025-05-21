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

#include "PonyDebug/Log/Log.h"

export module PonyEngine.Render.Detail:TextureManager;

import <cstddef>;
import <cstdint>;
import <memory>;
import <stdexcept>;
import <unordered_map>;
import <vector>;

import PonyBase.Utility;

import PonyDebug.Log;

import PonyEngine.Render;
import PonyEngine.Render.PixelHandlers;
import PonyEngine.Render.Types;

import :IRenderSystemContext;
import :Texture;
import :TextureDirtyFlag;

export namespace PonyEngine::Render
{
	/// @brief Texture manager.
	class TextureManager final : public ITextureManager
	{
	public:
		/// @brief Creates a texture manager.
		/// @param renderSystem Render system context.
		[[nodiscard("Pure constructor")]]
		explicit TextureManager(IRenderSystemContext& renderSystem) noexcept;
		TextureManager(const TextureManager&) = delete;
		TextureManager(TextureManager&&) = delete;

		~TextureManager() noexcept = default;

		[[nodiscard("Redundant call")]]
		virtual std::shared_ptr<ITexture> CreateTexture(const TextureParams& params) override;
		[[nodiscard("Pure function")]]
		virtual const TextureFormatInfo& FormatInfo(TextureFormat format) const noexcept override;

		/// @brief Tick the texture manager.
		void Tick();
		/// @brief Cleans out dead textures.
		void Clean();

		TextureManager& operator =(const TextureManager&) = delete;
		TextureManager& operator =(TextureManager&&) = delete;

	private:
		/// @brief Creates new textures on GPU.
		void Create();
		/// @brief Updates living textures.
		void Update();
		/// @brief Clears dirty flags and caches.
		void Clear() noexcept;

		IRenderSystemContext* renderSystem; ///< Render system context.

		std::unordered_map<TextureFormat, TextureFormatInfo> formatInfos; ///< Texture format infos.

		std::vector<std::shared_ptr<Texture>> textures; ///< Textures.
		std::vector<const Texture*> newTextures; ///< New textures and their clear values.
	};
}

namespace PonyEngine::Render
{
	/// @brief Static texture format infos. It doesn't contain info that is dependent on a runtime.
	const std::unordered_map<TextureFormat, TextureFormatInfo> StaticFormatInfos
	{
		{ TextureFormat::Unknown, TextureFormatInfo{.features = TextureFeature::None, .supportedDimensions = TextureDimensionMask::None, .pixelDataType = PixelDataType::Unknown, .blockSize = 0u, .blockWidth = 0u, .blockHeight = 0u, .blockDepth = 0u, .redBits = 0u, .blueBits = 0u, .greenBits = 0u, .alphaBits = 0u, .depthBits = 0u, .stencilBits = 0u, .compressed = false, .supportedByPlatform = false} },
		{ TextureFormat::R32G32B32A32_Float, TextureFormatInfo{.features = TextureFeature::Pixel, .supportedDimensions = TextureDimensionMask::None, .pixelDataType = PixelDataType::Sfloat, .blockSize = 16u, .blockWidth = 1u, .blockHeight = 1u, .blockDepth = 1u, .redBits = 32u, .greenBits = 32u, .blueBits = 32u, .alphaBits = 32u, .depthBits = 0u, .stencilBits = 0u, .compressed = false, .supportedByPlatform = false} },
		{ TextureFormat::R32G32B32A32_Uint, TextureFormatInfo{.features = TextureFeature::Pixel, .supportedDimensions = TextureDimensionMask::None, .pixelDataType = PixelDataType::Uint, .blockSize = 16u, .blockWidth = 1u, .blockHeight = 1u, .blockDepth = 1u, .redBits = 32u, .greenBits = 32u, .blueBits = 32u, .alphaBits = 32u, .depthBits = 0u, .stencilBits = 0u, .compressed = false, .supportedByPlatform = false} },
		{ TextureFormat::R32G32B32A32_Sint, TextureFormatInfo{.features = TextureFeature::Pixel, .supportedDimensions = TextureDimensionMask::None, .pixelDataType = PixelDataType::Sint, .blockSize = 16u, .blockWidth = 1u, .blockHeight = 1u, .blockDepth = 1u, .redBits = 32u, .greenBits = 32u, .blueBits = 32u, .alphaBits = 32u, .depthBits = 0u, .stencilBits = 0u, .compressed = false, .supportedByPlatform = false} },
		{ TextureFormat::R32G32B32_Float, TextureFormatInfo{.features = TextureFeature::Pixel, .supportedDimensions = TextureDimensionMask::None, .pixelDataType = PixelDataType::Sfloat, .blockSize = 12u, .blockWidth = 1u, .blockHeight = 1u, .blockDepth = 1u, .redBits = 32u, .greenBits = 32u, .blueBits = 32u, .alphaBits = 0u, .depthBits = 0u, .stencilBits = 0u, .compressed = false, .supportedByPlatform = false} },
		{ TextureFormat::R32G32B32_Uint, TextureFormatInfo{.features = TextureFeature::Pixel, .supportedDimensions = TextureDimensionMask::None, .pixelDataType = PixelDataType::Uint, .blockSize = 12u, .blockWidth = 1u, .blockHeight = 1u, .blockDepth = 1u, .redBits = 32u, .greenBits = 32u, .blueBits = 32u, .alphaBits = 0u, .depthBits = 0u, .stencilBits = 0u, .compressed = false, .supportedByPlatform = false} },
		{ TextureFormat::R32G32B32_Sint, TextureFormatInfo{.features = TextureFeature::Pixel, .supportedDimensions = TextureDimensionMask::None, .pixelDataType = PixelDataType::Sint, .blockSize = 12u, .blockWidth = 1u, .blockHeight = 1u, .blockDepth = 1u, .redBits = 32u, .greenBits = 32u, .blueBits = 32u, .alphaBits = 0u, .depthBits = 0u, .stencilBits = 0u, .compressed = false, .supportedByPlatform = false} },
		{ TextureFormat::R16G16B16A16_Float, TextureFormatInfo{.features = TextureFeature::Pixel, .supportedDimensions = TextureDimensionMask::None, .pixelDataType = PixelDataType::Sfloat, .blockSize = 8u, .blockWidth = 1u, .blockHeight = 1u, .blockDepth = 1u, .redBits = 16u, .greenBits = 16u, .blueBits = 16u, .alphaBits = 16u, .depthBits = 0u, .stencilBits = 0u, .compressed = false, .supportedByPlatform = false} },
		{ TextureFormat::R16G16B16A16_Unorm, TextureFormatInfo{.features = TextureFeature::Pixel, .supportedDimensions = TextureDimensionMask::None, .pixelDataType = PixelDataType::Unorm, .blockSize = 8u, .blockWidth = 1u, .blockHeight = 1u, .blockDepth = 1u, .redBits = 16u, .greenBits = 16u, .blueBits = 16u, .alphaBits = 16u, .depthBits = 0u, .stencilBits = 0u, .compressed = false, .supportedByPlatform = false} },
		{ TextureFormat::R16G16B16A16_Uint, TextureFormatInfo{.features = TextureFeature::Pixel, .supportedDimensions = TextureDimensionMask::None, .pixelDataType = PixelDataType::Uint, .blockSize = 8u, .blockWidth = 1u, .blockHeight = 1u, .blockDepth = 1u, .redBits = 16u, .greenBits = 16u, .blueBits = 16u, .alphaBits = 16u, .depthBits = 0u, .stencilBits = 0u, .compressed = false, .supportedByPlatform = false} },
		{ TextureFormat::R16G16B16A16_Snorm, TextureFormatInfo{.features = TextureFeature::Pixel, .supportedDimensions = TextureDimensionMask::None, .pixelDataType = PixelDataType::Snorm, .blockSize = 8u, .blockWidth = 1u, .blockHeight = 1u, .blockDepth = 1u, .redBits = 16u, .greenBits = 16u, .blueBits = 16u, .alphaBits = 16u, .depthBits = 0u, .stencilBits = 0u, .compressed = false, .supportedByPlatform = false} },
		{ TextureFormat::R16G16B16A16_Sint, TextureFormatInfo{.features = TextureFeature::Pixel, .supportedDimensions = TextureDimensionMask::None, .pixelDataType = PixelDataType::Sint, .blockSize = 8u, .blockWidth = 1u, .blockHeight = 1u, .blockDepth = 1u, .redBits = 16u, .greenBits = 16u, .blueBits = 16u, .alphaBits = 16u, .depthBits = 0u, .stencilBits = 0u, .compressed = false, .supportedByPlatform = false} },
		{ TextureFormat::R32G32_Float, TextureFormatInfo{.features = TextureFeature::Pixel, .supportedDimensions = TextureDimensionMask::None, .pixelDataType = PixelDataType::Sfloat, .blockSize = 8u, .blockWidth = 1u, .blockHeight = 1u, .blockDepth = 1u, .redBits = 32u, .greenBits = 32u, .blueBits = 0u, .alphaBits = 0u, .depthBits = 0u, .stencilBits = 0u, .compressed = false, .supportedByPlatform = false} },
		{ TextureFormat::R32G32_Uint, TextureFormatInfo{.features = TextureFeature::Pixel, .supportedDimensions = TextureDimensionMask::None, .pixelDataType = PixelDataType::Uint, .blockSize = 8u, .blockWidth = 1u, .blockHeight = 1u, .blockDepth = 1u, .redBits = 32u, .greenBits = 32u, .blueBits = 0u, .alphaBits = 0u, .depthBits = 0u, .stencilBits = 0u, .compressed = false, .supportedByPlatform = false} },
		{ TextureFormat::R32G32_Sint, TextureFormatInfo{.features = TextureFeature::Pixel, .supportedDimensions = TextureDimensionMask::None, .pixelDataType = PixelDataType::Sint, .blockSize = 8u, .blockWidth = 1u, .blockHeight = 1u, .blockDepth = 1u, .redBits = 32u, .greenBits = 32u, .blueBits = 0u, .alphaBits = 0u, .depthBits = 0u, .stencilBits = 0u, .compressed = false, .supportedByPlatform = false} },
		{ TextureFormat::D32_Float_S8X24_Uint, TextureFormatInfo{.features = TextureFeature::Pixel, .supportedDimensions = TextureDimensionMask::None, .pixelDataType = PixelDataType::DepthStencil, .blockSize = 8u, .blockWidth = 1u, .blockHeight = 1u, .blockDepth = 1u, .redBits = 0u, .greenBits = 0u, .blueBits = 0u, .alphaBits = 0u, .depthBits = 32u, .stencilBits = 8u, .compressed = false, .supportedByPlatform = false} },
		{ TextureFormat::R10G10B10A2_Unorm, TextureFormatInfo{.features = TextureFeature::Pixel, .supportedDimensions = TextureDimensionMask::None, .pixelDataType = PixelDataType::Unorm, .blockSize = 4u, .blockWidth = 1u, .blockHeight = 1u, .blockDepth = 1u, .redBits = 10u, .greenBits = 10u, .blueBits = 10u, .alphaBits = 2u, .depthBits = 0u, .stencilBits = 0u, .compressed = false, .supportedByPlatform = false} },
		{ TextureFormat::R10G10B10A2_Uint, TextureFormatInfo{.features = TextureFeature::Pixel, .supportedDimensions = TextureDimensionMask::None, .pixelDataType = PixelDataType::Uint, .blockSize = 4u, .blockWidth = 1u, .blockHeight = 1u, .blockDepth = 1u, .redBits = 10u, .greenBits = 10u, .blueBits = 10u, .alphaBits = 2u, .depthBits = 0u, .stencilBits = 0u, .compressed = false, .supportedByPlatform = false} },
		{ TextureFormat::R11G11B10_Float, TextureFormatInfo{.features = TextureFeature::Pixel, .supportedDimensions = TextureDimensionMask::None, .pixelDataType = PixelDataType::Ufloat, .blockSize = 4u, .blockWidth = 1u, .blockHeight = 1u, .blockDepth = 1u, .redBits = 11u, .greenBits = 11u, .blueBits = 10u, .alphaBits = 0u, .depthBits = 0u, .stencilBits = 0u, .compressed = false, .supportedByPlatform = false} },
		{ TextureFormat::R8G8B8A8_Unorm, TextureFormatInfo{.features = TextureFeature::Pixel, .supportedDimensions = TextureDimensionMask::None, .pixelDataType = PixelDataType::Unorm, .blockSize = 4u, .blockWidth = 1u, .blockHeight = 1u, .blockDepth = 1u, .redBits = 8u, .greenBits = 8u, .blueBits = 8u, .alphaBits = 8u, .depthBits = 0u, .stencilBits = 0u, .compressed = false, .supportedByPlatform = false} },
		{ TextureFormat::R8G8B8A8_Uint, TextureFormatInfo{.features = TextureFeature::Pixel, .supportedDimensions = TextureDimensionMask::None, .pixelDataType = PixelDataType::Uint, .blockSize = 4u, .blockWidth = 1u, .blockHeight = 1u, .blockDepth = 1u, .redBits = 8u, .greenBits = 8u, .blueBits = 8u, .alphaBits = 8u, .depthBits = 0u, .stencilBits = 0u, .compressed = false, .supportedByPlatform = false} },
		{ TextureFormat::R8G8B8A8_Snorm, TextureFormatInfo{.features = TextureFeature::Pixel, .supportedDimensions = TextureDimensionMask::None, .pixelDataType = PixelDataType::Snorm, .blockSize = 4u, .blockWidth = 1u, .blockHeight = 1u, .blockDepth = 1u, .redBits = 8u, .greenBits = 8u, .blueBits = 8u, .alphaBits = 8u, .depthBits = 0u, .stencilBits = 0u, .compressed = false, .supportedByPlatform = false} },
		{ TextureFormat::R8G8B8A8_Sint, TextureFormatInfo{.features = TextureFeature::Pixel, .supportedDimensions = TextureDimensionMask::None, .pixelDataType = PixelDataType::Sint, .blockSize = 4u, .blockWidth = 1u, .blockHeight = 1u, .blockDepth = 1u, .redBits = 8u, .greenBits = 8u, .blueBits = 8u, .alphaBits = 8u, .depthBits = 0u, .stencilBits = 0u, .compressed = false, .supportedByPlatform = false} },
		{ TextureFormat::R16G16_Float, TextureFormatInfo{.features = TextureFeature::Pixel, .supportedDimensions = TextureDimensionMask::None, .pixelDataType = PixelDataType::Sfloat, .blockSize = 4u, .blockWidth = 1u, .blockHeight = 1u, .blockDepth = 1u, .redBits = 16u, .greenBits = 16u, .blueBits = 0u, .alphaBits = 0u, .depthBits = 0u, .stencilBits = 0u, .compressed = false, .supportedByPlatform = false} },
		{ TextureFormat::R16G16_Unorm, TextureFormatInfo{.features = TextureFeature::Pixel, .supportedDimensions = TextureDimensionMask::None, .pixelDataType = PixelDataType::Unorm, .blockSize = 4u, .blockWidth = 1u, .blockHeight = 1u, .blockDepth = 1u, .redBits = 16u, .greenBits = 16u, .blueBits = 0u, .alphaBits = 0u, .depthBits = 0u, .stencilBits = 0u, .compressed = false, .supportedByPlatform = false} },
		{ TextureFormat::R16G16_Uint, TextureFormatInfo{.features = TextureFeature::Pixel, .supportedDimensions = TextureDimensionMask::None, .pixelDataType = PixelDataType::Uint, .blockSize = 4u, .blockWidth = 1u, .blockHeight = 1u, .blockDepth = 1u, .redBits = 16u, .greenBits = 16u, .blueBits = 0u, .alphaBits = 0u, .depthBits = 0u, .stencilBits = 0u, .compressed = false, .supportedByPlatform = false} },
		{ TextureFormat::R16G16_Snorm, TextureFormatInfo{.features = TextureFeature::Pixel, .supportedDimensions = TextureDimensionMask::None, .pixelDataType = PixelDataType::Snorm, .blockSize = 4u, .blockWidth = 1u, .blockHeight = 1u, .blockDepth = 1u, .redBits = 16u, .greenBits = 16u, .blueBits = 0u, .alphaBits = 0u, .depthBits = 0u, .stencilBits = 0u, .compressed = false, .supportedByPlatform = false} },
		{ TextureFormat::R16G16_Sint, TextureFormatInfo{.features = TextureFeature::Pixel, .supportedDimensions = TextureDimensionMask::None, .pixelDataType = PixelDataType::Sint, .blockSize = 4u, .blockWidth = 1u, .blockHeight = 1u, .blockDepth = 1u, .redBits = 16u, .greenBits = 16u, .blueBits = 0u, .alphaBits = 0u, .depthBits = 0u, .stencilBits = 0u, .compressed = false, .supportedByPlatform = false} },
		{ TextureFormat::D32_Float, TextureFormatInfo{.features = TextureFeature::Pixel, .supportedDimensions = TextureDimensionMask::None, .pixelDataType = PixelDataType::Depth, .blockSize = 4u, .blockWidth = 1u, .blockHeight = 1u, .blockDepth = 1u, .redBits = 0u, .greenBits = 0u, .blueBits = 0u, .alphaBits = 0u, .depthBits = 32u, .stencilBits = 0u, .compressed = false, .supportedByPlatform = false} },
		{ TextureFormat::R32_Float, TextureFormatInfo{.features = TextureFeature::Pixel, .supportedDimensions = TextureDimensionMask::None, .pixelDataType = PixelDataType::Sfloat, .blockSize = 4u, .blockWidth = 1u, .blockHeight = 1u, .blockDepth = 1u, .redBits = 32u, .greenBits = 0u, .blueBits = 0u, .alphaBits = 0u, .depthBits = 0u, .stencilBits = 0u, .compressed = false, .supportedByPlatform = false} },
		{ TextureFormat::R32_Uint, TextureFormatInfo{.features = TextureFeature::Pixel, .supportedDimensions = TextureDimensionMask::None, .pixelDataType = PixelDataType::Uint, .blockSize = 4u, .blockWidth = 1u, .blockHeight = 1u, .blockDepth = 1u, .redBits = 32u, .greenBits = 0u, .blueBits = 0u, .alphaBits = 0u, .depthBits = 0u, .stencilBits = 0u, .compressed = false, .supportedByPlatform = false} },
		{ TextureFormat::R32_Sint, TextureFormatInfo{.features = TextureFeature::Pixel, .supportedDimensions = TextureDimensionMask::None, .pixelDataType = PixelDataType::Sint, .blockSize = 4u, .blockWidth = 1u, .blockHeight = 1u, .blockDepth = 1u, .redBits = 32u, .greenBits = 0u, .blueBits = 0u, .alphaBits = 0u, .depthBits = 0u, .stencilBits = 0u, .compressed = false, .supportedByPlatform = false} },
		{ TextureFormat::D24_Unorm_S8_Uint, TextureFormatInfo{.features = TextureFeature::Pixel, .supportedDimensions = TextureDimensionMask::None, .pixelDataType = PixelDataType::DepthStencil, .blockSize = 4u, .blockWidth = 1u, .blockHeight = 1u, .blockDepth = 1u, .redBits = 0u, .greenBits = 0u, .blueBits = 0u, .alphaBits = 0u, .depthBits = 24u, .stencilBits = 8u, .compressed = false, .supportedByPlatform = false} },
		{ TextureFormat::R8G8_Unorm, TextureFormatInfo{.features = TextureFeature::Pixel, .supportedDimensions = TextureDimensionMask::None, .pixelDataType = PixelDataType::Unorm, .blockSize = 2u, .blockWidth = 1u, .blockHeight = 1u, .blockDepth = 1u, .redBits = 8u, .greenBits = 8u, .blueBits = 0u, .alphaBits = 0u, .depthBits = 0u, .stencilBits = 0u, .compressed = false, .supportedByPlatform = false} },
		{ TextureFormat::R8G8_Uint, TextureFormatInfo{.features = TextureFeature::Pixel, .supportedDimensions = TextureDimensionMask::None, .pixelDataType = PixelDataType::Uint, .blockSize = 2u, .blockWidth = 1u, .blockHeight = 1u, .blockDepth = 1u, .redBits = 8u, .greenBits = 8u, .blueBits = 0u, .alphaBits = 0u, .depthBits = 0u, .stencilBits = 0u, .compressed = false, .supportedByPlatform = false} },
		{ TextureFormat::R8G8_Snorm, TextureFormatInfo{.features = TextureFeature::Pixel, .supportedDimensions = TextureDimensionMask::None, .pixelDataType = PixelDataType::Snorm, .blockSize = 2u, .blockWidth = 1u, .blockHeight = 1u, .blockDepth = 1u, .redBits = 8u, .greenBits = 8u, .blueBits = 0u, .alphaBits = 0u, .depthBits = 0u, .stencilBits = 0u, .compressed = false, .supportedByPlatform = false} },
		{ TextureFormat::R8G8_Sint, TextureFormatInfo{.features = TextureFeature::Pixel, .supportedDimensions = TextureDimensionMask::None, .pixelDataType = PixelDataType::Sint, .blockSize = 2u, .blockWidth = 1u, .blockHeight = 1u, .blockDepth = 1u, .redBits = 8u, .greenBits = 8u, .blueBits = 0u, .alphaBits = 0u, .depthBits = 0u, .stencilBits = 0u, .compressed = false, .supportedByPlatform = false} },
		{ TextureFormat::D16_Unorm, TextureFormatInfo{.features = TextureFeature::Pixel, .supportedDimensions = TextureDimensionMask::None, .pixelDataType = PixelDataType::Depth, .blockSize = 2u, .blockWidth = 1u, .blockHeight = 1u, .blockDepth = 1u, .redBits = 0u, .greenBits = 0u, .blueBits = 0u, .alphaBits = 0u, .depthBits = 16u, .stencilBits = 0u, .compressed = false, .supportedByPlatform = false} },
		{ TextureFormat::R16_Float, TextureFormatInfo{.features = TextureFeature::Pixel, .supportedDimensions = TextureDimensionMask::None, .pixelDataType = PixelDataType::Sfloat, .blockSize = 2u, .blockWidth = 1u, .blockHeight = 1u, .blockDepth = 1u, .redBits = 16u, .greenBits = 0u, .blueBits = 0u, .alphaBits = 0u, .depthBits = 0u, .stencilBits = 0u, .compressed = false, .supportedByPlatform = false} },
		{ TextureFormat::R16_Unorm, TextureFormatInfo{.features = TextureFeature::Pixel, .supportedDimensions = TextureDimensionMask::None, .pixelDataType = PixelDataType::Unorm, .blockSize = 2u, .blockWidth = 1u, .blockHeight = 1u, .blockDepth = 1u, .redBits = 16u, .greenBits = 0u, .blueBits = 0u, .alphaBits = 0u, .depthBits = 0u, .stencilBits = 0u, .compressed = false, .supportedByPlatform = false} },
		{ TextureFormat::R16_Uint, TextureFormatInfo{.features = TextureFeature::Pixel, .supportedDimensions = TextureDimensionMask::None, .pixelDataType = PixelDataType::Uint, .blockSize = 2u, .blockWidth = 1u, .blockHeight = 1u, .blockDepth = 1u, .redBits = 16u, .greenBits = 0u, .blueBits = 0u, .alphaBits = 0u, .depthBits = 0u, .stencilBits = 0u, .compressed = false, .supportedByPlatform = false} },
		{ TextureFormat::R16_Snorm, TextureFormatInfo{.features = TextureFeature::Pixel, .supportedDimensions = TextureDimensionMask::None, .pixelDataType = PixelDataType::Snorm, .blockSize = 2u, .blockWidth = 1u, .blockHeight = 1u, .blockDepth = 1u, .redBits = 16u, .greenBits = 0u, .blueBits = 0u, .alphaBits = 0u, .depthBits = 0u, .stencilBits = 0u, .compressed = false, .supportedByPlatform = false} },
		{ TextureFormat::R16_Sint, TextureFormatInfo{.features = TextureFeature::Pixel, .supportedDimensions = TextureDimensionMask::None, .pixelDataType = PixelDataType::Sint, .blockSize = 2u, .blockWidth = 1u, .blockHeight = 1u, .blockDepth = 1u, .redBits = 16u, .greenBits = 0u, .blueBits = 0u, .alphaBits = 0u, .depthBits = 0u, .stencilBits = 0u, .compressed = false, .supportedByPlatform = false} },
		{ TextureFormat::R8_Unorm, TextureFormatInfo{.features = TextureFeature::Pixel, .supportedDimensions = TextureDimensionMask::None, .pixelDataType = PixelDataType::Unorm, .blockSize = 1u, .blockWidth = 1u, .blockHeight = 1u, .blockDepth = 1u, .redBits = 8u, .greenBits = 0u, .blueBits = 0u, .alphaBits = 0u, .depthBits = 0u, .stencilBits = 0u, .compressed = false, .supportedByPlatform = false} },
		{ TextureFormat::R8_Uint, TextureFormatInfo{.features = TextureFeature::Pixel, .supportedDimensions = TextureDimensionMask::None, .pixelDataType = PixelDataType::Uint, .blockSize = 1u, .blockWidth = 1u, .blockHeight = 1u, .blockDepth = 1u, .redBits = 8u, .greenBits = 0u, .blueBits = 0u, .alphaBits = 0u, .depthBits = 0u, .stencilBits = 0u, .compressed = false, .supportedByPlatform = false} },
		{ TextureFormat::R8_Snorm, TextureFormatInfo{.features = TextureFeature::Pixel, .supportedDimensions = TextureDimensionMask::None, .pixelDataType = PixelDataType::Snorm, .blockSize = 1u, .blockWidth = 1u, .blockHeight = 1u, .blockDepth = 1u, .redBits = 8u, .greenBits = 0u, .blueBits = 0u, .alphaBits = 0u, .depthBits = 0u, .stencilBits = 0u, .compressed = false, .supportedByPlatform = false} },
		{ TextureFormat::R8_Sint, TextureFormatInfo{.features = TextureFeature::Pixel, .supportedDimensions = TextureDimensionMask::None, .pixelDataType = PixelDataType::Sint, .blockSize = 1u, .blockWidth = 1u, .blockHeight = 1u, .blockDepth = 1u, .redBits = 8u, .greenBits = 0u, .blueBits = 0u, .alphaBits = 0u, .depthBits = 0u, .stencilBits = 0u, .compressed = false, .supportedByPlatform = false} },
		{ TextureFormat::A8_Unorm, TextureFormatInfo{.features = TextureFeature::Pixel, .supportedDimensions = TextureDimensionMask::None, .pixelDataType = PixelDataType::Unorm, .blockSize = 1u, .blockWidth = 1u, .blockHeight = 1u, .blockDepth = 1u, .redBits = 0u, .greenBits = 0u, .blueBits = 0u, .alphaBits = 8u, .depthBits = 0u, .stencilBits = 0u, .compressed = false, .supportedByPlatform = false} },
		{ TextureFormat::B8G8R8A8_Unorm, TextureFormatInfo{.features = TextureFeature::Pixel, .supportedDimensions = TextureDimensionMask::None, .pixelDataType = PixelDataType::Unorm, .blockSize = 4u, .blockWidth = 1u, .blockHeight = 1u, .blockDepth = 1u, .redBits = 8u, .greenBits = 8u, .blueBits = 8u, .alphaBits = 8u, .depthBits = 0u, .stencilBits = 0u, .compressed = false, .supportedByPlatform = false} },
		{ TextureFormat::B8G8R8X8_Unorm, TextureFormatInfo{.features = TextureFeature::Pixel, .supportedDimensions = TextureDimensionMask::None, .pixelDataType = PixelDataType::Unorm, .blockSize = 4u, .blockWidth = 1u, .blockHeight = 1u, .blockDepth = 1u, .redBits = 8u, .greenBits = 8u, .blueBits = 8u, .alphaBits = 0u, .depthBits = 0u, .stencilBits = 0u, .compressed = false, .supportedByPlatform = false} },
		{ TextureFormat::B5G6R5_Unorm, TextureFormatInfo{.features = TextureFeature::Pixel, .supportedDimensions = TextureDimensionMask::None, .pixelDataType = PixelDataType::Unorm, .blockSize = 2u, .blockWidth = 1u, .blockHeight = 1u, .blockDepth = 1u, .redBits = 5u, .greenBits = 6u, .blueBits = 5u, .alphaBits = 0u, .depthBits = 0u, .stencilBits = 0u, .compressed = false, .supportedByPlatform = false} },
		{ TextureFormat::B5G5R5A1_Unorm, TextureFormatInfo{.features = TextureFeature::Pixel, .supportedDimensions = TextureDimensionMask::None, .pixelDataType = PixelDataType::Unorm, .blockSize = 2u, .blockWidth = 1u, .blockHeight = 1u, .blockDepth = 1u, .redBits = 5u, .greenBits = 5u, .blueBits = 5u, .alphaBits = 1u, .depthBits = 0u, .stencilBits = 0u, .compressed = false, .supportedByPlatform = false} },
		{ TextureFormat::B4G4R4A4_Unorm, TextureFormatInfo{.features = TextureFeature::Pixel, .supportedDimensions = TextureDimensionMask::None, .pixelDataType = PixelDataType::Unorm, .blockSize = 2u, .blockWidth = 1u, .blockHeight = 1u, .blockDepth = 1u, .redBits = 4u, .greenBits = 4u, .blueBits = 4u, .alphaBits = 4u, .depthBits = 0u, .stencilBits = 0u, .compressed = false, .supportedByPlatform = false} },
		{ TextureFormat::BC1_Unorm, TextureFormatInfo{.features = TextureFeature::None, .supportedDimensions = TextureDimensionMask::None, .pixelDataType = PixelDataType::Unorm, .blockSize = 8u, .blockWidth = 4u, .blockHeight = 4u, .blockDepth = 1u, .redBits = 0u, .greenBits = 0u, .blueBits = 0u, .alphaBits = 0u, .depthBits = 0u, .stencilBits = 0u, .compressed = true, .supportedByPlatform = false} },
		{ TextureFormat::BC2_Unorm, TextureFormatInfo{.features = TextureFeature::None, .supportedDimensions = TextureDimensionMask::None, .pixelDataType = PixelDataType::Unorm, .blockSize = 16u, .blockWidth = 4u, .blockHeight = 4u, .blockDepth = 1u, .redBits = 0u, .greenBits = 0u, .blueBits = 0u, .alphaBits = 0u, .depthBits = 0u, .stencilBits = 0u, .compressed = true, .supportedByPlatform = false} },
		{ TextureFormat::BC3_Unorm, TextureFormatInfo{.features = TextureFeature::None, .supportedDimensions = TextureDimensionMask::None, .pixelDataType = PixelDataType::Unorm, .blockSize = 16u, .blockWidth = 4u, .blockHeight = 4u, .blockDepth = 1u, .redBits = 0u, .greenBits = 0u, .blueBits = 0u, .alphaBits = 0u, .depthBits = 0u, .stencilBits = 0u, .compressed = true, .supportedByPlatform = false} },
		{ TextureFormat::BC4_Unorm, TextureFormatInfo{.features = TextureFeature::None, .supportedDimensions = TextureDimensionMask::None, .pixelDataType = PixelDataType::Unorm, .blockSize = 8u, .blockWidth = 4u, .blockHeight = 4u, .blockDepth = 1u, .redBits = 0u, .greenBits = 0u, .blueBits = 0u, .alphaBits = 0u, .depthBits = 0u, .stencilBits = 0u, .compressed = true, .supportedByPlatform = false} },
		{ TextureFormat::BC4_Snorm, TextureFormatInfo{.features = TextureFeature::None, .supportedDimensions = TextureDimensionMask::None, .pixelDataType = PixelDataType::Snorm, .blockSize = 8u, .blockWidth = 4u, .blockHeight = 4u, .blockDepth = 1u, .redBits = 0u, .greenBits = 0u, .blueBits = 0u, .alphaBits = 0u, .depthBits = 0u, .stencilBits = 0u, .compressed = true, .supportedByPlatform = false} },
		{ TextureFormat::BC5_Unorm, TextureFormatInfo{.features = TextureFeature::None, .supportedDimensions = TextureDimensionMask::None, .pixelDataType = PixelDataType::Unorm, .blockSize = 16u, .blockWidth = 4u, .blockHeight = 4u, .blockDepth = 1u, .redBits = 0u, .greenBits = 0u, .blueBits = 0u, .alphaBits = 0u, .depthBits = 0u, .stencilBits = 0u, .compressed = true, .supportedByPlatform = false} },
		{ TextureFormat::BC5_Snorm, TextureFormatInfo{.features = TextureFeature::None, .supportedDimensions = TextureDimensionMask::None, .pixelDataType = PixelDataType::Snorm, .blockSize = 16u, .blockWidth = 4u, .blockHeight = 4u, .blockDepth = 1u, .redBits = 0u, .greenBits = 0u, .blueBits = 0u, .alphaBits = 0u, .depthBits = 0u, .stencilBits = 0u, .compressed = true, .supportedByPlatform = false} },
		{ TextureFormat::BC6H_UF16, TextureFormatInfo{.features = TextureFeature::None, .supportedDimensions = TextureDimensionMask::None, .pixelDataType = PixelDataType::Ufloat, .blockSize = 16u, .blockWidth = 4u, .blockHeight = 4u, .blockDepth = 1u, .redBits = 0u, .greenBits = 0u, .blueBits = 0u, .alphaBits = 0u, .depthBits = 0u, .stencilBits = 0u, .compressed = true, .supportedByPlatform = false} },
		{ TextureFormat::BC6H_SF16, TextureFormatInfo{.features = TextureFeature::None, .supportedDimensions = TextureDimensionMask::None, .pixelDataType = PixelDataType::Sfloat, .blockSize = 16u, .blockWidth = 4u, .blockHeight = 4u, .blockDepth = 1u, .redBits = 0u, .greenBits = 0u, .blueBits = 0u, .alphaBits = 0u, .depthBits = 0u, .stencilBits = 0u, .compressed = true, .supportedByPlatform = false} },
		{ TextureFormat::BC7_Unorm, TextureFormatInfo{.features = TextureFeature::None, .supportedDimensions = TextureDimensionMask::None, .pixelDataType = PixelDataType::Unorm, .blockSize = 16u, .blockWidth = 4u, .blockHeight = 4u, .blockDepth = 1u, .redBits = 0u, .greenBits = 0u, .blueBits = 0u, .alphaBits = 0u, .depthBits = 0u, .stencilBits = 0u, .compressed = true, .supportedByPlatform = false} }
	};

	/// @brief Unsupported pixel handler.
	const UnsupportedPixelHandler UnsupportedPixelHandler;
	/// @brief R32G32B32A32_Float pixel handler.
	const UniformPixelHandler<float, 0, 1, 2, 3, true, true, true, true> R32G32B32A32FloatPixelHandler;
	/// @brief R32G32B32A32_Uint pixel handler.
	const UniformPixelHandler<std::uint32_t, 0, 1, 2, 3, true, true, true, true> R32G32B32A32UintPixelHandler;
	/// @brief R32G32B32A32_Sint pixel handler.
	const UniformPixelHandler<std::int32_t, 0, 1, 2, 3, true, true, true, true> R32G32B32A32SintPixelHandler;
	/// @brief R32G32B32_Float pixel handler.
	const UniformPixelHandler<float, 0, 1, 2, 0, true, true, true, false> R32G32B32FloatPixelHandler;
	/// @brief R32G32B32_Uint pixel handler.
	const UniformPixelHandler<std::uint32_t, 0, 1, 2, 0, true, true, true, false> R32G32B32UintPixelHandler;
	/// @brief R32G32B32_Sint pixel handler.
	const UniformPixelHandler<std::int32_t, 0, 1, 2, 0, true, true, true, false> R32G32B32SintPixelHandler;
	/// @brief R16G16B16A16_Float pixel handler.
	const UniformPixelHandler<Half, 0, 1, 2, 3, true, true, true, true> R16G16B16A16FloatPixelHandler;
	/// @brief R16G16B16A16_Unorm pixel handler
	const UniformPixelHandler<Unorm16, 0, 1, 2, 3, true, true, true, true> R16G16B16A16UnormPixelHandler;
	/// @brief R16G16B16A16_Uint pixel handler.
	const UniformPixelHandler<std::uint16_t, 0, 1, 2, 3, true, true, true, true> R16G16B16A16UintPixelHandler;
	/// @brief R16G16B16A16_Snorm pixel handler.
	const UniformPixelHandler<Snorm16, 0, 1, 2, 3, true, true, true, true> R16G16B16A16SnormPixelHandler;
	/// @brief R16G16B16A16_Sint pixel handler.
	const UniformPixelHandler<std::int16_t, 0, 1, 2, 3, true, true, true, true> R16G16B16A16SintPixelHandler;
	/// @brief R32G32_Float pixel handler.
	const UniformPixelHandler<float, 0, 1, 0, 0, true, true, false, false> R32G32FloatPixelHandler;
	/// @brief R32G32_Uint pixel handler.
	const UniformPixelHandler<std::uint32_t, 0, 1, 0, 0, true, true, false, false> R32G32UintPixelHandler;
	/// @brief R32G32_Sint pixel handler.
	const UniformPixelHandler<std::int32_t, 0, 1, 0, 0, true, true, false, false> R32G32SintPixelHandler;
	/// @brief R10G10B10A2_Unorm pixel handler.
	const UnormPixelHandler<0, 10, 20, 30, 10, 10, 10, 2> R10G10B10A2UnormPixelHandler;
	/// @brief R10G10B10A2_Uint pixel handler.
	const UintPixelHandler<0, 10, 20, 30, 10, 10, 10, 2> R10G10B10A2UintPixelHandler;
	/// @brief R11G11B10_Float pixel handler.
	const UfloatPixelHandler<0, 11, 22, 0, 5, 6, 5, 6, 5, 5, 0, 0> R11G11B10FloatPixelHandler;
	/// @brief R8G8B8A8_Unorm pixel handler.
	const UniformPixelHandler<Unorm8, 0, 1, 2, 3, true, true, true, true> R8G8B8A8UnormPixelHandler;
	/// @brief R8G8B8A8_Uint pixel handler.
	const UniformPixelHandler<std::uint8_t, 0, 1, 2, 3, true, true, true, true> R8G8B8A8UintPixelHandler;
	/// @brief R8G8B8A8_Snorm pixel handler.
	const UniformPixelHandler<Snorm8, 0, 1, 2, 3, true, true, true, true> R8G8B8A8SnormPixelHandler;
	/// @brief R8G8B8A8_Sint pixel handler.
	const UniformPixelHandler<std::int8_t, 0, 1, 2, 3, true, true, true, true> R8G8B8A8SintPixelHandler;
	/// @brief R16G16_Float pixel handler.
	const UniformPixelHandler<Half, 0, 1, 0, 0, true, true, false, false> R16G16FloatPixelHandler;
	/// @brief R16G16_Unorm pixel handler.
	const UniformPixelHandler<Unorm16, 0, 1, 0, 0, true, true, false, false> R16G16UnormPixelHandler;
	/// @brief R16G16_Uint pixel handler.
	const UniformPixelHandler<std::uint16_t, 0, 1, 0, 0, true, true, false, false> R16G16UintPixelHandler;
	/// @brief R16G16_Snorm pixel handler.
	const UniformPixelHandler<Snorm16, 0, 1, 0, 0, true, true, false, false> R16G16SnormPixelHandler;
	/// @brief R16G16_Sint pixel handler.
	const UniformPixelHandler<std::int16_t, 0, 1, 0, 0, true, true, false, false> R16G16SintPixelHandler;
	/// @brief R32_Float pixel handler.
	const UniformPixelHandler<float, 0, 0, 0, 0, true, false, false, false> R32FloatPixelHandler;
	/// @brief R32_Uint pixel handler.
	const UniformPixelHandler<std::uint32_t, 0, 0, 0, 0, true, false, false, false> R32UintPixelHandler;
	/// @brief R32_Sint pixel handler.
	const UniformPixelHandler<std::int32_t, 0, 0, 0, 0, true, false, false, false> R32SintPixelHandler;
	/// @brief R8G8_Unorm pixel handler.
	const UniformPixelHandler<Unorm8, 0, 1, 0, 0, true, true, false, false> R8G8UnormPixelHandler;
	/// @brief R8G8_Uint pixel handler.
	const UniformPixelHandler<std::uint8_t, 0, 1, 0, 0, true, true, false, false> R8G8UintPixelHandler;
	/// @brief R8G8_Snorm pixel handler.
	const UniformPixelHandler<Snorm8, 0, 1, 0, 0, true, true, false, false> R8G8SnormPixelHandler;
	/// @brief R8G8_Sint pixel handler.
	const UniformPixelHandler<std::int8_t, 0, 1, 0, 0, true, true, false, false> R8G8SintPixelHandler;
	/// @brief R16_Float pixel handler.
	const UniformPixelHandler<Half, 0, 0, 0, 0, true, false, false, false> R16FloatPixelHandler;
	/// @brief R16_Unorm pixel handler.
	const UniformPixelHandler<Unorm16, 0, 0, 0, 0, true, false, false, false> R16UnormPixelHandler;
	/// @brief R16_Uint pixel handler.
	const UniformPixelHandler<std::uint16_t, 0, 0, 0, 0, true, false, false, false> R16UintPixelHandler;
	/// @brief R16_Snorm pixel handler.
	const UniformPixelHandler<Snorm16, 0, 0, 0, 0, true, false, false, false> R16SnormPixelHandler;
	/// @brief R16_Sint pixel handler.
	const UniformPixelHandler<std::int16_t, 0, 0, 0, 0, true, false, false, false> R16SintPixelHandler;
	/// @brief R8_Unorm pixel handler.
	const UniformPixelHandler<Unorm8, 0, 0, 0, 0, true, false, false, false> R8UnormPixelHandler;
	/// @brief R8_Uint pixel handler.
	const UniformPixelHandler<std::uint8_t, 0, 0, 0, 0, true, false, false, false> R8UintPixelHandler;
	/// @brief R8_Snorm pixel handler.
	const UniformPixelHandler<Snorm8, 0, 0, 0, 0, true, false, false, false> R8SnormPixelHandler;
	/// @brief R8_Sint pixel handler.
	const UniformPixelHandler<std::int8_t, 0, 0, 0, 0, true, false, false, false> R8SintPixelHandler;
	/// @brief A8_Unorm pixel handler.
	const UniformPixelHandler<Unorm8, 0, 0, 0, 0, false, false, false, true> A8UnormPixelHandler;
	/// @brief B8G8R8A8_Unorm pixel handler.
	const UniformPixelHandler<Unorm8, 2, 1, 0, 3, true, true, true, true> B8G8R8A8UnormPixelHandler;
	/// @brief B8G8R8X8_Unorm pixel handler.
	const UniformPixelHandler<Unorm8, 2, 1, 0, 0, true, true, true, false> B8G8R8X8UnormPixelHandler;
	/// @brief B5G6R5_Unorm pixel handler.
	const UnormPixelHandler<11, 5, 0, 0, 5, 6, 5, 0> B5G6R5UnormPixelHandler;
	/// @brief B5G5R5A1_Unorm pixel handler.
	const UnormPixelHandler<10, 5, 0, 15, 5, 5, 5, 1> B5G5R5A1UnormPixelHandler;
	/// @brief B4G4R4A4_Unorm pixel handler.
	const UnormPixelHandler<8, 4, 0, 12, 4, 4, 4, 4> B4G4R4A4UnormPixelHandler;

	/// @brief Pixel handlers.
	const std::unordered_map<TextureFormat, const IPixelHandler*> PixelHandlers
	{
		{ TextureFormat::Unknown, &UnsupportedPixelHandler },
		{ TextureFormat::R32G32B32A32_Float, &R32G32B32A32FloatPixelHandler },
		{ TextureFormat::R32G32B32A32_Uint, &R32G32B32A32UintPixelHandler },
		{ TextureFormat::R32G32B32A32_Sint, &R32G32B32A32SintPixelHandler },
		{ TextureFormat::R32G32B32_Float, &R32G32B32FloatPixelHandler },
		{ TextureFormat::R32G32B32_Uint, &R32G32B32UintPixelHandler },
		{ TextureFormat::R32G32B32_Sint, &R32G32B32SintPixelHandler },
		{ TextureFormat::R16G16B16A16_Float, &R16G16B16A16FloatPixelHandler },
		{ TextureFormat::R16G16B16A16_Unorm, &R16G16B16A16UnormPixelHandler },
		{ TextureFormat::R16G16B16A16_Uint, &R16G16B16A16UintPixelHandler },
		{ TextureFormat::R16G16B16A16_Snorm, &R16G16B16A16SnormPixelHandler },
		{ TextureFormat::R16G16B16A16_Sint, &R16G16B16A16SintPixelHandler },
		{ TextureFormat::R32G32_Float, &R32G32FloatPixelHandler },
		{ TextureFormat::R32G32_Uint, &R32G32UintPixelHandler },
		{ TextureFormat::R32G32_Sint, &R32G32SintPixelHandler },
		{ TextureFormat::D32_Float_S8X24_Uint, &UnsupportedPixelHandler },
		{ TextureFormat::R10G10B10A2_Unorm, &R10G10B10A2UnormPixelHandler },
		{ TextureFormat::R10G10B10A2_Uint, &R10G10B10A2UintPixelHandler },
		{ TextureFormat::R11G11B10_Float, &R11G11B10FloatPixelHandler },
		{ TextureFormat::R8G8B8A8_Unorm, &R8G8B8A8UnormPixelHandler },
		{ TextureFormat::R8G8B8A8_Uint, &R8G8B8A8UintPixelHandler },
		{ TextureFormat::R8G8B8A8_Snorm, &R8G8B8A8SnormPixelHandler },
		{ TextureFormat::R8G8B8A8_Sint, &R8G8B8A8SintPixelHandler },
		{ TextureFormat::R16G16_Float, &R16G16FloatPixelHandler },
		{ TextureFormat::R16G16_Unorm, &R16G16UnormPixelHandler },
		{ TextureFormat::R16G16_Uint, &R16G16UintPixelHandler },
		{ TextureFormat::R16G16_Snorm, &R16G16SnormPixelHandler },
		{ TextureFormat::R16G16_Sint, &R16G16SintPixelHandler },
		{ TextureFormat::D32_Float, &UnsupportedPixelHandler },
		{ TextureFormat::R32_Float, &R32FloatPixelHandler },
		{ TextureFormat::R32_Uint, &R32UintPixelHandler },
		{ TextureFormat::R32_Sint, &R32SintPixelHandler },
		{ TextureFormat::D24_Unorm_S8_Uint, &UnsupportedPixelHandler },
		{ TextureFormat::R8G8_Unorm, &R8G8UnormPixelHandler },
		{ TextureFormat::R8G8_Uint, &R8G8UintPixelHandler },
		{ TextureFormat::R8G8_Snorm, &R8G8SnormPixelHandler },
		{ TextureFormat::R8G8_Sint, &R8G8SintPixelHandler },
		{ TextureFormat::D16_Unorm, &UnsupportedPixelHandler },
		{ TextureFormat::R16_Float, &R16FloatPixelHandler },
		{ TextureFormat::R16_Unorm, &R16UnormPixelHandler },
		{ TextureFormat::R16_Uint, &R16UintPixelHandler },
		{ TextureFormat::R16_Snorm, &R16SnormPixelHandler },
		{ TextureFormat::R16_Sint, &R16SintPixelHandler },
		{ TextureFormat::R8_Unorm, &R8UnormPixelHandler },
		{ TextureFormat::R8_Uint, &R8UintPixelHandler },
		{ TextureFormat::R8_Snorm, &R8SnormPixelHandler },
		{ TextureFormat::R8_Sint, &R8SintPixelHandler },
		{ TextureFormat::A8_Unorm, &A8UnormPixelHandler },
		{ TextureFormat::B8G8R8A8_Unorm, &B8G8R8A8UnormPixelHandler },
		{ TextureFormat::B8G8R8X8_Unorm, &B8G8R8X8UnormPixelHandler },
		{ TextureFormat::B5G6R5_Unorm, &B5G6R5UnormPixelHandler },
		{ TextureFormat::B5G5R5A1_Unorm, &B5G5R5A1UnormPixelHandler },
		{ TextureFormat::B4G4R4A4_Unorm, &B4G4R4A4UnormPixelHandler },
		{ TextureFormat::BC1_Unorm, &UnsupportedPixelHandler },
		{ TextureFormat::BC2_Unorm, &UnsupportedPixelHandler },
		{ TextureFormat::BC3_Unorm, &UnsupportedPixelHandler },
		{ TextureFormat::BC4_Unorm, &UnsupportedPixelHandler },
		{ TextureFormat::BC4_Snorm, &UnsupportedPixelHandler },
		{ TextureFormat::BC5_Unorm, &UnsupportedPixelHandler },
		{ TextureFormat::BC5_Snorm, &UnsupportedPixelHandler },
		{ TextureFormat::BC6H_UF16, &UnsupportedPixelHandler },
		{ TextureFormat::BC6H_SF16, &UnsupportedPixelHandler },
		{ TextureFormat::BC7_Unorm, &UnsupportedPixelHandler }
	};

	TextureManager::TextureManager(IRenderSystemContext& renderSystem) noexcept :
		renderSystem{&renderSystem}
	{
		formatInfos.reserve(StaticFormatInfos.size());
		for (const auto& [format, staticInfo] : StaticFormatInfos)
		{
			TextureFormatInfo info = staticInfo;
			const auto [supported, dimensions, features] = this->renderSystem->RenderAgent().TextureAgent().TextureInfo(format);
			info.supportedDimensions = dimensions;
			info.features |= features;
			info.supportedByPlatform = supported;
			formatInfos[format] = info;
		}
	}

	std::shared_ptr<ITexture> TextureManager::CreateTexture(const TextureParams& params)
	{
		if (params.format == TextureFormat::Unknown) [[unlikely]]
		{
			throw std::invalid_argument("Can't create texture of unknown format.");
		}

		assert(formatInfos.contains(params.format) && "No texture format info.");
		const TextureFormatInfo& formatInfo = formatInfos.find(params.format)->second;

		if (!formatInfo.supportedByPlatform) [[unlikely]]
		{
			throw std::invalid_argument("Format is not supported by current platform.");
		}
		if (formatInfo.pixelDataType == PixelDataType::Depth || formatInfo.pixelDataType == PixelDataType::DepthStencil) [[unlikely]]
		{
			throw std::invalid_argument("Depth stencil textures can't be created as usual textures.");
		}
		if (!IsInMask(params.dimension, formatInfo.supportedDimensions)) [[unlikely]]
		{
			throw std::invalid_argument(PonyBase::Utility::SafeFormat("'{}' format doesn't support '{}' dimension.", ToString(params.format), ToString(params.dimension)));
		}
		if (params.width % formatInfo.blockWidth || params.height % formatInfo.blockHeight || params.depth % formatInfo.blockDepth) [[unlikely]]
		{
			throw std::invalid_argument(PonyBase::Utility::SafeFormat("Incorrect texture size. Size must be product of '{}' in width, '{}' in height and '{}' in depth.",
				formatInfo.blockWidth, formatInfo.blockHeight, formatInfo.blockDepth));
		}

		const std::uint32_t blockCount = params.width * params.height * params.depth / (formatInfo.blockWidth * formatInfo.blockHeight * formatInfo.blockDepth);
		const auto bufferParams = PonyBase::Container::BufferParams{.stride = formatInfo.blockSize, blockCount};

		assert(PixelHandlers.contains(params.format) && "No pixel handler.");
		const IPixelHandler* const pixelHandler = PixelHandlers.find(params.format)->second;

		const auto texture = std::make_shared<Texture>(params, bufferParams, *pixelHandler);
		textures.push_back(texture);
		newTextures.push_back(texture.get());

		return texture;
	}

	const TextureFormatInfo& TextureManager::FormatInfo(const TextureFormat format) const noexcept
	{
		if (const auto position = formatInfos.find(format); position != formatInfos.cend()) [[likely]]
		{
			return position->second;
		}

		assert(false && "Invalid texture format.");

		return formatInfos.find(TextureFormat::Unknown)->second;
	}

	void TextureManager::Tick()
	{
		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Verbose, "Create.");
		Create();
		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Verbose, "Update.");
		Update();
		PONY_LOG(renderSystem->Logger(), PonyDebug::Log::LogType::Verbose, "Clear.");
		Clear();
	}

	void TextureManager::Clean()
	{
		for (std::size_t i = textures.size(); i-- > 0; )
		{
			const std::shared_ptr<Texture>& texture = textures[i];
			if (texture.use_count() > 1L)
			{
				continue;
			}

			if (const auto position = std::ranges::find(newTextures, texture.get()); position != newTextures.cend())
			{
				newTextures.erase(position);
			}
			else
			{
				renderSystem->RenderAgent().TextureAgent().Destroy(*texture);
			}
			textures.erase(textures.cbegin() + i);
		}
	}

	void TextureManager::Create()
	{
		for (const Texture* texture : newTextures)
		{
			renderSystem->RenderAgent().TextureAgent().Create(*texture);
		}
	}

	void TextureManager::Update()
	{
		for (const std::shared_ptr<Texture>& texture : textures)
		{
			if (texture->DirtyFlags() != TextureDirtyFlag::None)
			{
				renderSystem->RenderAgent().TextureAgent().Update(*texture, texture->DirtyFlags());
			}
		}
	}

	void TextureManager::Clear() noexcept
	{
		for (const std::shared_ptr<Texture>& texture : textures)
		{
			texture->ResetDirty();
		}

		newTextures.clear();
	}
}
