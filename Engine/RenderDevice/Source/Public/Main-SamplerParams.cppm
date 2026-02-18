/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:SamplerParams;

import std;

import :SamplerAddressMode;
import :SamplerFilter;

export namespace PonyEngine::RenderDevice
{
	struct SamplerParams final
	{
		SamplerFilter filter;
		SamplerAddressMode addressU = SamplerAddressMode::Wrap;
		SamplerAddressMode addressV = SamplerAddressMode::Wrap;
		SamplerAddressMode addressW = SamplerAddressMode::Wrap;
		float mipLodBias = 0.f;
		float minLod = 0.f;
		float maxLod = 0.f;
	};
}
