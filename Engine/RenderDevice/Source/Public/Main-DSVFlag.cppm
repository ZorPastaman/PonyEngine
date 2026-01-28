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
	enum class DSVFlag : std::uint8_t
	{
		None = 0,
		DepthReadOnly = 1 << 0,
		StencilReadOnly = 1 << 1,
		All = (1 << 2) - 1
	};

	PONY_ENUM_MASK_FEATURES(DSVFlag)
}
