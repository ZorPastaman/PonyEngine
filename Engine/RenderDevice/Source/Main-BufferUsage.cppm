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

export module PonyEngine.RenderDevice:BufferUsage;

import std;

export namespace PonyEngine::RenderDevice
{
	/// @brief Buffer usage.
	enum class BufferUsage : std::uint8_t
	{
		None = 0,
		ShaderResource = 1 << 0,
		UnorderedAccess = 1 << 1,
		All = (1 << 2) - 1
	};

	PONY_ENUM_MASK_FEATURES(BufferUsage)
}

namespace PonyEngine::RenderDevice
{
	/// @brief Buffer usage names.
	constexpr std::array<std::string_view, 2> BufferUsageNames
	{
		"ShaderResource",
		"UnorderedAccess"
	};
}

export
{
	PONY_ENUM_MASK_FORMATTER(PonyEngine::RenderDevice::BufferUsage, PonyEngine::RenderDevice::BufferUsageNames)
}
