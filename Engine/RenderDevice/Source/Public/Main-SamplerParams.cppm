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
		SamplerAddressMode addressU;
		SamplerAddressMode addressV;
		SamplerAddressMode addressW;
		float mipLodBias;
		float minLod;
		float maxLod;
	};
}
