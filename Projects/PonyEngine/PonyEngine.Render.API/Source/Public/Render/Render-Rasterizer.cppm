/***************************************************
* MIT License                                     *
*                                                 *
* Copyright (c) 2023-present Vladimir Popov       *
*                                                 *
* Email: zor1994@gmail.com                        *
* Repo: https://github.com/ZorPastaman/PonyEngine *
***************************************************/

export module PonyEngine.Render:Rasterizer;

import :CullMode;
import :FillMode;

export namespace PonyEngine::Render
{
	struct Rasterizer final
	{
		FillMode fillMode = FillMode::Solid;
		CullMode cullMode = CullMode::Back;
		std::int32_t depthBias = 0;
		float depthBiasClamp = 0.f;
		float slopeScaledDepthBias = 0.f;
		bool depthClip = true;
	};
}
