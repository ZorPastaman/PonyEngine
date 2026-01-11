/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Render/Windows/D3D12Framework.h"

export module PonyEngine.RenderDevice.D3D12.Impl.Windows:D3D12Utility;

import std;

import PonyEngine.RenderDevice;

export namespace PonyEngine::Render::Windows
{
	[[nodiscard("Pure function")]]
	DXGI_FORMAT GetSrgbFormat(DXGI_FORMAT format) noexcept;
	[[nodiscard("Pure function")]]
	DXGI_FORMAT GetTypelessFormat(DXGI_FORMAT format) noexcept;
	[[nodiscard("Pure function")]]
	bool IsDepthStencilFormat(DXGI_FORMAT format) noexcept;
	[[nodiscard("Pure function")]]
	DXGI_FORMAT GetDepthViewFormat(DXGI_FORMAT depthStencilFormat) noexcept;
	[[nodiscard("Pure function")]]
	DXGI_FORMAT GetStencilViewFormat(DXGI_FORMAT depthStencilFormat) noexcept;

	/// @brief Sets the object name.
	/// @param object Target object.
	/// @param name Name to set.
	void SetName(ID3D12Object& object, std::string_view name);
}

namespace PonyEngine::Render::Windows
{
	DXGI_FORMAT GetSrgbFormat(const DXGI_FORMAT format) noexcept
	{
		switch (format)
		{
		case DXGI_FORMAT_R8G8B8A8_UNORM:
			return DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
		case DXGI_FORMAT_B8G8R8A8_UNORM:
			return DXGI_FORMAT_B8G8R8A8_UNORM_SRGB;
		case DXGI_FORMAT_B8G8R8X8_UNORM:
			return DXGI_FORMAT_B8G8R8X8_UNORM_SRGB;
		case DXGI_FORMAT_BC1_UNORM:
			return DXGI_FORMAT_BC1_UNORM_SRGB;
		case DXGI_FORMAT_BC2_UNORM:
			return DXGI_FORMAT_BC2_UNORM_SRGB;
		case DXGI_FORMAT_BC3_UNORM:
			return DXGI_FORMAT_BC3_UNORM_SRGB;
		case DXGI_FORMAT_BC7_UNORM:
			return DXGI_FORMAT_BC7_UNORM_SRGB;
		default:
			return DXGI_FORMAT_UNKNOWN;
		}
	}

	DXGI_FORMAT GetTypelessFormat(const DXGI_FORMAT format) noexcept
	{
		switch (format)
		{
		case DXGI_FORMAT_R32G32B32A32_TYPELESS:
		case DXGI_FORMAT_R32G32B32A32_FLOAT:
		case DXGI_FORMAT_R32G32B32A32_UINT:
		case DXGI_FORMAT_R32G32B32A32_SINT:
			return DXGI_FORMAT_R32G32B32A32_TYPELESS;
		case DXGI_FORMAT_R32G32B32_TYPELESS:
		case DXGI_FORMAT_R32G32B32_FLOAT:
		case DXGI_FORMAT_R32G32B32_UINT:
		case DXGI_FORMAT_R32G32B32_SINT:
			return DXGI_FORMAT_R32G32B32_TYPELESS;
		case DXGI_FORMAT_R16G16B16A16_TYPELESS:
		case DXGI_FORMAT_R16G16B16A16_FLOAT:
		case DXGI_FORMAT_R16G16B16A16_UNORM:
		case DXGI_FORMAT_R16G16B16A16_UINT:
		case DXGI_FORMAT_R16G16B16A16_SNORM:
		case DXGI_FORMAT_R16G16B16A16_SINT:
			return DXGI_FORMAT_R16G16B16A16_TYPELESS;
		case DXGI_FORMAT_R32G32_TYPELESS:
		case DXGI_FORMAT_R32G32_FLOAT:
		case DXGI_FORMAT_R32G32_UINT:
		case DXGI_FORMAT_R32G32_SINT:
			return DXGI_FORMAT_R32G32_TYPELESS;
		case DXGI_FORMAT_R32G8X24_TYPELESS:
		case DXGI_FORMAT_D32_FLOAT_S8X24_UINT:
		case DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS:
		case DXGI_FORMAT_X32_TYPELESS_G8X24_UINT:
			return DXGI_FORMAT_R32G8X24_TYPELESS;
		case DXGI_FORMAT_R10G10B10A2_TYPELESS:
		case DXGI_FORMAT_R10G10B10A2_UNORM:
		case DXGI_FORMAT_R10G10B10A2_UINT:
			return DXGI_FORMAT_R10G10B10A2_TYPELESS;
		case DXGI_FORMAT_R8G8B8A8_TYPELESS:
		case DXGI_FORMAT_R8G8B8A8_UNORM:
		case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
		case DXGI_FORMAT_R8G8B8A8_UINT:
		case DXGI_FORMAT_R8G8B8A8_SNORM:
		case DXGI_FORMAT_R8G8B8A8_SINT:
			return DXGI_FORMAT_R8G8B8A8_TYPELESS;
		case DXGI_FORMAT_R16G16_TYPELESS:
		case DXGI_FORMAT_R16G16_FLOAT:
		case DXGI_FORMAT_R16G16_UNORM:
		case DXGI_FORMAT_R16G16_UINT:
		case DXGI_FORMAT_R16G16_SNORM:
		case DXGI_FORMAT_R16G16_SINT:
			return DXGI_FORMAT_R16G16_TYPELESS;
		case DXGI_FORMAT_R32_TYPELESS:
		case DXGI_FORMAT_D32_FLOAT:
		case DXGI_FORMAT_R32_FLOAT:
		case DXGI_FORMAT_R32_UINT:
		case DXGI_FORMAT_R32_SINT:
			return DXGI_FORMAT_R32_TYPELESS;
		case DXGI_FORMAT_R24G8_TYPELESS:
		case DXGI_FORMAT_D24_UNORM_S8_UINT:
		case DXGI_FORMAT_R24_UNORM_X8_TYPELESS:
		case DXGI_FORMAT_X24_TYPELESS_G8_UINT:
			return DXGI_FORMAT_R24G8_TYPELESS;
		case DXGI_FORMAT_R8G8_TYPELESS:
		case DXGI_FORMAT_R8G8_UNORM:
		case DXGI_FORMAT_R8G8_UINT:
		case DXGI_FORMAT_R8G8_SNORM:
		case DXGI_FORMAT_R8G8_SINT:
			return DXGI_FORMAT_R8G8_TYPELESS;
		case DXGI_FORMAT_R16_TYPELESS:
		case DXGI_FORMAT_R16_FLOAT:
		case DXGI_FORMAT_D16_UNORM:
		case DXGI_FORMAT_R16_UNORM:
		case DXGI_FORMAT_R16_UINT:
		case DXGI_FORMAT_R16_SNORM:
		case DXGI_FORMAT_R16_SINT:
			return DXGI_FORMAT_R16_TYPELESS;
		case DXGI_FORMAT_R8_TYPELESS:
		case DXGI_FORMAT_R8_UNORM:
		case DXGI_FORMAT_R8_UINT:
		case DXGI_FORMAT_R8_SNORM:
		case DXGI_FORMAT_R8_SINT:
		case DXGI_FORMAT_A8_UNORM:
			return DXGI_FORMAT_R8_TYPELESS;
		case DXGI_FORMAT_BC1_TYPELESS:
		case DXGI_FORMAT_BC1_UNORM:
		case DXGI_FORMAT_BC1_UNORM_SRGB:
			return DXGI_FORMAT_BC1_TYPELESS;
		case DXGI_FORMAT_BC2_TYPELESS:
		case DXGI_FORMAT_BC2_UNORM:
		case DXGI_FORMAT_BC2_UNORM_SRGB:
			return DXGI_FORMAT_BC2_TYPELESS;
		case DXGI_FORMAT_BC3_TYPELESS:
		case DXGI_FORMAT_BC3_UNORM:
		case DXGI_FORMAT_BC3_UNORM_SRGB:
			return DXGI_FORMAT_BC3_TYPELESS;
		case DXGI_FORMAT_BC4_TYPELESS:
		case DXGI_FORMAT_BC4_UNORM:
		case DXGI_FORMAT_BC4_SNORM:
			return DXGI_FORMAT_BC4_TYPELESS;
		case DXGI_FORMAT_BC5_TYPELESS:
		case DXGI_FORMAT_BC5_UNORM:
		case DXGI_FORMAT_BC5_SNORM:
			return DXGI_FORMAT_BC5_TYPELESS;
		case DXGI_FORMAT_B8G8R8A8_UNORM:
		case DXGI_FORMAT_B8G8R8A8_TYPELESS:
		case DXGI_FORMAT_B8G8R8A8_UNORM_SRGB:
			return DXGI_FORMAT_B8G8R8A8_TYPELESS;
		case DXGI_FORMAT_B8G8R8X8_UNORM:
		case DXGI_FORMAT_B8G8R8X8_TYPELESS:
		case DXGI_FORMAT_B8G8R8X8_UNORM_SRGB:
			return DXGI_FORMAT_B8G8R8X8_TYPELESS;
		case DXGI_FORMAT_BC6H_TYPELESS:
		case DXGI_FORMAT_BC6H_UF16:
		case DXGI_FORMAT_BC6H_SF16:
			return DXGI_FORMAT_BC6H_TYPELESS;
		case DXGI_FORMAT_BC7_TYPELESS:
		case DXGI_FORMAT_BC7_UNORM:
		case DXGI_FORMAT_BC7_UNORM_SRGB:
			return DXGI_FORMAT_BC7_TYPELESS;
		default:
			return DXGI_FORMAT_UNKNOWN;
		}
	}

	bool IsDepthStencilFormat(const DXGI_FORMAT format) noexcept
	{
		return format == DXGI_FORMAT_D32_FLOAT_S8X24_UINT || format == DXGI_FORMAT_D32_FLOAT ||
			format == DXGI_FORMAT_D24_UNORM_S8_UINT || format == DXGI_FORMAT_D16_UNORM;
	}

	DXGI_FORMAT GetDepthViewFormat(const DXGI_FORMAT depthStencilFormat) noexcept
	{
		switch (depthStencilFormat)
		{
		case DXGI_FORMAT_D32_FLOAT_S8X24_UINT:
			return DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS;
		case DXGI_FORMAT_D32_FLOAT:
			return DXGI_FORMAT_R32_FLOAT;
		case DXGI_FORMAT_D24_UNORM_S8_UINT:
			return DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
		case DXGI_FORMAT_D16_UNORM:
			return DXGI_FORMAT_R16_UNORM;
		default:
			return DXGI_FORMAT_UNKNOWN;
		}
	}

	DXGI_FORMAT GetStencilViewFormat(const DXGI_FORMAT depthStencilFormat) noexcept
	{
		switch (depthStencilFormat)
		{
		case DXGI_FORMAT_D32_FLOAT_S8X24_UINT:
			return DXGI_FORMAT_X32_TYPELESS_G8X24_UINT;
		case DXGI_FORMAT_D24_UNORM_S8_UINT:
			return DXGI_FORMAT_X24_TYPELESS_G8_UINT;
		default:
			return DXGI_FORMAT_UNKNOWN;
		}
	}

	void SetName(ID3D12Object& object, const std::string_view name)
	{
		if (const HRESULT result = object.SetPrivateData(WKPDID_D3DDebugObjectName, static_cast<UINT>(name.size()), name.data()); FAILED(result)) [[unlikely]]
		{
			throw std::runtime_error(std::format("Failed to set name: Result = '0x{:X}'", static_cast<std::make_unsigned_t<HRESULT>>(result)));
		}
	}
}
