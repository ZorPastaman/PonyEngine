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

export module PonyEngine.RenderDevice:PipelineLayoutFlag;

import std;

export namespace PonyEngine::RenderDevice
{
	enum class PipelineLayoutFlag : std::uint8_t
	{
		None = 0,
		DirectlyIndexed = 1 << 0,
		All = (1 << 1) - 1
	};

	PONY_ENUM_MASK_FEATURES(PipelineLayoutFlag)
}
