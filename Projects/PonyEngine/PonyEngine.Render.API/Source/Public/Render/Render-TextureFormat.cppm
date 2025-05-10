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
	constexpr std::array<std::string_view, 59> TextureFormatNames
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
		"R16_Float",
		"D16_Unorm",
		"R16_Unorm",
		"R16_Uint",
		"R16_Snorm",
		"R16_Sint",
		"R8_Unorm",
		"R8_Uint",
		"R8_Snorm",
		"R8_Sint",
		"A8_Unorm",
		"R1_Unorm",
		"BC1_Unorm",
		"BC2_Unorm",
		"BC3_Unorm",
		"BC4_Unorm",
		"BC4_Snorm",
		"BC5_Unorm",
		"BC5_Snorm",
		"B8G8R8A8_Unorm",
		"B8G8R8X8_Unorm",
		"BC6H_UF16",
		"BC6H_SF16",
		"BC7_Unorm",
		"Invalid"
	};

	/// @brief Texture format type names.
	constexpr std::array<std::string_view, 4> TextureFormatTypeNames
	{
		"Unknown",
		"Color",
		"Depth",
		"Invalid"
	};

	/// @brief Pixel data type names.
	constexpr std::array<std::string_view, 8> PixelDataTypeNames
	{
		"Unknown",
		"Snorm",
		"Unorm",
		"Sint",
		"Uint",
		"Sfloat",
		"Ufloat",
		"Invalid"
	};

	/// @brief Texture feature names.
	constexpr std::array<std::string_view, 5> TextureFeatureNames
	{
		"Pixel",
		"SRGB",
		"RenderTarget",
		"DepthStencil",
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
		R16_Float,
		D16_Unorm,
		R16_Unorm,
		R16_Uint,
		R16_Snorm,
		R16_Sint,
		R8_Unorm,
		R8_Uint,
		R8_Snorm,
		R8_Sint,
		A8_Unorm,
		R1_Unorm,
		BC1_Unorm,
		BC2_Unorm,
		BC3_Unorm,
		BC4_Unorm,
		BC4_Snorm,
		BC5_Unorm,
		BC5_Snorm,
		B8G8R8A8_Unorm,
		B8G8R8X8_Unorm,
		BC6H_UF16,
		BC6H_SF16,
		BC7_Unorm
	};

	/// @brief Texture format type.
	enum class TextureFormatType : std::uint8_t
	{
		Unknown,
		Color,
		Depth
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
		Ufloat
	};

	/// @brief Texture features.
	enum class TextureFeature : std::uint8_t
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
		All = Pixel | SRGB | RenderTarget | DepthStencil
	};

	ENUM_VALUE_FEATURES(TextureFormat, TextureFormatNames)
	ENUM_VALUE_FEATURES(TextureFormatType, TextureFormatTypeNames)
	ENUM_VALUE_FEATURES(PixelDataType, PixelDataTypeNames)
	ENUM_MASK_FEATURES(TextureFeature, TextureFeatureNames)

	/// @brief Texture format info.
	struct TextureFormatInfo final
	{
		std::uint32_t blockSize; ///< Block size in bytes. For uncompressed formats it's a pixel size.
		std::uint32_t blockWidth; ///< Block width in pixels. For uncompressed formats it's always 1.
		std::uint32_t blockHeight; ///< Block height in pixels. For uncompressed formats it's always 1.
		std::uint32_t blockDepth; ///< Block depth in pixels. For uncompressed formats it's always 1.
		TextureDimensionMask supportedDimensions; ///< Supported dimensions. It's a dimension mask.
		TextureFormatType textureFormatType; ///< Texture format type.
		PixelDataType pixelDataType; ///< Pixel data type. For depth stencil formats it's unknown.
		TextureFeature features; ///< Texture format features.
		bool compressed; ///< Is it a compressed format?
		bool supportedByPlatform; ///< Is the format supported by a current platform?
	};
}
