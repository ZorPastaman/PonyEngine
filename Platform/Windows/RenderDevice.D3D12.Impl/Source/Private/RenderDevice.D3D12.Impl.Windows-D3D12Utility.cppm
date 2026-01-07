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
