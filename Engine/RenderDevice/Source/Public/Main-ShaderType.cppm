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
	/// @brief Graphics shader type.
	enum class GraphicsShaderType : std::uint8_t
	{
		Amplification,
		Mesh,
		Pixel
	};

	/// @brief Graphics shader type mask.
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

namespace PonyEngine::RenderDevice
{
	/// @brief Graphics shader type names.
	constexpr std::array<std::string_view, 3> GraphicsShaderTypeNames
	{
		"Amplification",
		"Mesh",
		"Pixel"
	};
}

export
{
	PONY_ENUM_VALUE_MASK_FORMATTER(PonyEngine::RenderDevice::GraphicsShaderType, PonyEngine::RenderDevice::GraphicsShaderTypeMask, PonyEngine::RenderDevice::GraphicsShaderTypeNames)
}
