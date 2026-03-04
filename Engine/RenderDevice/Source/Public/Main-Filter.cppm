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

export module PonyEngine.RenderDevice:Filter;

import std;

export namespace PonyEngine::RenderDevice
{
	/// @brief Filter type.
	enum class Filter : std::uint8_t
	{
		Nearest,
		Linear
	};
}

namespace PonyEngine::RenderDevice
{
	constexpr std::array<std::string_view, 2> FilterNames
	{
		"Nearest",
		"Linear"
	};
}

export
{
	PONY_ENUM_VALUE_FORMATTER(PonyEngine::RenderDevice::Filter, PonyEngine::RenderDevice::FilterNames)
}
