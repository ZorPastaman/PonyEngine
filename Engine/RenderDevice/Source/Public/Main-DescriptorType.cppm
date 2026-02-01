/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

export module PonyEngine.RenderDevice:DescriptorType;

import std;

export namespace PonyEngine::RenderDevice
{
	enum class DescriptorType : std::uint8_t
	{
		ConstantBuffer,
		BufferShaderResource,
		TextureShaderResource,
		BufferUnorderedAccess,
		TextureUnorderedAccess,
		Sampler
	};
}
