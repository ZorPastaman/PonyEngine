/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:DepthBias;

export namespace PonyEngine::RenderDevice
{
	struct DepthBias final
	{
		float depthBias = 0.f;
		float depthBiasClamp = 0.f;
		float slopeScaledDepthBias = 0.f;
	};
}
