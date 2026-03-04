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

export module PonyEngine.RenderDevice:ShaderType;

import std;

export namespace PonyEngine::RenderDevice
{
	enum class GraphicsShaderType : std::uint8_t
	{
		Amplification,
		Mesh,
		Pixel
	};

	enum class GraphicsShaderTypeMask : std::uint8_t
	{
		None = 0,
		Amplification = 1 << 0,
		Mesh = 1 << 1,
		Pixel = 1 << 2,
		All = (1 << 3) - 1
	};

	PONY_ENUM_VALUE_MASK_FEATURES(GraphicsShaderType, GraphicsShaderTypeMask)
}
