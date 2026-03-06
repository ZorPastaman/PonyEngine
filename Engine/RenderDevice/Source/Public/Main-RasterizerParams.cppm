/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:RasterizerParams;

import :CullMode;
import :FillMode;
import :LineRasterizationMode;

export namespace PonyEngine::RenderDevice
{
	/// @brief Rasterizer parameters.
	struct RasterizerParams final
	{
		FillMode fillMode = FillMode::Solid; ///< Fill mode.
		CullMode cullMode = CullMode::Back; ///< Cull mode.
		bool counterClockwiseFrontFace = false; ///< Counter-clockwise front face if it's @a true; clockwise front face otherwise.
		bool depthClipping = true; ///< Depth clipping enable?
		LineRasterizationMode lineRasterizationMode = LineRasterizationMode::Aliased; ///< Line rasterization mode.
		bool conservativeRasterization = false; ///< Conservative rasterization enable?
	};
}
