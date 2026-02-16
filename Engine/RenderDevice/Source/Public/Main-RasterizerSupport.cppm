/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:RasterizerSupport;

import :LineRasterizationMode;

export namespace PonyEngine::RenderDevice
{
	struct RasterizerSupport final
	{
		LineRasterizationModeMask lineRasterizationModes = LineRasterizationModeMask::None;
		bool conservativeRasterization = false;
	};
}
