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

#include "PonyBase/Core/Direct3D12/Framework.h"

export module PonyEngine.Render.Direct3D12.Detail:FormatUtility;

import <algorithm>;
import <array>;
import <unordered_map>;
import <utility>;

import PonyEngine.Render;

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief Gets a Direct3D12 format by the texture format.
	/// @param format Texture format.
	/// @return Direct3D12 format.
	[[nodiscard("Pure function")]]
	DXGI_FORMAT GetD3D12Format(TextureFormat format) noexcept;

	/// @brief Gets an SRGB version of the @p sourceFormat.
	/// @param sourceFormat Source format.
	/// @return SRGB format.
	[[nodiscard("Pure function")]]
	constexpr DXGI_FORMAT GetSrgbFormat(DXGI_FORMAT sourceFormat) noexcept;
	/// @brief Gets a usual format of the @p sourceFormat.
	/// @param sourceFormat SRGB format.
	/// @return Usual format.
	[[nodiscard("Pure function")]]
	constexpr DXGI_FORMAT GetUsualFormat(DXGI_FORMAT sourceFormat) noexcept;
}

namespace PonyEngine::Render::Direct3D12
{
	/// @brief Texture format to dxgi format map.
	static const std::unordered_map<TextureFormat, DXGI_FORMAT> TextureFormatDxgiFormatMap
	{
		{ TextureFormat::Unknown, DXGI_FORMAT_UNKNOWN },
		{ TextureFormat::R32G32B32A32_Float, DXGI_FORMAT_R32G32B32A32_FLOAT },
		{ TextureFormat::R32G32B32A32_Uint, DXGI_FORMAT_R32G32B32A32_UINT },
		{ TextureFormat::R32G32B32A32_Sint, DXGI_FORMAT_R32G32B32A32_SINT },
		{ TextureFormat::R32G32B32_Float, DXGI_FORMAT_R32G32B32_FLOAT },
		{ TextureFormat::R32G32B32_Uint, DXGI_FORMAT_R32G32B32_UINT },
		{ TextureFormat::R32G32B32_Sint, DXGI_FORMAT_R32G32B32_SINT },
		{ TextureFormat::R16G16B16A16_Float, DXGI_FORMAT_R16G16B16A16_FLOAT },
		{ TextureFormat::R16G16B16A16_Unorm, DXGI_FORMAT_R16G16B16A16_UNORM },
		{ TextureFormat::R16G16B16A16_Uint, DXGI_FORMAT_R16G16B16A16_UINT },
		{ TextureFormat::R16G16B16A16_Snorm, DXGI_FORMAT_R16G16B16A16_SNORM },
		{ TextureFormat::R16G16B16A16_Sint, DXGI_FORMAT_R16G16B16A16_SINT },
		{ TextureFormat::R32G32_Float, DXGI_FORMAT_R32G32_FLOAT },
		{ TextureFormat::R32G32_Uint, DXGI_FORMAT_R32G32_UINT },
		{ TextureFormat::R32G32_Sint, DXGI_FORMAT_R32G32_SINT },
		{ TextureFormat::D32_Float_S8X24_Uint, DXGI_FORMAT_D32_FLOAT_S8X24_UINT },
		{ TextureFormat::R10G10B10A2_Unorm, DXGI_FORMAT_R10G10B10A2_UNORM },
		{ TextureFormat::R10G10B10A2_Uint, DXGI_FORMAT_R10G10B10A2_UINT },
		{ TextureFormat::R11G11B10_Float, DXGI_FORMAT_R11G11B10_FLOAT },
		{ TextureFormat::R8G8B8A8_Unorm, DXGI_FORMAT_R8G8B8A8_UNORM },
		{ TextureFormat::R8G8B8A8_Unorm_SRGB, DXGI_FORMAT_R8G8B8A8_UNORM_SRGB },
		{ TextureFormat::R8G8B8A8_Uint, DXGI_FORMAT_R8G8B8A8_UINT },
		{ TextureFormat::R8G8B8A8_Snorm, DXGI_FORMAT_R8G8B8A8_SNORM },
		{ TextureFormat::R8G8B8A8_Sint, DXGI_FORMAT_R8G8B8A8_SINT },
		{ TextureFormat::R16G16_Float, DXGI_FORMAT_R16G16_FLOAT },
		{ TextureFormat::R16G16_Unorm, DXGI_FORMAT_R16G16_UNORM },
		{ TextureFormat::R16G16_Uint, DXGI_FORMAT_R16G16_UINT },
		{ TextureFormat::R16G16_Snorm, DXGI_FORMAT_R16G16_SNORM },
		{ TextureFormat::R16G16_Sint, DXGI_FORMAT_R16G16_SINT },
		{ TextureFormat::D32_Float, DXGI_FORMAT_D32_FLOAT },
		{ TextureFormat::R32_Float, DXGI_FORMAT_R32_FLOAT },
		{ TextureFormat::R32_Uint, DXGI_FORMAT_R32_UINT },
		{ TextureFormat::R32_Sint, DXGI_FORMAT_R32_SINT },
		{ TextureFormat::D24_Unorm_S8_Uint, DXGI_FORMAT_D24_UNORM_S8_UINT },
		{ TextureFormat::R8G8_Unorm, DXGI_FORMAT_R8G8_UNORM },
		{ TextureFormat::R8G8_Uint, DXGI_FORMAT_R8G8_UINT },
		{ TextureFormat::R8G8_Snorm, DXGI_FORMAT_R8G8_SNORM },
		{ TextureFormat::R8G8_Sint, DXGI_FORMAT_R8G8_SINT },
		{ TextureFormat::R16_Float, DXGI_FORMAT_R16_FLOAT },
		{ TextureFormat::D16_Unorm, DXGI_FORMAT_D16_UNORM },
		{ TextureFormat::R16_Unorm, DXGI_FORMAT_R16_UNORM },
		{ TextureFormat::R16_Uint, DXGI_FORMAT_R16_UINT },
		{ TextureFormat::R16_Snorm, DXGI_FORMAT_R16_SNORM },
		{ TextureFormat::R16_Sint, DXGI_FORMAT_R16_SINT },
		{ TextureFormat::R8_Unorm, DXGI_FORMAT_R8_UNORM },
		{ TextureFormat::R8_Uint, DXGI_FORMAT_R8_UINT },
		{ TextureFormat::R8_Snorm, DXGI_FORMAT_R8_SNORM },
		{ TextureFormat::R8_Sint, DXGI_FORMAT_R8_SINT },
		{ TextureFormat::A8_Unorm, DXGI_FORMAT_A8_UNORM },
		{ TextureFormat::R1_Unorm, DXGI_FORMAT_R1_UNORM },
		{ TextureFormat::BC1_Unorm, DXGI_FORMAT_BC1_UNORM },
		{ TextureFormat::BC1_Unorm_SRGB, DXGI_FORMAT_BC1_UNORM_SRGB },
		{ TextureFormat::BC2_Unorm, DXGI_FORMAT_BC2_UNORM },
		{ TextureFormat::BC2_Unorm_SRGB, DXGI_FORMAT_BC2_UNORM_SRGB },
		{ TextureFormat::BC3_Unorm, DXGI_FORMAT_BC3_UNORM },
		{ TextureFormat::BC3_Unorm_SRGB, DXGI_FORMAT_BC3_UNORM_SRGB },
		{ TextureFormat::BC4_Unorm, DXGI_FORMAT_BC4_UNORM },
		{ TextureFormat::BC4_Snorm, DXGI_FORMAT_BC4_SNORM },
		{ TextureFormat::BC5_Unorm, DXGI_FORMAT_BC5_UNORM },
		{ TextureFormat::BC5_Snorm, DXGI_FORMAT_BC5_SNORM },
		{ TextureFormat::B5G6R5_Unorm, DXGI_FORMAT_B5G6R5_UNORM },
		{ TextureFormat::B5G5R5A1_Unorm, DXGI_FORMAT_B5G5R5A1_UNORM },
		{ TextureFormat::B8G8R8A8_Unorm, DXGI_FORMAT_B8G8R8A8_UNORM },
		{ TextureFormat::B8G8R8X8_Unorm, DXGI_FORMAT_B8G8R8X8_UNORM },
		{ TextureFormat::B8G8R8A8_Unorm_SRGB, DXGI_FORMAT_B8G8R8A8_UNORM_SRGB },
		{ TextureFormat::B8G8R8X8_Unorm_SRGB, DXGI_FORMAT_B8G8R8X8_UNORM_SRGB },
		{ TextureFormat::BC6H_UF16, DXGI_FORMAT_BC6H_UF16 },
		{ TextureFormat::BC6H_SF16, DXGI_FORMAT_BC6H_SF16 },
		{ TextureFormat::BC7_Unorm, DXGI_FORMAT_BC7_UNORM },
		{ TextureFormat::BC7_Unorm_SRGB, DXGI_FORMAT_BC7_UNORM_SRGB },
		{ TextureFormat::B4G4R4A4_Unorm, DXGI_FORMAT_B4G4R4A4_UNORM }
	};

	/// @brief Non-SRGB and SRGB format pairs.
	constexpr std::array SrgbFormats
	{
		std::pair(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_FORMAT_R8G8B8A8_UNORM_SRGB),
		std::pair(DXGI_FORMAT_BC1_UNORM, DXGI_FORMAT_BC1_UNORM_SRGB),
		std::pair(DXGI_FORMAT_BC2_UNORM, DXGI_FORMAT_BC2_UNORM_SRGB),
		std::pair(DXGI_FORMAT_BC3_UNORM, DXGI_FORMAT_BC3_UNORM_SRGB),
		std::pair(DXGI_FORMAT_BC7_UNORM, DXGI_FORMAT_BC7_UNORM_SRGB),
		std::pair(DXGI_FORMAT_B8G8R8A8_UNORM, DXGI_FORMAT_B8G8R8A8_UNORM_SRGB),
		std::pair(DXGI_FORMAT_B8G8R8X8_UNORM, DXGI_FORMAT_B8G8R8X8_UNORM_SRGB)
	};

	DXGI_FORMAT GetD3D12Format(const TextureFormat format) noexcept
	{
		if (const auto position = TextureFormatDxgiFormatMap.find(format); position != TextureFormatDxgiFormatMap.cend())
		{
			return position->second;
		}

		assert(false && "Incorrect texture format.");

		return DXGI_FORMAT_UNKNOWN;
	}

	constexpr DXGI_FORMAT GetSrgbFormat(const DXGI_FORMAT sourceFormat) noexcept
	{
		if (const auto position = std::ranges::find_if(SrgbFormats, [&](const std::pair<DXGI_FORMAT, DXGI_FORMAT>& p) { return p.first == sourceFormat; }); position != SrgbFormats.cend()) [[likely]]
		{
			return position->second;
		}

		assert(false && "Incorrect source format.");

		return DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	}

	constexpr DXGI_FORMAT GetUsualFormat(const DXGI_FORMAT sourceFormat) noexcept
	{
		if (const auto position = std::ranges::find_if(SrgbFormats, [&](const std::pair<DXGI_FORMAT, DXGI_FORMAT>& p) { return p.second == sourceFormat; }); position != SrgbFormats.cend()) [[likely]]
		{
			return position->first;
		}

		assert(false && "Incorrect source format.");

		return DXGI_FORMAT_R8G8B8A8_UNORM;
	}
}
