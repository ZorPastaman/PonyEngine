/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:TextureCreateInfo;

import std;

import PonyEngine.Math;

import :ClearValue;
import :Layout;
import :SampleCount;
import :TextureFormatId;
import :TextureDimension;
import :TextureUsage;

export namespace PonyEngine::Render
{
	struct TextureCreateInfo final
	{
		TextureFormatId format;
		std::span<const TextureFormatId> castableFormats;
		Math::Vector3<std::uint32_t> size = Math::Vector3<std::uint32_t>(1u);
		std::uint32_t mipCount = 1u;
		std::uint32_t arraySize = 1u;
		ClearValue clearValue;
		TextureDimension dimension = TextureDimension::Texture2D;
		SampleCount sampleCount = SampleCount::X1;
		TextureUsage usage = TextureUsage::ShaderResource;
		Layout initialLayout = Layout::Common;
	};
}
