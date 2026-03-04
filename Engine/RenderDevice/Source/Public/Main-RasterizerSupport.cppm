/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:RasterizerSupport;

import std;

import :LineRasterizationMode;

export namespace PonyEngine::RenderDevice
{
	struct RasterizerSupport final
	{
		std::uint8_t simultaneousTargetCount = 0u;
		std::uint8_t maxRasterRegionCount = 0u;
		LineRasterizationModeMask lineRasterizationModes = LineRasterizationModeMask::None;
		bool conservativeRasterization = false;
	};
}
