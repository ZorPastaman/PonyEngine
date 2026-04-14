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

export module PonyEngine.RenderDevice:BlendMode;

import std;

export namespace PonyEngine::RenderDevice
{
	/// @brief Blend mode.
	enum class BlendMode : std::uint8_t
	{
		Arithmetic,
		Logic
	};

	/// @brief Blend mode mask.
	enum class BlendModeMask : std::uint8_t
	{
		None = 0,
		Arithmetic = 1 << 0,
		Logic = 1 << 1,
		All = (1 << 2) - 1
	};

	PONY_ENUM_VALUE_MASK_FEATURES(BlendMode, BlendModeMask)
}

namespace PonyEngine::RenderDevice
{
	/// @brief Blend mode names.
	constexpr std::array<std::string_view, 2> BlendModeNames
	{
		"Arithmetic",
		"Logic"
	};
}

export
{
	PONY_ENUM_VALUE_MASK_FORMATTER(PonyEngine::RenderDevice::BlendMode, PonyEngine::RenderDevice::BlendModeMask, PonyEngine::RenderDevice::BlendModeNames)
}
