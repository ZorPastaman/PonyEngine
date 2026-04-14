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

export module PonyEngine.RenderDevice:SwapChainFlag;

import std;

export namespace PonyEngine::RenderDevice
{
	/// @brief Swap chain flag.
	enum class SwapChainFlag : std::uint8_t
	{
		None = 0,
		SRGB = 1 << 0,
		All = (1 << 1) - 1
	};

	PONY_ENUM_MASK_FEATURES(SwapChainFlag)
}

namespace PonyEngine::RenderDevice
{
	/// @brief Swap chain flag names.
	constexpr std::array<std::string_view, 1> SwapChainFlagNames
	{
		"SRGB"
	};
}

export
{
	PONY_ENUM_MASK_FORMATTER(PonyEngine::RenderDevice::SwapChainFlag, PonyEngine::RenderDevice::SwapChainFlagNames)
}
