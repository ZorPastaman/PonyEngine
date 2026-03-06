/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:SamplerDescriptorRange;

import std;

export namespace PonyEngine::RenderDevice
{
	/// @brief Sampler descriptor range.
	struct SamplerDescriptorRange final
	{
		std::uint32_t firstShaderRegister = 0u; ///< First shader register.
		std::uint32_t shaderRegisterCount = 1u; ///< Shader register count.
	};
}
