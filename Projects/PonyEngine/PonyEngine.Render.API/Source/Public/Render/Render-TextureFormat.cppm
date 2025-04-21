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
		R8G8B8A8_Unorm_SRGB,
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
		BC1_Unorm_SRGB,
		BC2_Unorm,
		BC2_Unorm_SRGB,
		BC3_Unorm,
		BC3_Unorm_SRGB,
		BC4_Unorm,
		BC4_Snorm,
		BC5_Unorm,
		BC5_Snorm,
		B5G6R5_Unorm,
		B5G5R5A1_Unorm,
		B8G8R8A8_Unorm,
		B8G8R8X8_Unorm,
		B8G8R8A8_Unorm_SRGB,
		B8G8R8X8_Unorm_SRGB,
		BC6H_UF16,
		BC6H_SF16,
		BC7_Unorm,
		BC7_Unorm_SRGB,
		B4G4R4A4_Unorm
	};
}
