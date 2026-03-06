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

export module PonyEngine.RenderDevice:SwapChainEffect;

import std;

export namespace PonyEngine::RenderDevice
{
	/// @brief Swap chain effect.
	enum class SwapChainEffect : std::uint8_t
	{
		FlipDiscard,
		FlipSequential
	};

	/// @brief Swap chain effect mask.
	enum class SwapChainEffectMask : std::uint8_t
	{
		None = 0,
		FlipDiscard = 1 << 0,
		FlipSequential = 1 << 1,
		All = (1 << 2) - 1
	};

	PONY_ENUM_VALUE_MASK_FEATURES(SwapChainEffect, SwapChainEffectMask)
}

namespace PonyEngine::RenderDevice
{
	/// @brief Swap chain effect names.
	constexpr std::array<std::string_view, 2> SwapChainEffectNames
	{
		"FlipDiscard",
		"FlipSequential"
	};
}

export
{
	PONY_ENUM_VALUE_MASK_FORMATTER(PonyEngine::RenderDevice::SwapChainEffect, PonyEngine::RenderDevice::SwapChainEffectMask, PonyEngine::RenderDevice::SwapChainEffectNames)
}
