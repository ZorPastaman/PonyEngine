/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:TextureParams;

import std;

import PonyEngine.Math;

import :ClearValue;
import :ResourceLayout;
import :SampleCount;
import :TextureFlag;
import :TextureFormatID;
import :TextureDimension;
import :TextureUsage;

export namespace PonyEngine::RenderDevice
{
	/// @brief Texture parameters.
	struct TextureParams final
	{
		TextureFormatID format; ///< Texture format.
		std::span<const TextureFormatID> castableFormats; ///< Castable formats.
		Math::Vector3<std::uint32_t> size = Math::Vector3<std::uint32_t>(1u); ///< Texture size.
		ClearValue clearValue; ///< Clear value.
		std::uint16_t arraySize = 1u; ///< Array size.
		std::uint8_t mipCount = 1u; ///< Mip count.
		TextureDimension dimension = TextureDimension::Texture2D; ///< Texture dimension.
		SampleCount sampleCount = SampleCount::X1; ///< Sample count.
		TextureUsage usage = TextureUsage::ShaderResource; ///< Texture usages.
		ResourceLayout initialLayout = ResourceLayout::Common; ///< Texture initial layout.
		TextureFlag flags = TextureFlag::None; ///< Texture flags.
	};
}
