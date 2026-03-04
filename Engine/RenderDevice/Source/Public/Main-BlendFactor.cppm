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

export module PonyEngine.RenderDevice:BlendFactor;

import std;

export namespace PonyEngine::RenderDevice
{
	/// @brief Blend factor.
	enum class BlendFactor : std::uint8_t
	{
		Zero,
		One,
		SourceColor,
		OneMinusSourceColor,
		DestinationColor,
		OneMinusDestinationColor,
		SourceAlpha,
		OneMinusSourceAlpha,
		DestinationAlpha,
		OneMinusDestinationAlpha,
		SourceAlphaSaturate,
		Source1Color,
		OneMinusSource1Color,
		Source1Alpha,
		OneMinusSource1Alpha,
		Constant,
		OneMinusConstant
	};
}

namespace PonyEngine::RenderDevice
{
	/// @brief Blend factor names.
	constexpr std::array<std::string_view, 17> BlendFactorNames
	{
		"Zero",
		"One",
		"SourceColor",
		"OneMinusSourceColor",
		"DestinationColor",
		"OneMinusDestinationColor",
		"SourceAlpha",
		"OneMinusSourceAlpha",
		"DestinationAlpha",
		"OneMinusDestinationAlpha",
		"SourceAlphaSaturate",
		"Source1Color",
		"OneMinusSource1Color",
		"Source1Alpha",
		"OneMinusSource1Alpha",
		"Constant",
		"OneMinusConstant"
	};
}

export
{
	PONY_ENUM_VALUE_FORMATTER(PonyEngine::RenderDevice::BlendFactor, PonyEngine::RenderDevice::BlendFactorNames)
}
