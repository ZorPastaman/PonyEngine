/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Utility/Enum.h"

export module PonyEngine.Render:TextureFormat;

import <algorithm>;
import <array>;
import <cstddef>;
import <cstdint>;
import <ostream>;
import <string_view>;

import :TextureDimension;

namespace PonyEngine::Render
{
	/// @brief Texture format names.
	constexpr std::array<std::string_view, 64> TextureFormatNames
	{
		"Unknown",
		"R32G32B32A32_Float",
		"R32G32B32A32_Uint",
		"R32G32B32A32_Sint",
		"R32G32B32_Float",
		"R32G32B32_Uint",
		"R32G32B32_Sint",
		"R16G16B16A16_Float",
		"R16G16B16A16_Unorm",
		"R16G16B16A16_Uint",
		"R16G16B16A16_Snorm",
		"R16G16B16A16_Sint",
		"R32G32_Float",
		"R32G32_Uint",
		"R32G32_Sint",
		"D32_Float_S8X24_Uint",
		"R10G10B10A2_Unorm",
		"R10G10B10A2_Uint",
		"R11G11B10_Float",
		"R8G8B8A8_Unorm",
		"R8G8B8A8_Uint",
		"R8G8B8A8_Snorm",
		"R8G8B8A8_Sint",
		"R16G16_Float",
		"R16G16_Unorm",
		"R16G16_Uint",
		"R16G16_Snorm",
		"R16G16_Sint",
		"D32_Float",
		"R32_Float",
		"R32_Uint",
		"R32_Sint",
		"D24_Unorm_S8_Uint",
		"R8G8_Unorm",
		"R8G8_Uint",
		"R8G8_Snorm",
		"R8G8_Sint",
		"D16_Unorm",
		"R16_Float",
		"R16_Unorm",
		"R16_Uint",
		"R16_Snorm",
		"R16_Sint",
		"R8_Unorm",
		"R8_Uint",
		"R8_Snorm",
		"R8_Sint",
		"A8_Unorm",
		"B8G8R8A8_Unorm",
		"B8G8R8X8_Unorm",
		"B5G6R5_Unorm",
		"B5G5R5A1_Unorm",
		"B4G4R4A4_Unorm",
		"BC1_Unorm",
		"BC2_Unorm",
		"BC3_Unorm",
		"BC4_Unorm",
		"BC4_Snorm",
		"BC5_Unorm",
		"BC5_Snorm",
		"BC6H_UF16",
		"BC6H_SF16",
		"BC7_Unorm",
		"Invalid"
	};

	/// @brief Pixel data type names.
	constexpr std::array<std::string_view, 10> PixelDataTypeNames
	{
		"Unknown",
		"Snorm",
		"Unorm",
		"Sint",
		"Uint",
		"Sfloat",
		"Ufloat",
		"Depth",
		"DepthStencil"
		"Invalid"
	};

	/// @brief Texture feature names.
	constexpr std::array<std::string_view, 9> TextureFeatureNames
	{
		"Pixel",
		"SRGB",
		"RenderTarget",
		"DepthStencil",
		"SwapChain",
		"Blendable",
		"LogicBlendable",
		"MSAA",
		"Invalid"
	};
}

export namespace PonyEngine::Render
{
	/// @brief Texture format.
	enum class TextureFormat : std::uint8_t
	{
		Unknown,
		R32G32B32A32_Float,
		R32G32B32A32_Uint,
		R32G32B32A32_Sint,
		R32G32B32_Float,
		R32G32B32_Uint,
		R32G32B32_Sint,
		R16G16B16A16_Float,
		R16G16B16A16_Unorm,
		R16G16B16A16_Uint,
		R16G16B16A16_Snorm,
		R16G16B16A16_Sint,
		R32G32_Float,
		R32G32_Uint,
		R32G32_Sint,
		D32_Float_S8X24_Uint,
		R10G10B10A2_Unorm,
		R10G10B10A2_Uint,
		R11G11B10_Float,
		R8G8B8A8_Unorm,
		R8G8B8A8_Uint,
		R8G8B8A8_Snorm,
		R8G8B8A8_Sint,
		R16G16_Float,
		R16G16_Unorm,
		R16G16_Uint,
		R16G16_Snorm,
		R16G16_Sint,
		D32_Float,
		R32_Float,
		R32_Uint,
		R32_Sint,
		D24_Unorm_S8_Uint,
		R8G8_Unorm,
		R8G8_Uint,
		R8G8_Snorm,
		R8G8_Sint,
		D16_Unorm,
		R16_Float,
		R16_Unorm,
		R16_Uint,
		R16_Snorm,
		R16_Sint,
		R8_Unorm,
		R8_Uint,
		R8_Snorm,
		R8_Sint,
		A8_Unorm,
		B8G8R8A8_Unorm,
		B8G8R8X8_Unorm,
		B5G6R5_Unorm,
		B5G5R5A1_Unorm,
		B4G4R4A4_Unorm,
		BC1_Unorm,
		BC2_Unorm,
		BC3_Unorm,
		BC4_Unorm,
		BC4_Snorm,
		BC5_Unorm,
		BC5_Snorm,
		BC6H_UF16,
		BC6H_SF16,
		BC7_Unorm
	};

	/// @brief Pixel data types.
	enum class PixelDataType : std::uint8_t
	{
		Unknown,
		Snorm,
		Unorm,
		Sint,
		Uint,
		Sfloat,
		Ufloat,
		Depth,
		DepthStencil
	};

	/// @brief Texture features.
	enum class TextureFeature : std::uint16_t
	{
		None = 0,
		/// @brief Is an individual pixel readable and writable?
		Pixel = 1 << 0,
		/// @brief Is a format compatible with sRGB? The engine works only with linear space. But if a texture is used as an output render target and it's sRGB compatible, its output will be converted to srgb.
		SRGB = 1 << 1,
		/// @brief Is a format render target compatible?
		RenderTarget = 1 << 2,
		/// @brief Is a format depth stencil compatible?
		DepthStencil = 1 << 3,
		/// @brief Is a format swap chain buffer compatible?
		SwapChain = 1 << 4,
		/// @brief Are blend operations supported?
		Blendable = 1 << 5,
		/// @brief Are logic blend operations supported?
		LogicBlendable = 1 << 6,
		/// @brief Is a format msaa compatible?
		MSAA = 1 << 7,
		All = Pixel | SRGB | RenderTarget | DepthStencil | SwapChain | Blendable | LogicBlendable | MSAA
	};

	ENUM_VALUE_FEATURES(TextureFormat, TextureFormatNames)
	ENUM_VALUE_FEATURES(PixelDataType, PixelDataTypeNames)
	ENUM_MASK_FEATURES(TextureFeature, TextureFeatureNames)

	/// @brief Texture format info.
	struct TextureFormatInfo final
	{
		TextureFeature features; ///< Texture format features.
		TextureDimensionMask supportedDimensions; ///< Supported dimensions. It's a dimension mask.
		PixelDataType pixelDataType; ///< Pixel data type. For depth stencil formats it's unknown.
		std::uint8_t blockSize; ///< Block size in bytes. For uncompressed formats it's a pixel size.
		std::uint8_t blockWidth; ///< Block width in pixels. For uncompressed formats it's always 1.
		std::uint8_t blockHeight; ///< Block height in pixels. For uncompressed formats it's always 1.
		std::uint8_t blockDepth; ///< Block depth in pixels. For uncompressed formats it's always 1.
		std::uint8_t redBits; ///< How many bits a red channel uses. For compressed format, it's 0.
		std::uint8_t greenBits; ///< How many bits a green channel uses. For compressed format, it's 0.
		std::uint8_t blueBits; ///< How many bits a blue channel uses. For compressed format, it's 0.
		std::uint8_t alphaBits; ///< How many bits an alpha channel uses. For compressed format, it's 0.
		std::uint8_t depthBits; ///< How many bits a depth channel uses. For compressed format, it's 0.
		std::uint8_t stencilBits; ///< How many bits a stencil channel uses. For compressed format, it's 0.
		bool compressed; ///< Is it a compressed format?
		bool supportedByPlatform; ///< Is the format supported by a current platform?
	};
}
