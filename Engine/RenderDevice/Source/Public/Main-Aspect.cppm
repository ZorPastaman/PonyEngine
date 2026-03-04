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

export module PonyEngine.RenderDevice:Aspect;

import std;

export namespace PonyEngine::RenderDevice
{
	/// @brief Texture aspect.
	enum class Aspect : std::uint8_t
	{
		Color,
		Depth,
		Stencil
	};

	/// @brief Texture aspect mask.
	enum class AspectMask : std::uint8_t
	{
		None = 0,
		Color = 1 << 0,
		Depth = 1 << 1,
		Stencil = 1 << 2,
		All = (1 << 3) - 1
	};

	PONY_ENUM_VALUE_MASK_FEATURES(Aspect, AspectMask)
}

namespace PonyEngine::RenderDevice
{
	/// @brief Texture aspect names.
	constexpr std::array<std::string_view, 3> AspectNames
	{
		"Color",
		"Depth",
		"Stencil"
	};
}

export
{
	PONY_ENUM_VALUE_FORMATTER(PonyEngine::RenderDevice::Aspect, PonyEngine::RenderDevice::AspectNames)
	PONY_ENUM_MASK_FORMATTER(PonyEngine::RenderDevice::AspectMask, PonyEngine::RenderDevice::AspectNames)
}
