/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:SamplerSupport;

export namespace PonyEngine::RenderDevice
{
	struct SamplerSupport final
	{
		float maxAnisotropy = 0.f;
	};
}
