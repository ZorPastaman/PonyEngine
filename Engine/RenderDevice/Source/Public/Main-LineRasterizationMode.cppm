/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:LineRasterizationMode;

import std;

export namespace PonyEngine::RenderDevice
{
	enum class LineRasterizationMode : std::uint8_t
	{
		Aliased,
		AlphaAntialiased,
		QuadrilateralWide,
		QuadrilateralNarrow
	};
}
