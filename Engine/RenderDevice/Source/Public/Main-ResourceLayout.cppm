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

export module PonyEngine.RenderDevice:ResourceLayout;

import std;

export namespace PonyEngine::RenderDevice
{
	/// @brief Resource layout.
	enum class ResourceLayout : std::uint8_t
	{
		Common,
		Present,
		ShaderResource,
		RenderTarget,
		DepthStencilRead,
		DepthStencilWrite,
		UnorderedAccess,
		CopySource,
		CopyDestination,
		ResolveSource,
		ResolveDestination,
		Undefined
	};
}

namespace PonyEngine::RenderDevice
{
	/// @brief Resource layout names.
	constexpr std::array<std::string_view, 12> ResourceLayoutNames
	{
		"Common",
		"Present",
		"ShaderResource",
		"RenderTarget",
		"DepthStencilRead",
		"DepthStencilWrite",
		"UnorderedAccess",
		"CopySource",
		"CopyDestination",
		"ResolveSource",
		"ResolveDestination",
		"Undefined"
	};
}

export
{
	PONY_ENUM_VALUE_FORMATTER(PonyEngine::RenderDevice::ResourceLayout, PonyEngine::RenderDevice::ResourceLayoutNames)
}
