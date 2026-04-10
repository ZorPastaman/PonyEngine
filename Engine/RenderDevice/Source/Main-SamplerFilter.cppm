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
	/// @brief Basic sampler filter.
	struct BasicSamplerFilter final
	{
		Filter min = Filter::Linear; ///< Minification filter.
		Filter mag = Filter::Linear; ///< Magnification filter.
		Filter mip = Filter::Linear; ///< Mip filter.
		Reduction reduction; ///< Reduction.
	};

	/// @brief Anisotropic sampler filter.
	struct AnisotropicSamplerFilter final
	{
		float maxAnisotropy = 1.f; ///< Maximum anisotropy.
		Reduction reduction; ///< Reduction.
	};

	using SamplerFilter = std::variant<BasicSamplerFilter, AnisotropicSamplerFilter>; ///< Sampler filter.
}
