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

export module PonyEngine.RenderDevice:FillMode;

import std;

export namespace PonyEngine::RenderDevice
{
	/// @brief Fill mode.
	enum class FillMode : std::uint8_t
	{
		Solid,
		Wireframe
	};
}

namespace PonyEngine::RenderDevice
{
	/// @brief Fill mode names.
	constexpr std::array<std::string_view, 2> FillModeNames
	{
		"Solid",
		"Wireframe"
	};
}

export
{
	PONY_ENUM_VALUE_FORMATTER(PonyEngine::RenderDevice::FillMode, PonyEngine::RenderDevice::FillModeNames)
}
