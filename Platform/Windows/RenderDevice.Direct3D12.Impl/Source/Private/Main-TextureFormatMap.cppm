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
	/// @brief Texture format map.
	class TextureFormatMap final
	{
	public:
		/// @brief Creates a texture format map.
		/// @param renderDevice Render device context.
		[[nodiscard("Pure constructor")]]
		explicit TextureFormatMap(IRenderDeviceContext& renderDevice);
		TextureFormatMap(const TextureFormatMap&) = delete;
		TextureFormatMap(TextureFormatMap&&) = delete;

		~TextureFormatMap() noexcept = default;

		/// @brief Gets the size.
		/// @return Size.
		[[nodiscard("Pure function")]]
		std::size_t Size() const noexcept;

		/// @brief Finds an index of the texture format ID.
		/// @param textureFormatId Texture format ID.
		/// @return Index or @p Size() if not found.
		[[nodiscard("Pure function")]]
		std::size_t IndexOf(TextureFormatID textureFormatId) const noexcept;
		/// @brief Find an index of the DXGI format.
		/// @param dxgiFormat DXGI format.
		/// @return Index or @p Size() if not found.
		[[nodiscard("Pure function")]]
		std::size_t IndexOf(DXGI_FORMAT dxgiFormat) const noexcept;

		/// @brief Gets a texture format.
		/// @param index Texture format index.
		/// @return Texture format.
		[[nodiscard("Pure function")]]
		TextureFormatID TextureFormat(std::size_t index) const noexcept;
		/// @brief Gets a DXGI format.
		/// @param index DXGI format index.
		/// @return DXGI format.
		[[nodiscard("Pure function")]]
		DXGI_FORMAT DXGIFormat(std::size_t index) const noexcept;

		TextureFormatMap& operator =(const TextureFormatMap&) = delete;
		TextureFormatMap& operator =(TextureFormatMap&&) = delete;

	private:
		std::array<TextureFormatID, MainFormatMap.MapSize()> textureFormatIds; ///< Texture format IDs.
		std::array<DXGI_FORMAT, MainFormatMap.MapSize()> dxgiFormats; ///< DXGI formats.
	};
}

namespace PonyEngine::RenderDevice::Direct3D12::Windows
{
	TextureFormatMap::TextureFormatMap(IRenderDeviceContext& renderDevice)
	{
		for (std::size_t i = 0uz; i < MainFormatMap.MapSize(); ++i)
		{
			textureFormatIds[i] = renderDevice.TextureFormatID(MainFormatMap.GetEngineFormat(i));
			dxgiFormats[i] = MainFormatMap.GetFormat(i);
		}
	}

	std::size_t TextureFormatMap::Size() const noexcept
	{
		return textureFormatIds.size();
	}

	std::size_t TextureFormatMap::IndexOf(const TextureFormatID textureFormatId) const noexcept
	{
		return std::ranges::find(textureFormatIds, textureFormatId) - textureFormatIds.cbegin();
	}

	std::size_t TextureFormatMap::IndexOf(const DXGI_FORMAT dxgiFormat) const noexcept
	{
		return std::ranges::find(dxgiFormats, dxgiFormat) - dxgiFormats.cbegin();
	}

	TextureFormatID TextureFormatMap::TextureFormat(const std::size_t index) const noexcept
	{
		return textureFormatIds[index];
	}

	DXGI_FORMAT TextureFormatMap::DXGIFormat(const std::size_t index) const noexcept
	{
		return dxgiFormats[index];
	}
}
