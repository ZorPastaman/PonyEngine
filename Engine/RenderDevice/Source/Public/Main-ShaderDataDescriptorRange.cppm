/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:ShaderDataDescriptorRange;

import std;

import :ShaderDataDescriptorType;

export namespace PonyEngine::RenderDevice
{
	struct ShaderDataDescriptorRange final
	{
		ShaderDataDescriptorType type = ShaderDataDescriptorType::ConstantBuffer;
		std::uint32_t baseShaderRegister = 0u;
		std::uint32_t count = 1u;
	};
}
