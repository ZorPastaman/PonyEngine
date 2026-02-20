/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:RasterRegion;

import std;

import PonyEngine.Math;

import :DepthRange;

export namespace PonyEngine::RenderDevice
{
	struct RasterRegion final
	{
		Math::CornerRect<float> viewport;
		DepthRange depthRange;
		Math::CornerRect<std::uint32_t> scissor;
	};
}
