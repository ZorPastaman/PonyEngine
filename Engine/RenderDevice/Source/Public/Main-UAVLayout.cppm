/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:UAVLayout;

import std;

import :SubTextureRange;

export namespace PonyEngine::RenderDevice
{
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
}
