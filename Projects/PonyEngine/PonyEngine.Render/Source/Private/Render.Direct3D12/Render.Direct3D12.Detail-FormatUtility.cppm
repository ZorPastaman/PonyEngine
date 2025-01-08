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

export namespace PonyEngine::Render::Direct3D12
{
	/// @brief Gets an srgb version of the @p sourceFormat.
	/// @param sourceFormat Source format.
	/// @return Srgb format.
	constexpr DXGI_FORMAT GetSrgbFormat(DXGI_FORMAT sourceFormat) noexcept;
}

namespace PonyEngine::Render::Direct3D12
{
	constexpr DXGI_FORMAT GetSrgbFormat(const DXGI_FORMAT sourceFormat) noexcept
	{
		switch (sourceFormat)
		{
		case DXGI_FORMAT_R8G8B8A8_UNORM:
			return DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
		case DXGI_FORMAT_BC1_UNORM:
			return DXGI_FORMAT_BC1_UNORM_SRGB;
		case DXGI_FORMAT_BC2_UNORM:
			return DXGI_FORMAT_BC2_UNORM_SRGB;
		case DXGI_FORMAT_BC3_UNORM:
			return DXGI_FORMAT_BC3_UNORM_SRGB;
		case DXGI_FORMAT_B8G8R8A8_UNORM:
			return DXGI_FORMAT_B8G8R8A8_UNORM_SRGB;
		case DXGI_FORMAT_B8G8R8X8_UNORM:
			return DXGI_FORMAT_B8G8R8X8_UNORM_SRGB;
		case DXGI_FORMAT_BC7_UNORM:
			return DXGI_FORMAT_BC7_UNORM_SRGB;
		default: [[unlikely]]
			assert(false && "Incorrect source format");
			return DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
		}
	}
}
