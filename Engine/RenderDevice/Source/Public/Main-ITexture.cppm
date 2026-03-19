/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Object/Body.h"

export module PonyEngine.RenderDevice:ITexture;

import std;

import PonyEngine.Math;

import :IResource;
import :SampleCount;
import :SubTextureIndex;
import :TextureDimension;
import :TextureFormatId;
import :TextureUsage;

export namespace PonyEngine::RenderDevice
{
	/// @brief Texture.
	class ITexture : public IResource
	{
		PONY_INTERFACE_BODY(ITexture)

		/// @brief Gets the dimension.
		/// @return Dimension.
		[[nodiscard("Pure function")]]
		virtual TextureDimension Dimension() const noexcept = 0;
		/// @brief Gets the format.
		/// @return Format.
		[[nodiscard("Pure function")]]
		virtual TextureFormatId Format() const noexcept = 0;
		/// @brief Gets the castable formats.
		/// @return Castable formats.
		[[nodiscard("Pure function")]]
		virtual std::span<const TextureFormatId> CastableFormats() const noexcept = 0;
		/// @brief Gets the texture size.
		/// @return Size.
		[[nodiscard("Pure function")]]
		virtual Math::Vector3<std::uint32_t> Size() const noexcept = 0;
		/// @brief Gets the mip count.
		/// @return Mip count.
		[[nodiscard("Pure function")]]
		virtual std::uint8_t MipCount() const noexcept = 0;
		/// @brief Gets the array size.
		/// @return Array size.
		[[nodiscard("Pure function")]]
		virtual std::uint16_t ArraySize() const noexcept = 0;
		/// @brief Gets the sample count.
		/// @return Sample count.
		[[nodiscard("Pure function")]]
		virtual SampleCount SampleCount() const noexcept = 0;
		/// @brief Gets the texture usage.
		/// @return Usage.
		[[nodiscard("Pure function")]]
		virtual TextureUsage Usage() const noexcept = 0;
		/// @brief Checks if the texture is srgb compatible.
		/// @return @a True if it's compatible; @a false otherwise.
		[[nodiscard("Pure function")]]
		virtual bool SRGBCompatible() const noexcept = 0;
	};
}
