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

import :Aspect;
import :TextureFormatFeature;

export namespace PonyEngine::RenderDevice
{
	struct TextureFormatSupport final
	{
		TextureFormatFeature features = TextureFormatFeature::None;
		AspectMask aspects = AspectMask::None;
		bool supported = false;
	};
}
