/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/RenderDevice/Windows/D3D12Framework.h"

export module PonyEngine.RenderDevice.Direct3D12.Impl.Windows:FormatUtility;

import std;

import PonyEngine.RenderDevice;

export namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	/// @brief Format info.
	struct FormatInfo final
	{
		std::string_view engineFormat; ///< Engine format.
		DXGI_FORMAT format; ///< Native format.
		DXGI_FORMAT typelessFormat; ///< Typeless format in the same group. The same native format if there's only one format in a group.
		DXGI_FORMAT srgbFormat; ///< SRGB format variant. UNKNOWN if there's no SRGB variant.
		DXGI_FORMAT depthViewFormat; ///< Depth view format. UNKNOWN if the native format is not a depth format.
		DXGI_FORMAT stencilViewFormat; ///< Stencil view format. UNKNOWN if the native format doesn't have a stencil aspect.
	};

	/// @brief Format infos.
	constexpr std::array<FormatInfo, 62> FormatInfos
	{
		FormatInfo
		{
			.engineFormat = TextureFormat::R32G32B32A32_Float,
			.format = DXGI_FORMAT_R32G32B32A32_FLOAT,
			.typelessFormat = DXGI_FORMAT_R32G32B32A32_TYPELESS,
			.srgbFormat = DXGI_FORMAT_UNKNOWN,
			.depthViewFormat = DXGI_FORMAT_UNKNOWN,
			.stencilViewFormat = DXGI_FORMAT_UNKNOWN
		},
		FormatInfo
		{
			.engineFormat = TextureFormat::R32G32B32A32_Uint,
			.format = DXGI_FORMAT_R32G32B32A32_UINT,
			.typelessFormat = DXGI_FORMAT_R32G32B32A32_TYPELESS,
			.srgbFormat = DXGI_FORMAT_UNKNOWN,
			.depthViewFormat = DXGI_FORMAT_UNKNOWN,
			.stencilViewFormat = DXGI_FORMAT_UNKNOWN
		},
		FormatInfo
		{
			.engineFormat = TextureFormat::R32G32B32A32_Sint,
			.format = DXGI_FORMAT_R32G32B32A32_SINT,
			.typelessFormat = DXGI_FORMAT_R32G32B32A32_TYPELESS,
			.srgbFormat = DXGI_FORMAT_UNKNOWN,
			.depthViewFormat = DXGI_FORMAT_UNKNOWN,
			.stencilViewFormat = DXGI_FORMAT_UNKNOWN
		},
		FormatInfo
		{
			.engineFormat = TextureFormat::R32G32B32_Float,
			.format = DXGI_FORMAT_R32G32B32_FLOAT,
			.typelessFormat = DXGI_FORMAT_R32G32B32_TYPELESS,
			.srgbFormat = DXGI_FORMAT_UNKNOWN,
			.depthViewFormat = DXGI_FORMAT_UNKNOWN,
			.stencilViewFormat = DXGI_FORMAT_UNKNOWN
		},
		FormatInfo
		{
			.engineFormat = TextureFormat::R32G32B32_Uint,
			.format = DXGI_FORMAT_R32G32B32_UINT,
			.typelessFormat = DXGI_FORMAT_R32G32B32_TYPELESS,
			.srgbFormat = DXGI_FORMAT_UNKNOWN,
			.depthViewFormat = DXGI_FORMAT_UNKNOWN,
			.stencilViewFormat = DXGI_FORMAT_UNKNOWN
		},
		FormatInfo
		{
			.engineFormat = TextureFormat::R32G32B32_Sint,
			.format = DXGI_FORMAT_R32G32B32_SINT,
			.typelessFormat = DXGI_FORMAT_R32G32B32_TYPELESS,
			.srgbFormat = DXGI_FORMAT_UNKNOWN,
			.depthViewFormat = DXGI_FORMAT_UNKNOWN,
			.stencilViewFormat = DXGI_FORMAT_UNKNOWN
		},
		FormatInfo
		{
			.engineFormat = TextureFormat::R32G32_Float,
			.format = DXGI_FORMAT_R32G32_FLOAT,
			.typelessFormat = DXGI_FORMAT_R32G32_TYPELESS,
			.srgbFormat = DXGI_FORMAT_UNKNOWN,
			.depthViewFormat = DXGI_FORMAT_UNKNOWN,
			.stencilViewFormat = DXGI_FORMAT_UNKNOWN
		},
		FormatInfo
		{
			.engineFormat = TextureFormat::R32G32_Uint,
			.format = DXGI_FORMAT_R32G32_UINT,
			.typelessFormat = DXGI_FORMAT_R32G32_TYPELESS,
			.srgbFormat = DXGI_FORMAT_UNKNOWN,
			.depthViewFormat = DXGI_FORMAT_UNKNOWN,
			.stencilViewFormat = DXGI_FORMAT_UNKNOWN
		},
		FormatInfo
		{
			.engineFormat = TextureFormat::R32G32_Sint,
			.format = DXGI_FORMAT_R32G32_SINT,
			.typelessFormat = DXGI_FORMAT_R32G32_TYPELESS,
			.srgbFormat = DXGI_FORMAT_UNKNOWN,
			.depthViewFormat = DXGI_FORMAT_UNKNOWN,
			.stencilViewFormat = DXGI_FORMAT_UNKNOWN
		},
		FormatInfo
		{
			.engineFormat = TextureFormat::D32_Float_S8X24_Uint,
			.format = DXGI_FORMAT_D32_FLOAT_S8X24_UINT,
			.typelessFormat = DXGI_FORMAT_R32G8X24_TYPELESS,
			.srgbFormat = DXGI_FORMAT_UNKNOWN,
			.depthViewFormat = DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS,
			.stencilViewFormat = DXGI_FORMAT_X32_TYPELESS_G8X24_UINT
		},
		FormatInfo
		{
			.engineFormat = TextureFormat::D32_Float,
			.format = DXGI_FORMAT_D32_FLOAT,
			.typelessFormat = DXGI_FORMAT_R32_TYPELESS,
			.srgbFormat = DXGI_FORMAT_UNKNOWN,
			.depthViewFormat = DXGI_FORMAT_R32_FLOAT,
			.stencilViewFormat = DXGI_FORMAT_UNKNOWN
		},
		FormatInfo
		{
			.engineFormat = TextureFormat::R32_Float,
			.format = DXGI_FORMAT_R32_FLOAT,
			.typelessFormat = DXGI_FORMAT_R32_TYPELESS,
			.srgbFormat = DXGI_FORMAT_UNKNOWN,
			.depthViewFormat = DXGI_FORMAT_UNKNOWN,
			.stencilViewFormat = DXGI_FORMAT_UNKNOWN
		},
		FormatInfo
		{
			.engineFormat = TextureFormat::R32_Uint,
			.format = DXGI_FORMAT_R32_UINT,
			.typelessFormat = DXGI_FORMAT_R32_TYPELESS,
			.srgbFormat = DXGI_FORMAT_UNKNOWN,
			.depthViewFormat = DXGI_FORMAT_UNKNOWN,
			.stencilViewFormat = DXGI_FORMAT_UNKNOWN
		},
		FormatInfo
		{
			.engineFormat = TextureFormat::R32_Sint,
			.format = DXGI_FORMAT_R32_SINT,
			.typelessFormat = DXGI_FORMAT_R32_TYPELESS,
			.srgbFormat = DXGI_FORMAT_UNKNOWN,
			.depthViewFormat = DXGI_FORMAT_UNKNOWN,
			.stencilViewFormat = DXGI_FORMAT_UNKNOWN
		},
		FormatInfo
		{
			.engineFormat = TextureFormat::D24_Unorm_S8_Uint,
			.format = DXGI_FORMAT_D24_UNORM_S8_UINT,
			.typelessFormat = DXGI_FORMAT_R24G8_TYPELESS,
			.srgbFormat = DXGI_FORMAT_UNKNOWN,
			.depthViewFormat = DXGI_FORMAT_R24_UNORM_X8_TYPELESS,
			.stencilViewFormat = DXGI_FORMAT_X24_TYPELESS_G8_UINT
		},
		FormatInfo
		{
			.engineFormat = TextureFormat::R16G16B16A16_Float,
			.format = DXGI_FORMAT_R16G16B16A16_FLOAT,
			.typelessFormat = DXGI_FORMAT_R16G16B16A16_TYPELESS,
			.srgbFormat = DXGI_FORMAT_UNKNOWN,
			.depthViewFormat = DXGI_FORMAT_UNKNOWN,
			.stencilViewFormat = DXGI_FORMAT_UNKNOWN
		},
		FormatInfo
		{
			.engineFormat = TextureFormat::R16G16B16A16_Unorm,
			.format = DXGI_FORMAT_R16G16B16A16_UNORM,
			.typelessFormat = DXGI_FORMAT_R16G16B16A16_TYPELESS,
			.srgbFormat = DXGI_FORMAT_UNKNOWN,
			.depthViewFormat = DXGI_FORMAT_UNKNOWN,
			.stencilViewFormat = DXGI_FORMAT_UNKNOWN
		},
		FormatInfo
		{
			.engineFormat = TextureFormat::R16G16B16A16_Uint,
			.format = DXGI_FORMAT_R16G16B16A16_UINT,
			.typelessFormat = DXGI_FORMAT_R16G16B16A16_TYPELESS,
			.srgbFormat = DXGI_FORMAT_UNKNOWN,
			.depthViewFormat = DXGI_FORMAT_UNKNOWN,
			.stencilViewFormat = DXGI_FORMAT_UNKNOWN
		},
		FormatInfo
		{
			.engineFormat = TextureFormat::R16G16B16A16_Snorm,
			.format = DXGI_FORMAT_R16G16B16A16_SNORM,
			.typelessFormat = DXGI_FORMAT_R16G16B16A16_TYPELESS,
			.srgbFormat = DXGI_FORMAT_UNKNOWN,
			.depthViewFormat = DXGI_FORMAT_UNKNOWN,
			.stencilViewFormat = DXGI_FORMAT_UNKNOWN
		},
		FormatInfo
		{
			.engineFormat = TextureFormat::R16G16B16A16_Sint,
			.format = DXGI_FORMAT_R16G16B16A16_SINT,
			.typelessFormat = DXGI_FORMAT_R16G16B16A16_TYPELESS,
			.srgbFormat = DXGI_FORMAT_UNKNOWN,
			.depthViewFormat = DXGI_FORMAT_UNKNOWN,
			.stencilViewFormat = DXGI_FORMAT_UNKNOWN
		},
		FormatInfo
		{
			.engineFormat = TextureFormat::R16G16_Float,
			.format = DXGI_FORMAT_R16G16_FLOAT,
			.typelessFormat = DXGI_FORMAT_R16G16_TYPELESS,
			.srgbFormat = DXGI_FORMAT_UNKNOWN,
			.depthViewFormat = DXGI_FORMAT_UNKNOWN,
			.stencilViewFormat = DXGI_FORMAT_UNKNOWN
		},
		FormatInfo
		{
			.engineFormat = TextureFormat::R16G16_Unorm,
			.format = DXGI_FORMAT_R16G16_UNORM,
			.typelessFormat = DXGI_FORMAT_R16G16_TYPELESS,
			.srgbFormat = DXGI_FORMAT_UNKNOWN,
			.depthViewFormat = DXGI_FORMAT_UNKNOWN,
			.stencilViewFormat = DXGI_FORMAT_UNKNOWN
		},
		FormatInfo
		{
			.engineFormat = TextureFormat::R16G16_Uint,
			.format = DXGI_FORMAT_R16G16_UINT,
			.typelessFormat = DXGI_FORMAT_R16G16_TYPELESS,
			.srgbFormat = DXGI_FORMAT_UNKNOWN,
			.depthViewFormat = DXGI_FORMAT_UNKNOWN,
			.stencilViewFormat = DXGI_FORMAT_UNKNOWN
		},
		FormatInfo
		{
			.engineFormat = TextureFormat::R16G16_Snorm,
			.format = DXGI_FORMAT_R16G16_SNORM,
			.typelessFormat = DXGI_FORMAT_R16G16_TYPELESS,
			.srgbFormat = DXGI_FORMAT_UNKNOWN,
			.depthViewFormat = DXGI_FORMAT_UNKNOWN,
			.stencilViewFormat = DXGI_FORMAT_UNKNOWN
		},
		FormatInfo
		{
			.engineFormat = TextureFormat::R16G16_Sint,
			.format = DXGI_FORMAT_R16G16_SINT,
			.typelessFormat = DXGI_FORMAT_R16G16_TYPELESS,
			.srgbFormat = DXGI_FORMAT_UNKNOWN,
			.depthViewFormat = DXGI_FORMAT_UNKNOWN,
			.stencilViewFormat = DXGI_FORMAT_UNKNOWN
		},
		FormatInfo
		{
			.engineFormat = TextureFormat::D16_Unorm,
			.format = DXGI_FORMAT_D16_UNORM,
			.typelessFormat = DXGI_FORMAT_R16_TYPELESS,
			.srgbFormat = DXGI_FORMAT_UNKNOWN,
			.depthViewFormat = DXGI_FORMAT_R16_UNORM,
			.stencilViewFormat = DXGI_FORMAT_UNKNOWN
		},
		FormatInfo
		{
			.engineFormat = TextureFormat::R16_Float,
			.format = DXGI_FORMAT_R16_FLOAT,
			.typelessFormat = DXGI_FORMAT_R16_TYPELESS,
			.srgbFormat = DXGI_FORMAT_UNKNOWN,
			.depthViewFormat = DXGI_FORMAT_UNKNOWN,
			.stencilViewFormat = DXGI_FORMAT_UNKNOWN
		},
		FormatInfo
		{
			.engineFormat = TextureFormat::R16_Unorm,
			.format = DXGI_FORMAT_R16_UNORM,
			.typelessFormat = DXGI_FORMAT_R16_TYPELESS,
			.srgbFormat = DXGI_FORMAT_UNKNOWN,
			.depthViewFormat = DXGI_FORMAT_UNKNOWN,
			.stencilViewFormat = DXGI_FORMAT_UNKNOWN
		},
		FormatInfo
		{
			.engineFormat = TextureFormat::R16_Uint,
			.format = DXGI_FORMAT_R16_UINT,
			.typelessFormat = DXGI_FORMAT_R16_TYPELESS,
			.srgbFormat = DXGI_FORMAT_UNKNOWN,
			.depthViewFormat = DXGI_FORMAT_UNKNOWN,
			.stencilViewFormat = DXGI_FORMAT_UNKNOWN
		},
		FormatInfo
		{
			.engineFormat = TextureFormat::R16_Snorm,
			.format = DXGI_FORMAT_R16_SNORM,
			.typelessFormat = DXGI_FORMAT_R16_TYPELESS,
			.srgbFormat = DXGI_FORMAT_UNKNOWN,
			.depthViewFormat = DXGI_FORMAT_UNKNOWN,
			.stencilViewFormat = DXGI_FORMAT_UNKNOWN
		},
		FormatInfo
		{
			.engineFormat = TextureFormat::R16_Sint,
			.format = DXGI_FORMAT_R16_SINT,
			.typelessFormat = DXGI_FORMAT_R16_TYPELESS,
			.srgbFormat = DXGI_FORMAT_UNKNOWN,
			.depthViewFormat = DXGI_FORMAT_UNKNOWN,
			.stencilViewFormat = DXGI_FORMAT_UNKNOWN
		},
		FormatInfo
		{
			.engineFormat = TextureFormat::R11G11B10_Float,
			.format = DXGI_FORMAT_R11G11B10_FLOAT,
			.typelessFormat = DXGI_FORMAT_R11G11B10_FLOAT,
			.srgbFormat = DXGI_FORMAT_UNKNOWN,
			.depthViewFormat = DXGI_FORMAT_UNKNOWN,
			.stencilViewFormat = DXGI_FORMAT_UNKNOWN
		},
		FormatInfo
		{
			.engineFormat = TextureFormat::R10G10B10A2_Unorm,
			.format = DXGI_FORMAT_R10G10B10A2_UNORM,
			.typelessFormat = DXGI_FORMAT_R10G10B10A2_TYPELESS,
			.srgbFormat = DXGI_FORMAT_UNKNOWN,
			.depthViewFormat = DXGI_FORMAT_UNKNOWN,
			.stencilViewFormat = DXGI_FORMAT_UNKNOWN,
		},
		FormatInfo
		{
			.engineFormat = TextureFormat::R10G10B10A2_Uint,
			.format = DXGI_FORMAT_R10G10B10A2_UINT,
			.typelessFormat = DXGI_FORMAT_R10G10B10A2_TYPELESS,
			.srgbFormat = DXGI_FORMAT_UNKNOWN,
			.depthViewFormat = DXGI_FORMAT_UNKNOWN,
			.stencilViewFormat = DXGI_FORMAT_UNKNOWN,
		},
		FormatInfo
		{
			.engineFormat = TextureFormat::R9G9B9E5_SharedExp,
			.format = DXGI_FORMAT_R9G9B9E5_SHAREDEXP,
			.typelessFormat = DXGI_FORMAT_R9G9B9E5_SHAREDEXP,
			.srgbFormat = DXGI_FORMAT_UNKNOWN,
			.depthViewFormat = DXGI_FORMAT_UNKNOWN,
			.stencilViewFormat = DXGI_FORMAT_UNKNOWN,
		},
		FormatInfo
		{
			.engineFormat = TextureFormat::R8G8B8A8_Unorm,
			.format = DXGI_FORMAT_R8G8B8A8_UNORM,
			.typelessFormat = DXGI_FORMAT_R8G8B8A8_TYPELESS,
			.srgbFormat = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB,
			.depthViewFormat = DXGI_FORMAT_UNKNOWN,
			.stencilViewFormat = DXGI_FORMAT_UNKNOWN
		},
		FormatInfo
		{
			.engineFormat = TextureFormat::R8G8B8A8_Uint,
			.format = DXGI_FORMAT_R8G8B8A8_UINT,
			.typelessFormat = DXGI_FORMAT_R8G8B8A8_TYPELESS,
			.srgbFormat = DXGI_FORMAT_UNKNOWN,
			.depthViewFormat = DXGI_FORMAT_UNKNOWN,
			.stencilViewFormat = DXGI_FORMAT_UNKNOWN
		},
		FormatInfo
		{
			.engineFormat = TextureFormat::R8G8B8A8_Snorm,
			.format = DXGI_FORMAT_R8G8B8A8_SNORM,
			.typelessFormat = DXGI_FORMAT_R8G8B8A8_TYPELESS,
			.srgbFormat = DXGI_FORMAT_UNKNOWN,
			.depthViewFormat = DXGI_FORMAT_UNKNOWN,
			.stencilViewFormat = DXGI_FORMAT_UNKNOWN
		},
		FormatInfo
		{
			.engineFormat = TextureFormat::R8G8B8A8_Sint,
			.format = DXGI_FORMAT_R8G8B8A8_SINT,
			.typelessFormat = DXGI_FORMAT_R8G8B8A8_TYPELESS,
			.srgbFormat = DXGI_FORMAT_UNKNOWN,
			.depthViewFormat = DXGI_FORMAT_UNKNOWN,
			.stencilViewFormat = DXGI_FORMAT_UNKNOWN
		},
		FormatInfo
		{
			.engineFormat = TextureFormat::R8G8_Unorm,
			.format = DXGI_FORMAT_R8G8_UNORM,
			.typelessFormat = DXGI_FORMAT_R8G8_TYPELESS,
			.srgbFormat = DXGI_FORMAT_UNKNOWN,
			.depthViewFormat = DXGI_FORMAT_UNKNOWN,
			.stencilViewFormat = DXGI_FORMAT_UNKNOWN
		},
		FormatInfo
		{
			.engineFormat = TextureFormat::R8G8_Uint,
			.format = DXGI_FORMAT_R8G8_UINT,
			.typelessFormat = DXGI_FORMAT_R8G8_TYPELESS,
			.srgbFormat = DXGI_FORMAT_UNKNOWN,
			.depthViewFormat = DXGI_FORMAT_UNKNOWN,
			.stencilViewFormat = DXGI_FORMAT_UNKNOWN
		},
		FormatInfo
		{
			.engineFormat = TextureFormat::R8G8_Snorm,
			.format = DXGI_FORMAT_R8G8_SNORM,
			.typelessFormat = DXGI_FORMAT_R8G8_TYPELESS,
			.srgbFormat = DXGI_FORMAT_UNKNOWN,
			.depthViewFormat = DXGI_FORMAT_UNKNOWN,
			.stencilViewFormat = DXGI_FORMAT_UNKNOWN
		},
		FormatInfo
		{
			.engineFormat = TextureFormat::R8G8_Sint,
			.format = DXGI_FORMAT_R8G8_SINT,
			.typelessFormat = DXGI_FORMAT_R8G8_TYPELESS,
			.srgbFormat = DXGI_FORMAT_UNKNOWN,
			.depthViewFormat = DXGI_FORMAT_UNKNOWN,
			.stencilViewFormat = DXGI_FORMAT_UNKNOWN
		},
		FormatInfo
		{
			.engineFormat = TextureFormat::R8_Unorm,
			.format = DXGI_FORMAT_R8_UNORM,
			.typelessFormat = DXGI_FORMAT_R8_TYPELESS,
			.srgbFormat = DXGI_FORMAT_UNKNOWN,
			.depthViewFormat = DXGI_FORMAT_UNKNOWN,
			.stencilViewFormat = DXGI_FORMAT_UNKNOWN
		},
		FormatInfo
		{
			.engineFormat = TextureFormat::R8_Uint,
			.format = DXGI_FORMAT_R8_UINT,
			.typelessFormat = DXGI_FORMAT_R8_TYPELESS,
			.srgbFormat = DXGI_FORMAT_UNKNOWN,
			.depthViewFormat = DXGI_FORMAT_UNKNOWN,
			.stencilViewFormat = DXGI_FORMAT_UNKNOWN
		},
		FormatInfo
		{
			.engineFormat = TextureFormat::R8_Snorm,
			.format = DXGI_FORMAT_R8_SNORM,
			.typelessFormat = DXGI_FORMAT_R8_TYPELESS,
			.srgbFormat = DXGI_FORMAT_UNKNOWN,
			.depthViewFormat = DXGI_FORMAT_UNKNOWN,
			.stencilViewFormat = DXGI_FORMAT_UNKNOWN
		},
		FormatInfo
		{
			.engineFormat = TextureFormat::R8_Sint,
			.format = DXGI_FORMAT_R8_SINT,
			.typelessFormat = DXGI_FORMAT_R8_TYPELESS,
			.srgbFormat = DXGI_FORMAT_UNKNOWN,
			.depthViewFormat = DXGI_FORMAT_UNKNOWN,
			.stencilViewFormat = DXGI_FORMAT_UNKNOWN
		},
		FormatInfo
		{
			.engineFormat = TextureFormat::B8G8R8A8_Unorm,
			.format = DXGI_FORMAT_B8G8R8A8_UNORM,
			.typelessFormat = DXGI_FORMAT_B8G8R8A8_TYPELESS,
			.srgbFormat = DXGI_FORMAT_B8G8R8A8_UNORM_SRGB,
			.depthViewFormat = DXGI_FORMAT_UNKNOWN,
			.stencilViewFormat = DXGI_FORMAT_UNKNOWN
		},
		FormatInfo
		{
			.engineFormat = TextureFormat::B8G8R8X8_Unorm,
			.format = DXGI_FORMAT_B8G8R8X8_UNORM,
			.typelessFormat = DXGI_FORMAT_B8G8R8X8_TYPELESS,
			.srgbFormat = DXGI_FORMAT_B8G8R8X8_UNORM_SRGB,
			.depthViewFormat = DXGI_FORMAT_UNKNOWN,
			.stencilViewFormat = DXGI_FORMAT_UNKNOWN
		},
		FormatInfo
		{
			.engineFormat = TextureFormat::A8_Unorm,
			.format = DXGI_FORMAT_A8_UNORM,
			.typelessFormat = DXGI_FORMAT_R8_TYPELESS,
			.srgbFormat = DXGI_FORMAT_UNKNOWN,
			.depthViewFormat = DXGI_FORMAT_UNKNOWN,
			.stencilViewFormat = DXGI_FORMAT_UNKNOWN
		},
		FormatInfo
		{
			.engineFormat = TextureFormat::B5G6R5_Unorm,
			.format = DXGI_FORMAT_B5G6R5_UNORM,
			.typelessFormat = DXGI_FORMAT_B5G6R5_UNORM,
			.srgbFormat = DXGI_FORMAT_UNKNOWN,
			.depthViewFormat = DXGI_FORMAT_UNKNOWN,
			.stencilViewFormat = DXGI_FORMAT_UNKNOWN
		},
		FormatInfo
		{
			.engineFormat = TextureFormat::B5G5R5A1_Unorm,
			.format = DXGI_FORMAT_B5G5R5A1_UNORM,
			.typelessFormat = DXGI_FORMAT_B5G5R5A1_UNORM,
			.srgbFormat = DXGI_FORMAT_UNKNOWN,
			.depthViewFormat = DXGI_FORMAT_UNKNOWN,
			.stencilViewFormat = DXGI_FORMAT_UNKNOWN
		},
		FormatInfo
		{
			.engineFormat = TextureFormat::BC1_Unorm,
			.format = DXGI_FORMAT_BC1_UNORM,
			.typelessFormat = DXGI_FORMAT_BC1_TYPELESS,
			.srgbFormat = DXGI_FORMAT_BC1_UNORM_SRGB,
			.depthViewFormat = DXGI_FORMAT_UNKNOWN,
			.stencilViewFormat = DXGI_FORMAT_UNKNOWN
		},
		FormatInfo
		{
			.engineFormat = TextureFormat::BC2_Unorm,
			.format = DXGI_FORMAT_BC2_UNORM,
			.typelessFormat = DXGI_FORMAT_BC2_TYPELESS,
			.srgbFormat = DXGI_FORMAT_BC2_UNORM_SRGB,
			.depthViewFormat = DXGI_FORMAT_UNKNOWN,
			.stencilViewFormat = DXGI_FORMAT_UNKNOWN
		},
		FormatInfo
		{
			.engineFormat = TextureFormat::BC3_Unorm,
			.format = DXGI_FORMAT_BC3_UNORM,
			.typelessFormat = DXGI_FORMAT_BC3_TYPELESS,
			.srgbFormat = DXGI_FORMAT_BC3_UNORM_SRGB,
			.depthViewFormat = DXGI_FORMAT_UNKNOWN,
			.stencilViewFormat = DXGI_FORMAT_UNKNOWN
		},
		FormatInfo
		{
			.engineFormat = TextureFormat::BC4_Unorm,
			.format = DXGI_FORMAT_BC4_UNORM,
			.typelessFormat = DXGI_FORMAT_BC4_TYPELESS,
			.srgbFormat = DXGI_FORMAT_UNKNOWN,
			.depthViewFormat = DXGI_FORMAT_UNKNOWN,
			.stencilViewFormat = DXGI_FORMAT_UNKNOWN
		},
		FormatInfo
		{
			.engineFormat = TextureFormat::BC4_Snorm,
			.format = DXGI_FORMAT_BC4_SNORM,
			.typelessFormat = DXGI_FORMAT_BC4_TYPELESS,
			.srgbFormat = DXGI_FORMAT_UNKNOWN,
			.depthViewFormat = DXGI_FORMAT_UNKNOWN,
			.stencilViewFormat = DXGI_FORMAT_UNKNOWN
		},
		FormatInfo
		{
			.engineFormat = TextureFormat::BC5_Unorm,
			.format = DXGI_FORMAT_BC5_UNORM,
			.typelessFormat = DXGI_FORMAT_BC5_TYPELESS,
			.srgbFormat = DXGI_FORMAT_UNKNOWN,
			.depthViewFormat = DXGI_FORMAT_UNKNOWN,
			.stencilViewFormat = DXGI_FORMAT_UNKNOWN
		},
		FormatInfo
		{
			.engineFormat = TextureFormat::BC5_Snorm,
			.format = DXGI_FORMAT_BC5_SNORM,
			.typelessFormat = DXGI_FORMAT_BC5_TYPELESS,
			.srgbFormat = DXGI_FORMAT_UNKNOWN,
			.depthViewFormat = DXGI_FORMAT_UNKNOWN,
			.stencilViewFormat = DXGI_FORMAT_UNKNOWN
		},
		FormatInfo
		{
			.engineFormat = TextureFormat::BC6H_UF16,
			.format = DXGI_FORMAT_BC6H_UF16,
			.typelessFormat = DXGI_FORMAT_BC6H_TYPELESS,
			.srgbFormat = DXGI_FORMAT_UNKNOWN,
			.depthViewFormat = DXGI_FORMAT_UNKNOWN,
			.stencilViewFormat = DXGI_FORMAT_UNKNOWN
		},
		FormatInfo
		{
			.engineFormat = TextureFormat::BC6H_SF16,
			.format = DXGI_FORMAT_BC6H_SF16,
			.typelessFormat = DXGI_FORMAT_BC6H_TYPELESS,
			.srgbFormat = DXGI_FORMAT_UNKNOWN,
			.depthViewFormat = DXGI_FORMAT_UNKNOWN,
			.stencilViewFormat = DXGI_FORMAT_UNKNOWN
		},
		FormatInfo
		{
			.engineFormat = TextureFormat::BC7_Unorm,
			.format = DXGI_FORMAT_BC7_UNORM,
			.typelessFormat = DXGI_FORMAT_BC7_TYPELESS,
			.srgbFormat = DXGI_FORMAT_BC7_UNORM_SRGB,
			.depthViewFormat = DXGI_FORMAT_UNKNOWN,
			.stencilViewFormat = DXGI_FORMAT_UNKNOWN
		}
	};

	/// @brief Main format map. Contains data that any format has.
	class MainFormatMap final
	{
	public:
		[[nodiscard("Pure constructor")]]
		constexpr MainFormatMap() noexcept
		{
			constexpr auto getAspect = [](const FormatInfo& info) noexcept
			{
				auto aspect = AspectMask::None;
				if (info.depthViewFormat != DXGI_FORMAT_UNKNOWN)
				{
					aspect |= AspectMask::Depth;
					if (info.stencilViewFormat != DXGI_FORMAT_UNKNOWN)
					{
						aspect |= AspectMask::Stencil;
					}
				}
				else
				{
					aspect |= AspectMask::Color;
				}

				return aspect;
			};

			for (std::size_t i = 0uz; i < FormatInfos.size(); ++i)
			{
				formats[i] = FormatInfos[i].format;
				aspects[i] = getAspect(FormatInfos[i]);
				typelessFormats[i] = FormatInfos[i].typelessFormat;
				engineFormats[i] = FormatInfos[i].engineFormat;
			}

			formats[FormatInfos.size()] = DXGI_FORMAT_UNKNOWN;
			aspects[FormatInfos.size()] = AspectMask::None;
			typelessFormats[FormatInfos.size()] = DXGI_FORMAT_UNKNOWN;
			engineFormats[FormatInfos.size()] = std::string_view();
		}
		[[nodiscard("Pure constructor")]]
		constexpr MainFormatMap(const MainFormatMap&) noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr MainFormatMap(MainFormatMap&&) noexcept = default;

		constexpr ~MainFormatMap() noexcept = default;

		/// @brief Gets the size.
		/// @return Map size.
		[[nodiscard("Pure function")]]
		static constexpr std::size_t MapSize() noexcept
		{
			return FormatInfos.size();
		}
		/// @brief Gets an index of the @p format.
		/// @param format Format.
		/// @return Format index. It's always safe to use. If the format is not found the index to default data is returned.
		[[nodiscard("Pure function")]]
		constexpr std::size_t IndexOf(const DXGI_FORMAT format) const noexcept
		{
			return std::ranges::find(formats.cbegin(), formats.cbegin() + MapSize(), format) - formats.cbegin();
		}

		/// @brief Gets a native format.
		/// @param index Format index. Must be less than @p MapSize().
		/// @return Native format.
		[[nodiscard("Pure function")]]
		constexpr DXGI_FORMAT GetFormat(const std::size_t index) const noexcept
		{
			return formats[index];
		}
		/// @brief Gets a format aspect.
		/// @param index Format index. Must be less than @p MapSize().
		/// @return Format aspect.
		[[nodiscard("Pure function")]]
		constexpr AspectMask GetAspect(const std::size_t index) const noexcept
		{
			return aspects[index];
		}
		/// @brief Gets a typeless format.
		/// @param index Format index. Must be less than @p MapSize().
		/// @return Typeless format.
		[[nodiscard("Pure function")]]
		constexpr DXGI_FORMAT GetTypelessFormat(const std::size_t index) const noexcept
		{
			return typelessFormats[index];
		}
		/// @brief Gets an engine format.
		/// @param index Format index. Must be less than @p MapSize().
		/// @return Engine format.
		[[nodiscard("Pure function")]]
		constexpr std::string_view GetEngineFormat(const std::size_t index) const noexcept
		{
			return engineFormats[index];
		}

		constexpr MainFormatMap& operator =(const MainFormatMap& other) noexcept = default;
		constexpr MainFormatMap& operator =(MainFormatMap&& other) noexcept = default;

	private:
		std::array<DXGI_FORMAT, FormatInfos.size() + 1> formats; ///< Native formats.
		std::array<AspectMask, FormatInfos.size() + 1> aspects; ///< Format aspects.
		std::array<DXGI_FORMAT, FormatInfos.size() + 1> typelessFormats; ///< Typeless formats.
		std::array<std::string_view, FormatInfos.size() + 1> engineFormats; ///< Engine formats.
	};
	constexpr MainFormatMap MainFormatMap; ///< Main format map.

	/// @brief Format map that contains specific format details.
	/// @tparam T Value type.
	/// @tparam Size Map size. The actual size is incremented by 1 to add a default set.
	template<typename T, std::size_t Size>
	class FormatMap final
	{
	public:
		[[nodiscard("Pure constructor")]]
		constexpr FormatMap() noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr FormatMap(const FormatMap& other) noexcept = default;
		[[nodiscard("Pure constructor")]]
		constexpr FormatMap(FormatMap&& other) noexcept = default;

		constexpr ~FormatMap() noexcept = default;

		/// @brief Gets a map size.
		/// @return Map size.
		[[nodiscard("Pure function")]]
		static constexpr std::size_t MapSize() noexcept
		{
			return Size;
		}
		/// @brief Gets an index of the format.
		/// @param format Format.
		/// @return Index of the format. It's always safe to use.
		[[nodiscard("Pure function")]]
		constexpr std::size_t IndexOf(const DXGI_FORMAT format) const noexcept
		{
			return std::ranges::find(formats.cbegin(), formats.cbegin() + Size, format) - formats.cbegin();
		}

		/// @brief Gets a format.
		/// @param index Format index.
		/// @return Format.
		[[nodiscard("Pure function")]]
		constexpr DXGI_FORMAT GetFormat(const std::size_t index) const noexcept
		{
			return formats[index];
		}
		/// @brief Gets a value.
		/// @param index Format index.
		/// @return Value.
		[[nodiscard("Pure function")]]
		constexpr const T& GetValue(const std::size_t index) const noexcept
		{
			return values[index];
		}
		/// @brief Sets a format-value pair.
		/// @param index Format index.
		/// @param format Format.
		/// @param value Value.
		constexpr void SetValue(const std::size_t index, const DXGI_FORMAT format, const T& value) noexcept
		{
			formats[index] = format;
			values[index] = value;
		}

		constexpr FormatMap& operator =(const FormatMap& other) noexcept = default;
		constexpr FormatMap& operator =(FormatMap& other) noexcept = default;

	private:
		std::array<DXGI_FORMAT, Size + 1> formats; ///< Formats.
		std::array<T, Size + 1> values; ///< Values.
	};

	/// @brief Gets SRGB compatible format count.
	/// @return SRGB compatible format count.
	[[nodiscard("Pure function")]]
	constexpr std::size_t GetSRGBFormatCount() noexcept
	{
		std::size_t count = 0uz;
		for (const FormatInfo& info : FormatInfos)
		{
			count += info.srgbFormat != DXGI_FORMAT_UNKNOWN;
		}

		return count;
	}
	constexpr std::size_t SRGBFormatCount = GetSRGBFormatCount(); ///< SRGB compatible format count.
	/// @brief Gets an SRGB format map.
	/// @return SRGB format map.
	[[nodiscard("Pure function")]]
	constexpr FormatMap<DXGI_FORMAT, SRGBFormatCount> GetSRGBFormatMap()
	{
		FormatMap<DXGI_FORMAT, SRGBFormatCount> map;

		std::size_t index = 0uz;
		for (const FormatInfo& info : FormatInfos)
		{
			if (info.srgbFormat != DXGI_FORMAT_UNKNOWN)
			{
				map.SetValue(index++, info.format, info.srgbFormat);
			}
		}
		map.SetValue(index, DXGI_FORMAT_UNKNOWN, DXGI_FORMAT_UNKNOWN);

		return map;
	}
	constexpr FormatMap<DXGI_FORMAT, SRGBFormatCount> SRGBFormatMap = GetSRGBFormatMap(); ///< SRGB format map.

	/// @brief Gets depth format count.
	/// @return Depth format count.
	[[nodiscard("Pure function")]]
	constexpr std::size_t GetDepthFormatCount() noexcept
	{
		std::size_t count = 0uz;
		for (const FormatInfo& info : FormatInfos)
		{
			count += info.depthViewFormat != DXGI_FORMAT_UNKNOWN;
		}

		return count;
	}
	constexpr std::size_t DepthFormatCount = GetDepthFormatCount(); ///< Depth format count.
	/// @brief Gets a depth format map.
	/// @return Depth format map.
	[[nodiscard("Pure function")]]
	constexpr FormatMap<DXGI_FORMAT, DepthFormatCount> GetDepthFormatMap()
	{
		FormatMap<DXGI_FORMAT, DepthFormatCount> map;

		std::size_t index = 0uz;
		for (const FormatInfo& info : FormatInfos)
		{
			if (info.depthViewFormat != DXGI_FORMAT_UNKNOWN)
			{
				map.SetValue(index++, info.format, info.depthViewFormat);
			}
		}
		map.SetValue(index, DXGI_FORMAT_UNKNOWN, DXGI_FORMAT_UNKNOWN);

		return map;
	}
	constexpr FormatMap<DXGI_FORMAT, DepthFormatCount> DepthFormatMap = GetDepthFormatMap(); ///< Depth format map.

	/// @brief Gets a stencil format count.
	/// @return Stencil format count.
	[[nodiscard("Pure function")]]
	constexpr std::size_t GetStencilFormatCount() noexcept
	{
		std::size_t count = 0uz;
		for (const FormatInfo& info : FormatInfos)
		{
			count += info.stencilViewFormat != DXGI_FORMAT_UNKNOWN;
		}

		return count;
	}
	constexpr std::size_t StencilFormatCount = GetStencilFormatCount(); ///< Stencil format count.
	/// @brief Gets a stencil format map.
	/// @return Stencil format map.
	[[nodiscard("Pure function")]]
	constexpr FormatMap<DXGI_FORMAT, StencilFormatCount> GetStencilFormatMap()
	{
		FormatMap<DXGI_FORMAT, StencilFormatCount> map;

		std::size_t index = 0uz;
		for (const FormatInfo& info : FormatInfos)
		{
			if (info.stencilViewFormat != DXGI_FORMAT_UNKNOWN)
			{
				map.SetValue(index++, info.format, info.stencilViewFormat);
			}
		}
		map.SetValue(index, DXGI_FORMAT_UNKNOWN, DXGI_FORMAT_UNKNOWN);

		return map;
	}
	constexpr FormatMap<DXGI_FORMAT, StencilFormatCount> StencilFormatMap = GetStencilFormatMap(); ///< Stencil format map.

	/// @brief Gets a typeless format of the native format.
	/// @param format Native format.
	/// @return Typeless format or UNKNOWN if invalid.
	[[nodiscard("Pure function")]]
	constexpr DXGI_FORMAT GetTypelessFormat(DXGI_FORMAT format) noexcept;

	/// @brief Checks if the format is SRGB-compatible.
	/// @param format Native format. Must be one of the @p FormatInfos.
	/// @return @a True if it's SRGB-compatible; @a false otherwise.
	[[nodiscard("Pure function")]]
	constexpr bool IsSRGBCompatibleFormat(DXGI_FORMAT format) noexcept;
	/// @brief Gets a SRGB format variant.
	/// @param format Original format.
	/// @return SRGB format variant or UNKNOWN if invalid.
	[[nodiscard("Pure function")]]
	constexpr DXGI_FORMAT GetSRGBFormat(DXGI_FORMAT format) noexcept;

	/// @brief Checks if the format is a depth stencil format.
	/// @param format Native format. Must be one of the @p FormatInfos.
	/// @return @a True if it's a depth stencil format; @a false otherwise.
	[[nodiscard("Pure function")]]
	constexpr bool IsDepthStencilFormat(DXGI_FORMAT format) noexcept;
	/// @brief Gets a depth view format.
	/// @param depthStencilFormat Depth stencil format.
	/// @return Depth view format or UNKNOWN if invalid.
	[[nodiscard("Pure function")]]
	constexpr DXGI_FORMAT GetDepthViewFormat(DXGI_FORMAT depthStencilFormat) noexcept;
	/// @brief Checks if the format has a stencil.
	/// @param format Native format. Must be one of the @p FormatInfos.
	/// @return @a True if the format has a stencil; @a false otherwise.
	[[nodiscard("Pure function")]]
	constexpr bool HasStencil(DXGI_FORMAT format) noexcept;
	/// @brief Gets a stencil view format.
	/// @param depthStencilFormat Depth stencil format.
	/// @return Stencil view format or UNKNOWN if invalid.
	[[nodiscard("Pure function")]]
	constexpr DXGI_FORMAT GetStencilViewFormat(DXGI_FORMAT depthStencilFormat) noexcept;

	/// @brief Gets the format aspects.
	/// @param format Native format.
	/// @return Format aspects.
	[[nodiscard("Pure function")]]
	constexpr AspectMask GetAspects(DXGI_FORMAT format) noexcept;

	/// @brief Gets texture dimensions from the support.
	/// @param support Texture format support.
	/// @return Texture dimensions.
	[[nodiscard("Pure function")]]
	constexpr TextureDimensionMask GetTextureDimensions(const D3D12_FEATURE_DATA_FORMAT_SUPPORT& support) noexcept;
	/// @brief Gets texture view dimensions from the support.
	/// @param support Texture format support.
	/// @return Texture view dimensions.
	[[nodiscard("Pure function")]]
	constexpr TextureViewDimensionMask GetTextureViewDimensions(const D3D12_FEATURE_DATA_FORMAT_SUPPORT& support) noexcept;
	/// @brief Gets a texture usage from the support.
	/// @param support Texture format support.
	/// @return Texture usage.
	[[nodiscard("Pure function")]]
	constexpr TextureUsage GetTextureUsage(const D3D12_FEATURE_DATA_FORMAT_SUPPORT& support) noexcept;
	/// @brief Gets shader operations from the support.
	/// @param support Texture format support.
	/// @return Shader operations.
	[[nodiscard("Pure function")]]
	constexpr ShaderOperationMask GetShaderOperations(const D3D12_FEATURE_DATA_FORMAT_SUPPORT& support) noexcept;
	/// @brief Gets blend modes from the support.
	/// @param support Texture format support.
	/// @return Blend modes.
	[[nodiscard("Pure function")]]
	constexpr BlendModeMask GetBlendModes(const D3D12_FEATURE_DATA_FORMAT_SUPPORT& support) noexcept;
	/// @brief Checks if the format is swap chain compatible.
	/// @param support Texture format support.
	/// @return @a True if it's swap chain compatible; @a false otherwise.
	[[nodiscard("Pure function")]]
	constexpr bool IsSwapChainCompatible(const D3D12_FEATURE_DATA_FORMAT_SUPPORT& support) noexcept;
}

namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	constexpr DXGI_FORMAT GetTypelessFormat(const DXGI_FORMAT format) noexcept
	{
		return MainFormatMap.GetTypelessFormat(MainFormatMap.IndexOf(format));
	}

	constexpr bool IsSRGBCompatibleFormat(const DXGI_FORMAT format) noexcept
	{
		return SRGBFormatMap.IndexOf(format) < SRGBFormatMap.MapSize();
	}

	constexpr DXGI_FORMAT GetSRGBFormat(const DXGI_FORMAT format) noexcept
	{
		return SRGBFormatMap.GetValue(SRGBFormatMap.IndexOf(format));
	}

	constexpr bool IsDepthStencilFormat(const DXGI_FORMAT format) noexcept
	{
		return DepthFormatMap.IndexOf(format) < DepthFormatMap.MapSize();
	}

	constexpr DXGI_FORMAT GetDepthViewFormat(const DXGI_FORMAT depthStencilFormat) noexcept
	{
		return DepthFormatMap.GetValue(DepthFormatMap.IndexOf(depthStencilFormat));
	}

	constexpr bool HasStencil(const DXGI_FORMAT format) noexcept
	{
		return StencilFormatMap.IndexOf(format) < StencilFormatMap.MapSize();
	}

	constexpr DXGI_FORMAT GetStencilViewFormat(const DXGI_FORMAT depthStencilFormat) noexcept
	{
		return StencilFormatMap.GetValue(StencilFormatMap.IndexOf(depthStencilFormat));
	}

	constexpr AspectMask GetAspects(const DXGI_FORMAT format) noexcept
	{
		return MainFormatMap.GetAspect(MainFormatMap.IndexOf(format));
	}

	constexpr TextureDimensionMask GetTextureDimensions(const D3D12_FEATURE_DATA_FORMAT_SUPPORT& support) noexcept
	{
		auto dimensions = TextureDimensionMask::None;
		if (support.Support1 & D3D12_FORMAT_SUPPORT1_TEXTURE1D)
		{
			dimensions |= TextureDimensionMask::Texture1D;
		}
		if (support.Support1 & D3D12_FORMAT_SUPPORT1_TEXTURE2D)
		{
			dimensions |= TextureDimensionMask::Texture2D;
		}
		if (support.Support1 & D3D12_FORMAT_SUPPORT1_TEXTURE3D)
		{
			dimensions |= TextureDimensionMask::Texture3D;
		}

		return dimensions;
	}

	constexpr TextureViewDimensionMask GetTextureViewDimensions(const D3D12_FEATURE_DATA_FORMAT_SUPPORT& support) noexcept
	{
		auto dimensions = TextureViewDimensionMask::None;
		if (support.Support1 & D3D12_FORMAT_SUPPORT1_TEXTURE1D)
		{
			dimensions |= TextureViewDimensionMask::Texture1D;
		}
		if (support.Support1 & D3D12_FORMAT_SUPPORT1_TEXTURE2D)
		{
			dimensions |= TextureViewDimensionMask::Texture2D;
		}
		if (support.Support1 & D3D12_FORMAT_SUPPORT1_TEXTURE3D)
		{
			dimensions |= TextureViewDimensionMask::Texture3D;
		}
		if (support.Support1 & D3D12_FORMAT_SUPPORT1_TEXTURECUBE)
		{
			dimensions |= TextureViewDimensionMask::TextureCube;
		}

		return dimensions;
	}

	constexpr TextureUsage GetTextureUsage(const D3D12_FEATURE_DATA_FORMAT_SUPPORT& support) noexcept
	{
		auto usage = TextureUsage::ShaderResource;
		if (support.Support1 & D3D12_FORMAT_SUPPORT1_TYPED_UNORDERED_ACCESS_VIEW)
		{
			usage |= TextureUsage::UnorderedAccess;
		}
		if (support.Support1 & D3D12_FORMAT_SUPPORT1_RENDER_TARGET)
		{
			usage |= TextureUsage::RenderTarget;
		}
		if (support.Support1 & D3D12_FORMAT_SUPPORT1_DEPTH_STENCIL)
		{
			usage |= TextureUsage::DepthStencil;
		}

		return usage;
	}

	constexpr ShaderOperationMask GetShaderOperations(const D3D12_FEATURE_DATA_FORMAT_SUPPORT& support) noexcept
	{
		auto operations = ShaderOperationMask::None;
		if (support.Support1 & D3D12_FORMAT_SUPPORT1_SHADER_LOAD)
		{
			operations |= ShaderOperationMask::ShaderLoad;
		}
		if (support.Support1 & D3D12_FORMAT_SUPPORT1_SHADER_SAMPLE)
		{
			operations |= ShaderOperationMask::ShaderSample;
		}
		if (support.Support1 & D3D12_FORMAT_SUPPORT1_SHADER_SAMPLE_COMPARISON)
		{
			operations |= ShaderOperationMask::ShaderSampleComparison;
		}
		if (support.Support1 & D3D12_FORMAT_SUPPORT1_SHADER_GATHER)
		{
			operations |= ShaderOperationMask::ShaderGather;
		}
		if (support.Support1 & D3D12_FORMAT_SUPPORT1_SHADER_GATHER_COMPARISON)
		{
			operations |= ShaderOperationMask::ShaderGatherComparison;
		}
		if (support.Support2 & D3D12_FORMAT_SUPPORT2_UAV_ATOMIC_ADD)
		{
			operations |= ShaderOperationMask::UnorderedAccessAtomicAdd;
		}
		if (support.Support2 & D3D12_FORMAT_SUPPORT2_UAV_ATOMIC_BITWISE_OPS)
		{
			operations |= ShaderOperationMask::UnorderedAccessAtomicBitwise;
		}
		if (support.Support2 & D3D12_FORMAT_SUPPORT2_UAV_ATOMIC_EXCHANGE)
		{
			operations |= ShaderOperationMask::UnorderedAccessAtomicExchange;
		}
		if (support.Support2 & D3D12_FORMAT_SUPPORT2_UAV_ATOMIC_COMPARE_STORE_OR_COMPARE_EXCHANGE)
		{
			operations |= ShaderOperationMask::UnorderedAccessAtomicExchangeComparison;
		}
		if (support.Support2 & D3D12_FORMAT_SUPPORT2_UAV_ATOMIC_SIGNED_MIN_OR_MAX)
		{
			operations |= ShaderOperationMask::UnorderedAccessAtomicSignedMinMax;
		}
		if (support.Support2 & D3D12_FORMAT_SUPPORT2_UAV_ATOMIC_UNSIGNED_MIN_OR_MAX)
		{
			operations |= ShaderOperationMask::UnorderedAccessAtomicUnsignedMinMax;
		}
		if (support.Support2 & D3D12_FORMAT_SUPPORT2_UAV_TYPED_LOAD)
		{
			operations |= ShaderOperationMask::UnorderedAccessLoad;
		}
		if (support.Support2 & D3D12_FORMAT_SUPPORT2_UAV_TYPED_STORE)
		{
			operations |= ShaderOperationMask::UnorderedAccessStore;
		}

		return operations;
	}

	constexpr BlendModeMask GetBlendModes(const D3D12_FEATURE_DATA_FORMAT_SUPPORT& support) noexcept
	{
		auto modes = BlendModeMask::None;
		if (support.Support1 & D3D12_FORMAT_SUPPORT1_BLENDABLE)
		{
			modes |= BlendModeMask::Arithmetic;
		}
		if (support.Support2 & D3D12_FORMAT_SUPPORT2_OUTPUT_MERGER_LOGIC_OP)
		{
			modes |= BlendModeMask::Logic;
		}

		return modes;
	}

	constexpr bool IsSwapChainCompatible(const D3D12_FEATURE_DATA_FORMAT_SUPPORT& support) noexcept
	{
		return support.Support1 & D3D12_FORMAT_SUPPORT1_DISPLAY;
	}
}
