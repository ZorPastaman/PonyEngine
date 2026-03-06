/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Type/Enum.h"

export module PonyEngine.RenderDevice:ShaderDataDescriptorType;

import std;

export namespace PonyEngine::RenderDevice
{
	/// @brief Shader data descriptor type.
	enum class ShaderDataDescriptorType : std::uint8_t
	{
		ConstantBuffer,
		BufferShaderResource,
		TextureShaderResource,
		BufferUnorderedAccess,
		TextureUnorderedAccess
	};
}

namespace PonyEngine::RenderDevice
{
	/// @brief Shader data descriptor type names.
	constexpr std::array<std::string_view, 5> ShaderDataDescriptorTypeNames
	{
		"ConstantBuffer",
		"BufferShaderResource",
		"TextureShaderResource",
		"BufferUnorderedAccess",
		"TextureUnorderedAccess"
	};
}

export 
{
	PONY_ENUM_VALUE_FORMATTER(PonyEngine::RenderDevice::ShaderDataDescriptorType, PonyEngine::RenderDevice::ShaderDataDescriptorTypeNames)
}
