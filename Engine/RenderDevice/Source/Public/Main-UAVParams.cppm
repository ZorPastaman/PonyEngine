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

import :SubTextureRange;
import :TextureFormatId;

export namespace PonyEngine::RenderDevice
{
	struct BufferUAVParams final
	{
		std::uint64_t firstElementIndex = 0ull;
		std::uint32_t elementCount = 0u;
		std::uint32_t stride = 0u;
		bool raw = false;
	};

	struct TextureSingleUAVLayout final
	{
		std::uint32_t mipIndex = 0u;
	};
	struct TextureArrayUAVLayout final
	{
		std::uint32_t mipIndex = 0u;
		ArrayRange arrayRange;
	};
	using TextureUAVLayout = std::variant<TextureSingleUAVLayout, TextureArrayUAVLayout>;

	struct TextureUAVParams final
	{
		TextureFormatId format;
		Aspect aspect = Aspect::Color;
		TextureUAVLayout layout;
	};
}
