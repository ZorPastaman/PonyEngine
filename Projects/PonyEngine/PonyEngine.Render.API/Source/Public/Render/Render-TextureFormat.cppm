/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.Render:TextureFormat;

import <cstdint>;
import <type_traits>;

import :TextureDimension;

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

	/// @brief Texture format info.
	struct TextureFormatInfo final
	{
		std::uint32_t blockSize; ///< Block size in bytes. For uncompressed formats it's a pixel size.
		std::uint32_t blockWidth; ///< Block width in pixels. For uncompressed formats it's always 1.
		std::uint32_t blockHeight; ///< Block height in pixels. For uncompressed formats it's always 1.
		std::uint32_t blockDepth; ///< Block depth in pixels. For uncompressed formats it's always 1.
		std::underlying_type_t<TextureDimension> supportedDimensions; ///< Supported dimensions.
		TextureFormatType textureFormatType; ///< Texture format type.
		PixelDataType pixelDataType; ///< Pixel data type. For depth stencil formats it's unknown.
		bool isCompressed; ///< Is it a compressed format?
		bool pixelAccessible; ///< Is it possible to read/write individual pixels? Usually uncompressed formats have @a true, and compressed ones have @a false.
		bool supportedByPlatform; /// < Does the current platform supports the format? If it's false, all other fields will be default.
	};
}
