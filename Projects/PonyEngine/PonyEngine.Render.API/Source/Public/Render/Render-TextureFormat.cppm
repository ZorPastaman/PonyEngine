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
import <unordered_map>;

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

	/// @brief Gets the size of a buffer by the texture format.
	/// @param size Buffer size in pixel count.
	/// @param format Texture format.
	/// @return Buffer size in bytes.
	[[nodiscard("Pure function")]]
	std::uint32_t TextureFormatSize(std::uint32_t size, TextureFormat format) noexcept;
}

namespace PonyEngine::Render
{
	/// @brief Format multipliers. A pixel count is multiplied by this to get a buffer size in bytes.
	const std::unordered_map<TextureFormat, std::uint32_t> FormatMultipliers
	{
		{ TextureFormat::R32G32B32A32_Float, 16 },
		{ TextureFormat::R32G32B32A32_Uint, 16 },
		{ TextureFormat::R32G32B32A32_Sint, 16 },
		{ TextureFormat::R32G32B32_Float, 12 },
		{ TextureFormat::R32G32B32_Uint, 12 },
		{ TextureFormat::R32G32B32_Sint, 12 },
		{ TextureFormat::R16G16B16A16_Float, 8 },
		{ TextureFormat::R16G16B16A16_Unorm, 8 },
		{ TextureFormat::R16G16B16A16_Uint, 8 },
		{ TextureFormat::R16G16B16A16_Snorm, 8 },
		{ TextureFormat::R16G16B16A16_Sint, 8 },
		{ TextureFormat::R32G32_Float, 8 },
		{ TextureFormat::R32G32_Uint, 8 },
		{ TextureFormat::R32G32_Sint, 8 },
		{ TextureFormat::D32_Float_S8X24_Uint, 8 },
		{ TextureFormat::R10G10B10A2_Unorm, 4 },
		{ TextureFormat::R10G10B10A2_Uint, 4 },
		{ TextureFormat::R11G11B10_Float, 4 },
		{ TextureFormat::R8G8B8A8_Unorm, 4 },
		{ TextureFormat::R8G8B8A8_Unorm_SRGB, 4 },
		{ TextureFormat::R8G8B8A8_Uint, 4 },
		{ TextureFormat::R8G8B8A8_Snorm, 4 },
		{ TextureFormat::R8G8B8A8_Sint, 4 },
		{ TextureFormat::R16G16_Float, 4 },
		{ TextureFormat::R16G16_Unorm, 4 },
		{ TextureFormat::R16G16_Uint, 4 },
		{ TextureFormat::R16G16_Snorm, 4 },
		{ TextureFormat::R16G16_Sint, 4 },
		{ TextureFormat::D32_Float, 4 },
		{ TextureFormat::R32_Float, 4 },
		{ TextureFormat::R32_Uint, 4 },
		{ TextureFormat::R32_Sint, 4 },
		{ TextureFormat::D24_Unorm_S8_Uint, 4 },
		{ TextureFormat::R8G8_Unorm, 2 },
		{ TextureFormat::R8G8_Uint, 2 },
		{ TextureFormat::R8G8_Snorm, 2 },
		{ TextureFormat::R8G8_Sint, 2 },
		{ TextureFormat::R16_Float, 2 },
		{ TextureFormat::D16_Unorm, 2 },
		{ TextureFormat::R16_Unorm, 2 },
		{ TextureFormat::R16_Uint, 2 },
		{ TextureFormat::R16_Snorm, 2 },
		{ TextureFormat::R16_Sint, 2 },
		{ TextureFormat::B5G6R5_Unorm, 2 },
		{ TextureFormat::B5G5R5A1_Unorm, 2 },
		{ TextureFormat::B8G8R8A8_Unorm, 4 },
		{ TextureFormat::B8G8R8X8_Unorm, 4 },
		{ TextureFormat::B8G8R8A8_Unorm_SRGB, 4 },
		{ TextureFormat::B8G8R8X8_Unorm_SRGB, 4 },
		{ TextureFormat::B4G4R4A4_Unorm, 2 }
	};

	/// @brief Format divisors. A pixel count is divided by this to get a buffer size in bytes.
	const std::unordered_map<TextureFormat, std::uint32_t> FormatDivisors
	{
		{ TextureFormat::BC1_Unorm, 2 },
		{ TextureFormat::BC1_Unorm_SRGB, 2 },
		{ TextureFormat::BC4_Unorm, 2 },
		{ TextureFormat::BC4_Snorm, 2 }
	};

	std::uint32_t TextureFormatSize(std::uint32_t size, const TextureFormat format) noexcept
	{
		if (const auto position = FormatMultipliers.find(format); position != FormatMultipliers.cend())
		{
			size *= position->second;
		}

		if (const auto position = FormatDivisors.find(format); position != FormatDivisors.cend())
		{
			size /= position->second;
		}

		return size;
	}
}
