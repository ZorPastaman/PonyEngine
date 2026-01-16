/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/RenderDevice/Windows/DXGIFramework.h"

export module PonyEngine.RenderDevice.D3D12.Impl.Windows:DXGITextureFormatMap;

import std;

import PonyEngine.RenderDevice.Ext;

export namespace PonyEngine::RenderDevice::Windows
{
	class DXGITextureFormatMap final
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit DXGITextureFormatMap(IRenderDeviceContext& renderDevice);
		DXGITextureFormatMap(const DXGITextureFormatMap&) = delete;
		DXGITextureFormatMap(DXGITextureFormatMap&&) = delete;

		~DXGITextureFormatMap() noexcept = default;

		[[nodiscard("Pure function")]]
		std::size_t Size() const noexcept;

		[[nodiscard("Pure function")]]
		std::size_t IndexOf(TextureFormatId textureFormatId) const noexcept;
		[[nodiscard("Pure function")]]
		std::size_t IndexOf(DXGI_FORMAT dxgiFormat) const noexcept;

		[[nodiscard("Pure function")]]
		TextureFormatId TextureFormat(std::size_t index) const noexcept;
		[[nodiscard("Pure function")]]
		DXGI_FORMAT DXGIFormat(std::size_t index) const noexcept;

		DXGITextureFormatMap& operator =(const DXGITextureFormatMap&) = delete;
		DXGITextureFormatMap& operator =(DXGITextureFormatMap&&) = delete;

	private:
		void Bind(std::string_view textureFormat, DXGI_FORMAT dxgiFormat, IRenderDeviceContext& renderDevice);

		std::vector<TextureFormatId> textureFormatIds;
		std::vector<DXGI_FORMAT> dxgiFormats;
	};
}

namespace PonyEngine::RenderDevice::Windows
{
	DXGITextureFormatMap::DXGITextureFormatMap(IRenderDeviceContext& renderDevice)
	{
		Bind(TextureFormat::R32G32B32A32_Float, DXGI_FORMAT_R32G32B32A32_FLOAT, renderDevice);
		Bind(TextureFormat::R32G32B32A32_Uint, DXGI_FORMAT_R32G32B32A32_UINT, renderDevice);
		Bind(TextureFormat::R32G32B32A32_Sint, DXGI_FORMAT_R32G32B32A32_SINT, renderDevice);

		Bind(TextureFormat::R32G32B32_Float, DXGI_FORMAT_R32G32B32_FLOAT, renderDevice);
		Bind(TextureFormat::R32G32B32_Uint, DXGI_FORMAT_R32G32B32_UINT, renderDevice);
		Bind(TextureFormat::R32G32B32_Sint, DXGI_FORMAT_R32G32B32_SINT, renderDevice);

		Bind(TextureFormat::R32G32_Float, DXGI_FORMAT_R32G32_FLOAT, renderDevice);
		Bind(TextureFormat::R32G32_Uint, DXGI_FORMAT_R32G32_UINT, renderDevice);
		Bind(TextureFormat::R32G32_Sint, DXGI_FORMAT_R32G32_SINT, renderDevice);

		Bind(TextureFormat::D32_Float_S8X24_Uint, DXGI_FORMAT_D32_FLOAT_S8X24_UINT, renderDevice);
		Bind(TextureFormat::D32_Float, DXGI_FORMAT_D32_FLOAT, renderDevice);

		Bind(TextureFormat::R32_Float, DXGI_FORMAT_R32_FLOAT, renderDevice);
		Bind(TextureFormat::R32_Uint, DXGI_FORMAT_R32_UINT, renderDevice);
		Bind(TextureFormat::R32_Sint, DXGI_FORMAT_R32_SINT, renderDevice);

		Bind(TextureFormat::D24_Unorm_S8_Uint, DXGI_FORMAT_D24_UNORM_S8_UINT, renderDevice);

		Bind(TextureFormat::R16G16B16A16_Float, DXGI_FORMAT_R16G16B16A16_FLOAT, renderDevice);
		Bind(TextureFormat::R16G16B16A16_Unorm, DXGI_FORMAT_R16G16B16A16_UNORM, renderDevice);
		Bind(TextureFormat::R16G16B16A16_Uint, DXGI_FORMAT_R16G16B16A16_UINT, renderDevice);
		Bind(TextureFormat::R16G16B16A16_Snorm, DXGI_FORMAT_R16G16B16A16_SNORM, renderDevice);
		Bind(TextureFormat::R16G16B16A16_Sint, DXGI_FORMAT_R16G16B16A16_SINT, renderDevice);

		Bind(TextureFormat::R16G16_Float, DXGI_FORMAT_R16G16_FLOAT, renderDevice);
		Bind(TextureFormat::R16G16_Unorm, DXGI_FORMAT_R16G16_UNORM, renderDevice);
		Bind(TextureFormat::R16G16_Uint, DXGI_FORMAT_R16G16_UINT, renderDevice);
		Bind(TextureFormat::R16G16_Snorm, DXGI_FORMAT_R16G16_SNORM, renderDevice);
		Bind(TextureFormat::R16G16_Sint, DXGI_FORMAT_R16G16_SINT, renderDevice);

		Bind(TextureFormat::D16_Unorm, DXGI_FORMAT_D16_UNORM, renderDevice);

		Bind(TextureFormat::R16_Float, DXGI_FORMAT_R16_FLOAT, renderDevice);
		Bind(TextureFormat::R16_Unorm, DXGI_FORMAT_R16_UNORM, renderDevice);
		Bind(TextureFormat::R16_Uint, DXGI_FORMAT_R16_UINT, renderDevice);
		Bind(TextureFormat::R16_Snorm, DXGI_FORMAT_R16_SNORM, renderDevice);
		Bind(TextureFormat::R16_Sint, DXGI_FORMAT_R16_SINT, renderDevice);

		Bind(TextureFormat::R11G11B10_Float, DXGI_FORMAT_R11G11B10_FLOAT, renderDevice);

		Bind(TextureFormat::R10G10B10A2_Unorm, DXGI_FORMAT_R10G10B10A2_UNORM, renderDevice);
		Bind(TextureFormat::R10G10B10A2_Uint, DXGI_FORMAT_R10G10B10A2_UINT, renderDevice);

		Bind(TextureFormat::R9G9B9E5_SharedExp, DXGI_FORMAT_R9G9B9E5_SHAREDEXP, renderDevice);

		Bind(TextureFormat::R8G8B8A8_Unorm, DXGI_FORMAT_R8G8B8A8_UNORM, renderDevice);
		Bind(TextureFormat::R8G8B8A8_Uint, DXGI_FORMAT_R8G8B8A8_UINT, renderDevice);
		Bind(TextureFormat::R8G8B8A8_Snorm, DXGI_FORMAT_R8G8B8A8_SNORM, renderDevice);
		Bind(TextureFormat::R8G8B8A8_Sint, DXGI_FORMAT_R8G8B8A8_SINT, renderDevice);

		Bind(TextureFormat::R8G8_Unorm, DXGI_FORMAT_R8G8_UNORM, renderDevice);
		Bind(TextureFormat::R8G8_Uint, DXGI_FORMAT_R8G8_UINT, renderDevice);
		Bind(TextureFormat::R8G8_Snorm, DXGI_FORMAT_R8G8_SNORM, renderDevice);
		Bind(TextureFormat::R8G8_Sint, DXGI_FORMAT_R8G8_SINT, renderDevice);

		Bind(TextureFormat::R8_Unorm, DXGI_FORMAT_R8_UNORM, renderDevice);
		Bind(TextureFormat::R8_Uint, DXGI_FORMAT_R8_UINT, renderDevice);
		Bind(TextureFormat::R8_Snorm, DXGI_FORMAT_R8_SNORM, renderDevice);
		Bind(TextureFormat::R8_Sint, DXGI_FORMAT_R8_SINT, renderDevice);

		Bind(TextureFormat::B8G8R8A8_Unorm, DXGI_FORMAT_B8G8R8A8_UNORM, renderDevice);
		Bind(TextureFormat::B8G8R8X8_Unorm, DXGI_FORMAT_B8G8R8X8_UNORM, renderDevice);

		Bind(TextureFormat::A8_Unorm, DXGI_FORMAT_A8_UNORM, renderDevice);

		Bind(TextureFormat::B5G6R5_Unorm, DXGI_FORMAT_B5G6R5_UNORM, renderDevice);
		Bind(TextureFormat::B5G5R5A1_Unorm, DXGI_FORMAT_B5G5R5A1_UNORM, renderDevice);

		Bind(TextureFormat::BC1_Unorm, DXGI_FORMAT_BC1_UNORM, renderDevice);
		Bind(TextureFormat::BC2_Unorm, DXGI_FORMAT_BC2_UNORM, renderDevice);
		Bind(TextureFormat::BC3_Unorm, DXGI_FORMAT_BC3_UNORM, renderDevice);
		Bind(TextureFormat::BC4_Unorm, DXGI_FORMAT_BC4_UNORM, renderDevice);
		Bind(TextureFormat::BC4_Snorm, DXGI_FORMAT_BC4_SNORM, renderDevice);
		Bind(TextureFormat::BC5_Unorm, DXGI_FORMAT_BC5_UNORM, renderDevice);
		Bind(TextureFormat::BC5_Snorm, DXGI_FORMAT_BC5_SNORM, renderDevice);
		Bind(TextureFormat::BC6H_UF16, DXGI_FORMAT_BC6H_UF16, renderDevice);
		Bind(TextureFormat::BC6H_SF16, DXGI_FORMAT_BC6H_SF16, renderDevice);
		Bind(TextureFormat::BC7_Unorm, DXGI_FORMAT_BC7_UNORM, renderDevice);
	}

	std::size_t DXGITextureFormatMap::Size() const noexcept
	{
		return textureFormatIds.size();
	}

	std::size_t DXGITextureFormatMap::IndexOf(const TextureFormatId textureFormatId) const noexcept
	{
		return std::ranges::find(textureFormatIds, textureFormatId) - textureFormatIds.cbegin();
	}

	std::size_t DXGITextureFormatMap::IndexOf(const DXGI_FORMAT dxgiFormat) const noexcept
	{
		return std::ranges::find(dxgiFormats, dxgiFormat) - dxgiFormats.cbegin();
	}

	TextureFormatId DXGITextureFormatMap::TextureFormat(const std::size_t index) const noexcept
	{
		return textureFormatIds[index];
	}

	DXGI_FORMAT DXGITextureFormatMap::DXGIFormat(const std::size_t index) const noexcept
	{
		return dxgiFormats[index];
	}

	void DXGITextureFormatMap::Bind(const std::string_view textureFormat, const DXGI_FORMAT dxgiFormat, IRenderDeviceContext& renderDevice)
	{
		textureFormatIds.push_back(renderDevice.TextureFormatId(textureFormat));
		try
		{
			dxgiFormats.push_back(dxgiFormat);
		}
		catch (...)
		{
			textureFormatIds.pop_back();
			throw;
		}
	}
}
