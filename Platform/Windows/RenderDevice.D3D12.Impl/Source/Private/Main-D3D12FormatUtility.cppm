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

export module PonyEngine.RenderDevice.D3D12.Impl.Windows:D3D12FormatUtility;

import std;

import PonyEngine.RenderDevice;

export namespace PonyEngine::RenderDevice::Windows
{
	struct FormatInfo final
	{
		std::string_view engineFormat;
		DXGI_FORMAT format;
		DXGI_FORMAT typelessFormat;
		DXGI_FORMAT srgbFormat;
		DXGI_FORMAT depthViewFormat;
		DXGI_FORMAT stencilViewFormat;
	};
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

	class MainFormatMap final
	{
	public:
		[[nodiscard("Pure constructor")]]
		constexpr MainFormatMap() noexcept
		{
			auto getAspect = [](const FormatInfo& info) noexcept
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

		[[nodiscard("Pure function")]]
		static constexpr std::size_t MapSize() noexcept
		{
			return FormatInfos.size();
		}
		[[nodiscard("Pure function")]]
		constexpr std::size_t IndexOf(const DXGI_FORMAT format) const noexcept
		{
			return std::ranges::find(formats.cbegin(), formats.cbegin() + MapSize(), format) - formats.cbegin();
		}

		[[nodiscard("Pure function")]]
		constexpr DXGI_FORMAT GetFormat(const std::size_t index) const noexcept
		{
			return formats[index];
		}

		[[nodiscard("Pure function")]]
		constexpr AspectMask GetAspect(const std::size_t index) const noexcept
		{
			return aspects[index];
		}

		[[nodiscard("Pure function")]]
		constexpr DXGI_FORMAT GetTypelessFormat(const std::size_t index) const noexcept
		{
			return typelessFormats[index];
		}

		[[nodiscard("Pure function")]]
		constexpr std::string_view GetEngineFormat(const std::size_t index) const noexcept
		{
			return engineFormats[index];
		}

		constexpr MainFormatMap& operator =(const MainFormatMap& other) noexcept = default;
		constexpr MainFormatMap& operator =(MainFormatMap&& other) noexcept = default;

	private:
		std::array<DXGI_FORMAT, FormatInfos.size() + 1> formats;
		std::array<AspectMask, FormatInfos.size() + 1> aspects;
		std::array<DXGI_FORMAT, FormatInfos.size() + 1> typelessFormats;
		std::array<std::string_view, FormatInfos.size() + 1> engineFormats;
	};
	constexpr MainFormatMap MainFormatMap;

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

		[[nodiscard("Pure function")]]
		static constexpr std::size_t MapSize() noexcept
		{
			return Size;
		}
		[[nodiscard("Pure function")]]
		constexpr std::size_t IndexOf(const DXGI_FORMAT format) const noexcept
		{
			return std::ranges::find(formats.cbegin(), formats.cbegin() + Size, format) - formats.cbegin();
		}

		[[nodiscard("Pure function")]]
		constexpr DXGI_FORMAT GetFormat(const std::size_t index) const noexcept
		{
			return formats[index];
		}
		[[nodiscard("Pure function")]]
		constexpr const T& GetValue(const std::size_t index) const noexcept
		{
			return values[index];
		}
		constexpr void SetValue(const std::size_t index, const DXGI_FORMAT format, const T& value) noexcept
		{
			formats[index] = format;
			values[index] = value;
		}

		constexpr FormatMap& operator =(const FormatMap& other) noexcept = default;
		constexpr FormatMap& operator =(FormatMap& other) noexcept = default;

	private:
		std::array<DXGI_FORMAT, Size + 1> formats;
		std::array<T, Size + 1> values;
	};

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
	constexpr std::size_t SRGBFormatCount = GetSRGBFormatCount();
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
	constexpr FormatMap<DXGI_FORMAT, SRGBFormatCount> SRGBFormatMap = GetSRGBFormatMap();

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
	constexpr std::size_t DepthFormatCount = GetDepthFormatCount();
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
	constexpr FormatMap<DXGI_FORMAT, DepthFormatCount> DepthFormatMap = GetDepthFormatMap();

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
	constexpr std::size_t StencilFormatCount = GetStencilFormatCount();
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
	constexpr FormatMap<DXGI_FORMAT, StencilFormatCount> StencilFormatMap = GetStencilFormatMap();

	[[nodiscard("Pure function")]]
	constexpr DXGI_FORMAT GetTypelessFormat(DXGI_FORMAT format) noexcept;

	[[nodiscard("Pure function")]]
	constexpr bool IsSRGBCompatibleFormat(DXGI_FORMAT format) noexcept;
	[[nodiscard("Pure function")]]
	constexpr DXGI_FORMAT GetSRGBFormat(DXGI_FORMAT format) noexcept;

	[[nodiscard("Pure function")]]
	constexpr bool IsDepthStencilFormat(DXGI_FORMAT format) noexcept;
	[[nodiscard("Pure function")]]
	constexpr DXGI_FORMAT GetDepthViewFormat(DXGI_FORMAT depthStencilFormat) noexcept;
	[[nodiscard("Pure function")]]
	constexpr bool HasStencil(DXGI_FORMAT format) noexcept;
	[[nodiscard("Pure function")]]
	constexpr DXGI_FORMAT GetStencilViewFormat(DXGI_FORMAT depthStencilFormat) noexcept;

	[[nodiscard("Pure function")]]
	constexpr AspectMask GetAspects(DXGI_FORMAT format) noexcept;

	[[nodiscard("Pure function")]]
	constexpr TextureFormatFeature ToTextureFormatFeature(const D3D12_FEATURE_DATA_FORMAT_SUPPORT& support) noexcept;
}

namespace PonyEngine::RenderDevice::Windows
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
		return StencilFormatMap.GetValue(StencilFormatMap.IndexOf(format)) < StencilFormatMap.MapSize();
	}

	constexpr DXGI_FORMAT GetStencilViewFormat(const DXGI_FORMAT depthStencilFormat) noexcept
	{
		return StencilFormatMap.GetValue(StencilFormatMap.IndexOf(depthStencilFormat));
	}

	constexpr AspectMask GetAspects(const DXGI_FORMAT format) noexcept
	{
		return MainFormatMap.GetAspect(MainFormatMap.IndexOf(format));
	}

	constexpr TextureFormatFeature ToTextureFormatFeature(const D3D12_FEATURE_DATA_FORMAT_SUPPORT& support) noexcept
	{
		auto features = TextureFormatFeature::None;
		if (support.Support1 & D3D12_FORMAT_SUPPORT1_SHADER_LOAD)
		{
			features |= TextureFormatFeature::ShaderLoad;
		}
		if (support.Support1 & D3D12_FORMAT_SUPPORT1_SHADER_SAMPLE)
		{
			features |= TextureFormatFeature::ShaderSample;
		}
		if (support.Support1 & D3D12_FORMAT_SUPPORT1_SHADER_SAMPLE_COMPARISON)
		{
			features |= TextureFormatFeature::ShaderSampleComparison;
		}
		if (support.Support1 & D3D12_FORMAT_SUPPORT1_SHADER_GATHER)
		{
			features |= TextureFormatFeature::ShaderGather;
		}
		if (support.Support1 & D3D12_FORMAT_SUPPORT1_SHADER_GATHER_COMPARISON)
		{
			features |= TextureFormatFeature::ShaderGatherComparison;
		}
		if (support.Support1 & D3D12_FORMAT_SUPPORT1_RENDER_TARGET)
		{
			features |= TextureFormatFeature::RenderTarget;
		}
		if (support.Support1 & D3D12_FORMAT_SUPPORT1_BLENDABLE)
		{
			features |= TextureFormatFeature::Blendable;
		}
		if (support.Support2 & D3D12_FORMAT_SUPPORT2_OUTPUT_MERGER_LOGIC_OP)
		{
			features |= TextureFormatFeature::LogicBlendable;
		}
		if (support.Support1 & D3D12_FORMAT_SUPPORT1_DEPTH_STENCIL)
		{
			features |= TextureFormatFeature::DepthStencil;
		}
		if (support.Support1 & D3D12_FORMAT_SUPPORT1_TYPED_UNORDERED_ACCESS_VIEW)
		{
			features |= TextureFormatFeature::UnorderedAccess;
		}
		if (support.Support2 & D3D12_FORMAT_SUPPORT2_UAV_ATOMIC_ADD)
		{
			features |= TextureFormatFeature::UnorderedAccessAtomicAdd;
		}
		if (support.Support2 & D3D12_FORMAT_SUPPORT2_UAV_ATOMIC_BITWISE_OPS)
		{
			features |= TextureFormatFeature::UnorderedAccessAtomicBitwise;
		}
		if (support.Support2 & D3D12_FORMAT_SUPPORT2_UAV_ATOMIC_EXCHANGE)
		{
			features |= TextureFormatFeature::UnorderedAccessAtomicExchange;
		}
		if (support.Support2 & D3D12_FORMAT_SUPPORT2_UAV_ATOMIC_COMPARE_STORE_OR_COMPARE_EXCHANGE)
		{
			features |= TextureFormatFeature::UnorderedAccessAtomicExchangeComparison;
		}
		if (support.Support2 & D3D12_FORMAT_SUPPORT2_UAV_ATOMIC_SIGNED_MIN_OR_MAX)
		{
			features |= TextureFormatFeature::UnorderedAccessAtomicSignedMinMax;
		}
		if (support.Support2 & D3D12_FORMAT_SUPPORT2_UAV_ATOMIC_UNSIGNED_MIN_OR_MAX)
		{
			features |= TextureFormatFeature::UnorderedAccessAtomicUnsignedMinMax;
		}
		if (support.Support2 & D3D12_FORMAT_SUPPORT2_UAV_TYPED_LOAD)
		{
			features |= TextureFormatFeature::UnorderedAccessLoad;
		}
		if (support.Support2 & D3D12_FORMAT_SUPPORT2_UAV_TYPED_STORE)
		{
			features |= TextureFormatFeature::UnorderedAccessStore;
		}
		if (support.Support1 & D3D12_FORMAT_SUPPORT1_DISPLAY)
		{
			features |= TextureFormatFeature::SwapChain;
		}
		if (IsSRGBCompatibleFormat(support.Format))
		{
			features |= TextureFormatFeature::SRGB;
		}
		if (support.Support1 & D3D12_FORMAT_SUPPORT1_TEXTURECUBE)
		{
			features |= TextureFormatFeature::Cube;
		}

		return features;
	}
}
