/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:DepthStencil;

import std;

export namespace PonyEngine::Render
{
	struct DepthStencil final
	{
		float depth = 1.f;
		std::uint8_t stencil = 0u;
	};
}
