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

export module PonyEngine.RenderDevice:SwapChainScaling;

import std;

export namespace PonyEngine::RenderDevice
{
	enum class SwapChainScaling : std::uint8_t
	{
		NoScaling,
		Stretch,
		StretchAspectRatio
	};

	enum class SwapChainScalingMask : std::uint8_t
	{
		None = 0,
		NoScaling = 1 << 0,
		Stretch = 1 << 1,
		StretchAspectRatio = 1 << 2,
		All = (1 << 3) - 1
	};

	PONY_ENUM_VALUE_MASK_FEATURES(SwapChainScaling, SwapChainScalingMask)
}
