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

export module PonyEngine.RenderDevice:ComponentSwizzle;

import std;

export namespace PonyEngine::RenderDevice
{
	/// @brief Component swizzle. It sets what data a shader will get in a channel.
	enum class ComponentSwizzle : std::uint8_t
	{
		Red,
		Green,
		Blue,
		Alpha,
		Zero,
		One
	};
}

namespace PonyEngine::RenderDevice
{
	/// @brief Component swizzle names.
	constexpr std::array<std::string_view, 6> ComponentSwizzleNames
	{
		"Red",
		"Green",
		"Blue",
		"Alpha",
		"Zero",
		"One"
	};
}

export
{
	PONY_ENUM_VALUE_FORMATTER(PonyEngine::RenderDevice::ComponentSwizzle, PonyEngine::RenderDevice::ComponentSwizzleNames)
}
