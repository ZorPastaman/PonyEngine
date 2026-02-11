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

export module PonyEngine.RenderDevice.Direct3D12.Impl.Windows:TextureFormatMap;

import std;

import PonyEngine.RenderDevice.Ext;

import :FormatUtility;

export namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	class TextureFormatMap final
	{
	public:
		[[nodiscard("Pure constructor")]]
		explicit TextureFormatMap(IRenderDeviceContext& renderDevice);
		TextureFormatMap(const TextureFormatMap&) = delete;
		TextureFormatMap(TextureFormatMap&&) = delete;

		~TextureFormatMap() noexcept = default;

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

		TextureFormatMap& operator =(const TextureFormatMap&) = delete;
		TextureFormatMap& operator =(TextureFormatMap&&) = delete;

	private:
		void Bind(std::string_view textureFormat, DXGI_FORMAT dxgiFormat, IRenderDeviceContext& renderDevice);

		std::vector<TextureFormatId> textureFormatIds;
		std::vector<DXGI_FORMAT> dxgiFormats;
	};
}

namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	TextureFormatMap::TextureFormatMap(IRenderDeviceContext& renderDevice)
	{
		for (std::size_t i = 0uz; i < MainFormatMap.MapSize(); ++i)
		{
			Bind(MainFormatMap.GetEngineFormat(i), MainFormatMap.GetFormat(i), renderDevice);
		}
	}

	std::size_t TextureFormatMap::Size() const noexcept
	{
		return textureFormatIds.size();
	}

	std::size_t TextureFormatMap::IndexOf(const TextureFormatId textureFormatId) const noexcept
	{
		return std::ranges::find(textureFormatIds, textureFormatId) - textureFormatIds.cbegin();
	}

	std::size_t TextureFormatMap::IndexOf(const DXGI_FORMAT dxgiFormat) const noexcept
	{
		return std::ranges::find(dxgiFormats, dxgiFormat) - dxgiFormats.cbegin();
	}

	TextureFormatId TextureFormatMap::TextureFormat(const std::size_t index) const noexcept
	{
		return textureFormatIds[index];
	}

	DXGI_FORMAT TextureFormatMap::DXGIFormat(const std::size_t index) const noexcept
	{
		return dxgiFormats[index];
	}

	void TextureFormatMap::Bind(const std::string_view textureFormat, const DXGI_FORMAT dxgiFormat, IRenderDeviceContext& renderDevice)
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
