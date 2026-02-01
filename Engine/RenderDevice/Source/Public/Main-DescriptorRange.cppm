/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:DescriptorRange;

import std;

import :DescriptorType;

export namespace PonyEngine::RenderDevice
{
	struct DescriptorRange final
	{
		DescriptorType type = DescriptorType::ConstantBuffer;
		std::uint32_t baseShaderRegister = 0u;
		std::uint32_t count = 1u;
	};
}
