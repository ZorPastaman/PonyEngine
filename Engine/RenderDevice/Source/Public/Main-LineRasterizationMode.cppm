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

export module PonyEngine.RenderDevice:LineRasterizationMode;

import std;

export namespace PonyEngine::RenderDevice
{
	/// @brief Line rasterization mode.
	enum class LineRasterizationMode : std::uint8_t
	{
		Aliased,
		AlphaAntialiased,
		QuadrilateralWide,
		QuadrilateralNarrow
	};

	/// @brief Line rasterization mode mask.
	enum class LineRasterizationModeMask : std::uint8_t
	{
		None = 0,
		Aliased = 1 << 0,
		AlphaAntialiased = 1 << 1,
		QuadrilateralWide = 1 << 2,
		QuadrilateralNarrow = 1 << 3,
		All = (1 << 4) - 1
	};

	PONY_ENUM_VALUE_MASK_FEATURES(LineRasterizationMode, LineRasterizationModeMask)
}

namespace PonyEngine::RenderDevice
{
	/// @brief Line rasterization mode names.
	constexpr std::array<std::string_view, 4> LineRasterizationModeNames
	{
		"Aliased",
		"AlphaAntialiased",
		"QuadrilateralWide",
		"QuadrilateralNarrow"
	};
}

export
{
	PONY_ENUM_VALUE_MASK_FORMATTER(PonyEngine::RenderDevice::LineRasterizationMode, PonyEngine::RenderDevice::LineRasterizationModeMask, PonyEngine::RenderDevice::LineRasterizationModeNames)
}
