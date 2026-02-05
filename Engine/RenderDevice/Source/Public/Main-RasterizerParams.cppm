/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:RasterizerParams;

import std;

import :CullMode;
import :FillMode;
import :LineRasterizationMode;

export namespace PonyEngine::RenderDevice
{
	struct RasterizerParams final
	{
		FillMode fillMode = FillMode::Solid;
		CullMode cullMode = CullMode::Back;
		bool counterClockwiseFrontFace = false;
		bool depthClipping = true;
		float depthBias = 0.f;
		float depthBiasClamp = 0.f;
		float slopeScaledDepthBias = 0.f;
		LineRasterizationMode lineRasterizationMode = LineRasterizationMode::Aliased;
		bool conservativeRasterization = false;
	};
}
