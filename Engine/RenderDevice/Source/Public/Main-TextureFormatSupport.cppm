/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:TextureFormatSupport;

import std;

import :TextureFormatFeature;

export namespace PonyEngine::RenderDevice
{
	struct TextureFormatSupport final
	{
		TextureFormatFeature features = TextureFormatFeature::None;
		std::uint8_t planeCount = 0u;
		bool supported = false;
	};
}
