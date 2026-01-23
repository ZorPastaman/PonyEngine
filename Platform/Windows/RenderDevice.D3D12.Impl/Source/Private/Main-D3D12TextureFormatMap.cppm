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

export module PonyEngine.RenderDevice.D3D12.Impl.Windows:D3D12TextureFormatMap;

import std;

import PonyEngine.RenderDevice.Ext;

import :D3D12FormatUtility;

export namespace PonyEngine::RenderDevice::Windows
{
	class D3D12TextureFormatMap final
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit D3D12TextureFormatMap(IRenderDeviceContext& renderDevice);
		D3D12TextureFormatMap(const D3D12TextureFormatMap&) = delete;
		D3D12TextureFormatMap(D3D12TextureFormatMap&&) = delete;

		~D3D12TextureFormatMap() noexcept = default;

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

		D3D12TextureFormatMap& operator =(const D3D12TextureFormatMap&) = delete;
		D3D12TextureFormatMap& operator =(D3D12TextureFormatMap&&) = delete;

	private:
		void Bind(std::string_view textureFormat, DXGI_FORMAT dxgiFormat, IRenderDeviceContext& renderDevice);

		std::vector<TextureFormatId> textureFormatIds;
		std::vector<DXGI_FORMAT> dxgiFormats;
	};
}

namespace PonyEngine::RenderDevice::Windows
{
	D3D12TextureFormatMap::D3D12TextureFormatMap(IRenderDeviceContext& renderDevice)
	{
		for (std::size_t i = 0uz; i < MainFormatMap.MapSize(); ++i)
		{
			Bind(MainFormatMap.GetEngineFormat(i), MainFormatMap.GetFormat(i), renderDevice);
		}
	}

	std::size_t D3D12TextureFormatMap::Size() const noexcept
	{
		return textureFormatIds.size();
	}

	std::size_t D3D12TextureFormatMap::IndexOf(const TextureFormatId textureFormatId) const noexcept
	{
		return std::ranges::find(textureFormatIds, textureFormatId) - textureFormatIds.cbegin();
	}

	std::size_t D3D12TextureFormatMap::IndexOf(const DXGI_FORMAT dxgiFormat) const noexcept
	{
		return std::ranges::find(dxgiFormats, dxgiFormat) - dxgiFormats.cbegin();
	}

	TextureFormatId D3D12TextureFormatMap::TextureFormat(const std::size_t index) const noexcept
	{
		return textureFormatIds[index];
	}

	DXGI_FORMAT D3D12TextureFormatMap::DXGIFormat(const std::size_t index) const noexcept
	{
		return dxgiFormats[index];
	}

	void D3D12TextureFormatMap::Bind(const std::string_view textureFormat, const DXGI_FORMAT dxgiFormat, IRenderDeviceContext& renderDevice)
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
