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

export module PonyEngine.RenderDevice:SwapChainAlphaMode;

import std;

export namespace PonyEngine::Render
{
	enum class SwapChainAlphaMode : std::uint8_t
	{
		Ignore,
		Straight,
		Premultiplied,
		Inherit
	};

	enum class SwapChainAlphaModeMask : std::uint8_t
	{
		None = 0,
		Ignore = 1 << 0,
		Straight = 1 << 1,
		Premultiplied = 1 << 2,
		Inherit = 1 << 3,
		All = (1 << 4) - 1
	};

	PONY_ENUM_VALUE_MASK_FEATURES(SwapChainAlphaMode, SwapChainAlphaModeMask)
}
