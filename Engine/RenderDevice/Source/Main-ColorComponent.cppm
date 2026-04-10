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

export module PonyEngine.RenderDevice:ColorComponent;

import std;

export namespace PonyEngine::RenderDevice
{
	/// @brief Color component.
	enum class ColorComponent : std::uint8_t
	{
		Red,
		Green,
		Blue,
		Alpha
	};

	/// @brief Color component mask.
	enum class ColorComponentMask : std::uint8_t
	{
		None = 0,
		Red = 1 << 0,
		Green = 1 << 1,
		Blue = 1 << 2,
		Alpha = 1 << 3,
		All = (1 << 4) - 1
	};

	PONY_ENUM_VALUE_MASK_FEATURES(ColorComponent, ColorComponentMask)
}

namespace PonyEngine::RenderDevice
{
	/// @brief Color component names.
	constexpr std::array<std::string_view, 4> ColorComponentNames
	{
		"Red",
		"Green",
		"Blue",
		"Alpha"
	};
}

export
{
	PONY_ENUM_VALUE_MASK_FORMATTER(PonyEngine::RenderDevice::ColorComponent, PonyEngine::RenderDevice::ColorComponentMask, PonyEngine::RenderDevice::ColorComponentNames)
}
