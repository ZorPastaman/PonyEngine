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

export module PonyEngine.Render.Direct3D12.Detail:Direct3D12FormatUtility;

export namespace PonyEngine::Render
{
	/// @brief Gets the vertex format info.
	/// @param format Vertex format.
	/// @param componentSize Component size in bytes.
	/// @param componentCount Component count.
	/// @return Index format.
	constexpr void GetVertexFormatInfo(DXGI_FORMAT format, UINT& componentSize, UINT& componentCount) noexcept;
	/// @brief Gets the index format info.
	/// @param format Index format. Must be DXGI_FORMAT_R16_UINT or DXGI_FORMAT_R32_UINT.
	/// @param indexSize Index size in bytes.
	/// @return Index format.
	constexpr void GetIndexFormatInfo(DXGI_FORMAT format, UINT& indexSize) noexcept;

	/// @brief Gets an srgb version of the @p sourceFormat.
	/// @param sourceFormat Source format.
	/// @return Srgb format.
	constexpr DXGI_FORMAT GetSrgbFormat(DXGI_FORMAT sourceFormat) noexcept;
}

namespace PonyEngine::Render
{
	constexpr void GetVertexFormatInfo(const DXGI_FORMAT format, UINT& componentSize, UINT& componentCount) noexcept
	{
		switch (format)
		{
		case DXGI_FORMAT_R32G32B32A32_FLOAT:
		case DXGI_FORMAT_R32G32B32A32_UINT:
		case DXGI_FORMAT_R32G32B32A32_SINT:
			componentSize = 4u;
			componentCount = 4u;
			break;
		case DXGI_FORMAT_R32G32B32_FLOAT:
		case DXGI_FORMAT_R32G32B32_UINT:
		case DXGI_FORMAT_R32G32B32_SINT:
			componentSize = 4u;
			componentCount = 3u;
			break;
		case DXGI_FORMAT_R16G16B16A16_FLOAT:
		case DXGI_FORMAT_R16G16B16A16_UNORM:
		case DXGI_FORMAT_R16G16B16A16_UINT:
		case DXGI_FORMAT_R16G16B16A16_SNORM:
		case DXGI_FORMAT_R16G16B16A16_SINT:
			componentSize = 2u;
			componentCount = 4u;
			break;
		case DXGI_FORMAT_R32G32_FLOAT:
		case DXGI_FORMAT_R32G32_UINT:
		case DXGI_FORMAT_R32G32_SINT:
			componentSize = 4u;
			componentCount = 2u;
			break;
		case DXGI_FORMAT_R8G8B8A8_UNORM:
		case DXGI_FORMAT_R8G8B8A8_UINT:
		case DXGI_FORMAT_R8G8B8A8_SNORM:
		case DXGI_FORMAT_R8G8B8A8_SINT:
			componentSize = 1u;
			componentCount = 4u;
			break;
		case DXGI_FORMAT_R16G16_FLOAT:
		case DXGI_FORMAT_R16G16_UNORM:
		case DXGI_FORMAT_R16G16_UINT:
		case DXGI_FORMAT_R16G16_SNORM:
		case DXGI_FORMAT_R16G16_SINT:
			componentSize = 2u;
			componentCount = 2u;
			break;
		case DXGI_FORMAT_R32_FLOAT:
		case DXGI_FORMAT_R32_UINT:
		case DXGI_FORMAT_R32_SINT:
			componentSize = 4u;
			componentCount = 1u;
			break;
		case DXGI_FORMAT_R8G8_UNORM:
		case DXGI_FORMAT_R8G8_UINT:
		case DXGI_FORMAT_R8G8_SNORM:
		case DXGI_FORMAT_R8G8_SINT:
			componentSize = 1u;
			componentCount = 2u;
			break;
		case DXGI_FORMAT_R16_FLOAT:
		case DXGI_FORMAT_R16_UINT:
		case DXGI_FORMAT_R16_SNORM:
		case DXGI_FORMAT_R16_SINT:
			componentSize = 2u;
			componentCount = 1u;
			break;
		case DXGI_FORMAT_R8_UNORM:
		case DXGI_FORMAT_R8_UINT:
		case DXGI_FORMAT_R8_SNORM:
		case DXGI_FORMAT_R8_SINT:
			componentSize = 1u;
			componentCount = 1u;
			break;
		default: [[unlikely]]
			assert(false && "Incorrect vertex format");
			componentSize = 0u;
			componentCount = 0u;
			break;
		}
	}

	constexpr void GetIndexFormatInfo(const DXGI_FORMAT format, UINT& indexSize) noexcept
	{
		switch (format)
		{
		case DXGI_FORMAT_R16_UINT:
			indexSize = 2u;
			break;
		case DXGI_FORMAT_R32_UINT:
			indexSize = 4u;
			break;
		default: [[unlikely]]
			assert(false && "Incorrect index format");
			indexSize = 0u;
			break;
		}
	}

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
