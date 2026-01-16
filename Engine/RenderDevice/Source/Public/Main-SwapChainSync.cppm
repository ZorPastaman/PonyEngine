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

export module PonyEngine.RenderDevice:SwapChainSync;

import std;

export namespace PonyEngine::RenderDevice
{
	enum class SwapChainSync : std::uint8_t
	{
		NoSync,
		FastSync,
		FullSync,
		FullSyncHalf,
		FullSyncThird,
		FullSyncFourth
	};

	enum class SwapChainSyncMask : std::uint8_t
	{
		None = 0,
		NoSync = 1 << 0,
		FastSync = 1 << 1,
		FullSync = 1 << 2,
		FullSyncHalf = 1 << 3,
		FullSyncThird = 1 << 4,
		FullSyncFourth = 1 << 5,
		All = (1 << 6) - 1
	};

	PONY_ENUM_VALUE_MASK_FEATURES(SwapChainSync, SwapChainSyncMask)
}
