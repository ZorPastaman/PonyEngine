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

export module PonyEngine.RenderDevice:BufferUsage;

import std;

export namespace PonyEngine::Render
{
	enum class BufferUsage : std::uint8_t
	{
		None = 0,
		ShaderResource = 1 << 0,
		UnorderedAccess = 1 << 1,
		All = (1 << 2) - 1
	};

	PONY_ENUM_MASK_FEATURES(BufferUsage)
}
