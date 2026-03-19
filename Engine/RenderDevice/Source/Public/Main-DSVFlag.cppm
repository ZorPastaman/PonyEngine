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

export module PonyEngine.RenderDevice:DSVFlag;

import std;

export namespace PonyEngine::RenderDevice
{
	/// @brief Depth stencil view flags.
	enum class DSVFlag : std::uint8_t
	{
		None = 0,
		DepthReadOnly = 1 << 0,
		StencilReadOnly = 1 << 1,
		All = (1 << 2) - 1
	};

	PONY_ENUM_MASK_FEATURES(DSVFlag)
}

namespace PonyEngine::RenderDevice
{
	/// @brief Depth stencil view flag names.
	constexpr std::array<std::string_view, 2> DSVFlagNames
	{
		"DepthReadOnly",
		"StencilReadOnly"
	};
}

export
{
	PONY_ENUM_MASK_FORMATTER(PonyEngine::RenderDevice::DSVFlag, PonyEngine::RenderDevice::DSVFlagNames)
}
