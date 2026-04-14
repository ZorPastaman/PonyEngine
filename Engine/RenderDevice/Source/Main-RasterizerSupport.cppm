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
	/// @brief Rasterizer support.
	struct RasterizerSupport final
	{
		std::uint8_t simultaneousTargetCount = 0u; ///< How many RTVs can be bound at the same time?
		std::uint8_t maxRasterRegionCount = 0u; ///< How many raster regions can be set at the same time?
		LineRasterizationModeMask lineRasterizationModes = LineRasterizationModeMask::None; ///< Supported line rasterization modes.
		bool conservativeRasterization = false; ///< Is conservative rasterization supported?
	};
}
