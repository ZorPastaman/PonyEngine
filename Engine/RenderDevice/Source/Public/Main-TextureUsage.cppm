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

export module PonyEngine.RenderDevice:TextureUsage;

import std;

export namespace PonyEngine::RenderDevice
{
	/// @brief Texture usages.
	enum class TextureUsage : std::uint8_t
	{
		None = 0,
		ShaderResource = 1 << 0,
		UnorderedAccess = 1 << 1,
		RenderTarget = 1 << 2,
		DepthStencil = 1 << 3,
		All = (1 << 4) - 1
	};

	PONY_ENUM_MASK_FEATURES(TextureUsage)
}

namespace PonyEngine::RenderDevice
{
	/// @brief Texture usage names.
	constexpr std::array<std::string_view, 4> TextureUsageNames
	{
		"ShaderResource",
		"UnorderedAccess",
		"RenderTarget",
		"DepthStencil"
	};
}

export
{
	PONY_ENUM_MASK_FORMATTER(PonyEngine::RenderDevice::TextureUsage, PonyEngine::RenderDevice::TextureUsageNames)
}
