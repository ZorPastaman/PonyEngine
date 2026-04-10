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

export module PonyEngine.RenderDevice:ResolveMode;

import std;

export namespace PonyEngine::RenderDevice
{
	/// @brief Resolve mode.
	enum class ResolveMode : std::uint8_t
	{
		Average,
		Minimum,
		Maximum
	};
}

namespace PonyEngine::RenderDevice
{
	/// @brief Resolve mode names.
	constexpr std::array<std::string_view, 3> ResolveModeNames
	{
		"Average",
		"Minimum",
		"Maximum"
	};
}

export
{
	PONY_ENUM_VALUE_FORMATTER(PonyEngine::RenderDevice::ResolveMode, PonyEngine::RenderDevice::ResolveModeNames)
}
