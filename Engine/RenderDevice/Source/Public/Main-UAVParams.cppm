/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:UAVParams;

import std;

import :Aspect;
import :TextureDimension;
import :TextureFormatId;
import :UAVLayout;

export namespace PonyEngine::RenderDevice
{
	struct BufferUAVParams final
	{
		std::uint64_t firstElementIndex = 0ull;
		std::uint32_t elementCount = 0u;
		std::uint32_t stride = 0u;
	};

	struct TextureUAVParams final
	{
		TextureFormatId format;
		TextureDimension dimension = TextureDimension::Texture2D;
		Aspect aspect = Aspect::Color;
		TextureUAVLayout layout;
	};
}
