/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:StaticSamplerParams;

import std;

import :SamplerParams;

export namespace PonyEngine::RenderDevice
{
	/// @brief Static sampler parameters.
	struct StaticSamplerParams final
	{
		SamplerParams samplerParams; ///< Sampler parameters.
		std::uint32_t shaderRegister = 0u; ///< Shader register.
	};
}
