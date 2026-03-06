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

export module PonyEngine.RenderDevice:ResourceAccess;

import std;

export namespace PonyEngine::RenderDevice
{
	/// @brief Resource access.
	enum class ResourceAccess : std::uint8_t
	{
		ConstantBuffer,
		ShaderResource,
		UnorderedAccess,
		RenderTarget,
		DepthStencilRead,
		DepthStencilWrite,
		CopySource,
		CopyDestination,
		ResolveSource,
		ResolveDestination
	};

	/// @brief Resource access mask.
	enum class ResourceAccessMask : std::uint16_t
	{
		None = 0,
		ConstantBuffer = 1 << 0,
		ShaderResource = 1 << 1,
		UnorderedAccess = 1 << 2,
		RenderTarget = 1 << 3,
		DepthStencilRead = 1 << 4,
		DepthStencilWrite = 1 << 5,
		CopySource = 1 << 6,
		CopyDestination = 1 << 7,
		ResolveSource = 1 << 8,
		ResolveDestination = 1 << 9,
		All = (1 << 10) - 1
	};

	PONY_ENUM_VALUE_MASK_FEATURES(ResourceAccess, ResourceAccessMask)
}

namespace PonyEngine::RenderDevice
{
	/// @brief Resource access names.
	constexpr std::array<std::string_view, 10> ResourceAccessNames
	{
		"ConstantBuffer",
		"ShaderResource",
		"UnorderedAccess",
		"RenderTarget",
		"DepthStencilRead",
		"DepthStencilWrite",
		"CopySource",
		"CopyDestination",
		"ResolveSource",
		"ResolveDestination"
	};
}

export
{
	PONY_ENUM_VALUE_MASK_FORMATTER(PonyEngine::RenderDevice::ResourceAccess, PonyEngine::RenderDevice::ResourceAccessMask, PonyEngine::RenderDevice::ResourceAccessNames)
}
