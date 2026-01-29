/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:SamplerFilter;

import std;

import :Filter;
import :Reduction;

export namespace PonyEngine::RenderDevice
{
	struct BasicSamplerFilter final
	{
		Filter min = Filter::Linear;
		Filter mag = Filter::Linear;
		Filter mip = Filter::Linear;
		Reduction reduction;
	};

	struct AnisotropicSamplerFilter final
	{
		float maxAnisotropy = 1.f;
		Reduction reduction;
	};

	using SamplerFilter = std::variant<BasicSamplerFilter, AnisotropicSamplerFilter>;
}
