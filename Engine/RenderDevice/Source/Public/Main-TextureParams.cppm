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
import :TextureFormatId;
import :TextureDimension;
import :TextureUsage;

export namespace PonyEngine::RenderDevice
{
	struct TextureParams final
	{
		TextureFormatId format;
		std::span<const TextureFormatId> castableFormats;
		Math::Vector3<std::uint32_t> size = Math::Vector3<std::uint32_t>(1u);
		ClearValue clearValue;
		std::uint16_t arraySize = 1u;
		std::uint8_t mipCount = 1u;
		TextureDimension dimension = TextureDimension::Texture2D;
		SampleCount sampleCount = SampleCount::X1;
		TextureUsage usage = TextureUsage::ShaderResource;
		ResourceLayout initialLayout = ResourceLayout::Common;
		TextureFlag flags = TextureFlag::None;
	};
}
