/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:SRVParams;

import std;

import :Aspect;
import :ComponentMapping;
import :SRVLayout;
import :TextureFormatId;
import :TextureViewDimension;

export namespace PonyEngine::RenderDevice
{
	struct BufferSRVParams final
	{
		std::uint64_t firstElementIndex = 0ull;
		std::uint32_t elementCount = 0u;
		std::uint32_t stride = 0u;
		bool raw = false;
	};

	struct TextureSRVParams final
	{
		TextureFormatId format;
		bool srgb = false;
		TextureViewDimension dimension = TextureViewDimension::Texture2D;
		Aspect aspect = Aspect::Color;
		ComponentMapping mapping;
		TextureSRVLayout layout;
	};
}
