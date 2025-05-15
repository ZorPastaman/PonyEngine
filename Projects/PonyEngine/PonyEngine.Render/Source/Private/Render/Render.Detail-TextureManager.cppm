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

import PonyEngine.Render;
import PonyEngine.Render.Detail.PixelHandlers;

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
		std::vector<std::pair<const Texture*, ClearValue>> newTextures; ///< New textures and their clear values.
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
	};

	/// @brief Pixel handlers.
	const std::unordered_map<TextureFormat, std::unique_ptr<const PixelHandler>> PixelHandlers
	{
		{ TextureFormat::Unknown, std::make_unique<UnsupportedPixelHandler>() },
		{ TextureFormat::R32G32B32A32_Float, std::make_unique<UniformColorPixelHandler<float, 4>>() }
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
		const PixelHandler* const pixelHandler = PixelHandlers.find(params.format)->second.get();

		const auto texture = std::make_shared<Texture>(params, bufferParams, *pixelHandler);
		textures.push_back(texture);
		newTextures.emplace_back(texture.get(), params.clear);

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

			if (const auto position = std::ranges::find_if(newTextures, [&](const std::pair<const Texture*, ClearValue>& p) { return p.first == texture.get(); }); position != newTextures.cend())
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
		for (const auto& [texture, clear] : newTextures)
		{
			renderSystem->RenderAgent().TextureAgent().Create(*texture, clear);
		}
	}

	void TextureManager::Update()
	{
		for (const std::shared_ptr<Texture>& texture : textures)
		{
			if (texture->DirtyFlags() != TextureDirtyFlag::None)
			{
				renderSystem->RenderAgent().TextureAgent().Update(*texture);
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
