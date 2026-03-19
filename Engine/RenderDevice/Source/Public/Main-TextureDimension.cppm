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

export module PonyEngine.RenderDevice:TextureDimension;

import std;

export namespace PonyEngine::RenderDevice
{
	/// @brief Texture dimension.
	enum class TextureDimension : std::uint8_t
	{
		Texture1D,
		Texture2D,
		Texture3D
	};

	/// @brief Texture dimension mask.
	enum class TextureDimensionMask : std::uint8_t
	{
		None = 0,
		Texture1D = 1 << 0,
		Texture2D = 1 << 1,
		Texture3D = 1 << 2,
		All = (1 << 3) - 1
	};

	PONY_ENUM_VALUE_MASK_FEATURES(TextureDimension, TextureDimensionMask)
}

namespace PonyEngine::RenderDevice
{
	/// @brief Texture dimension names.
	constexpr std::array<std::string_view, 3> TextureDimensionNames
	{
		"Texture1D",
		"Texture2D",
		"Texture3D"
	};
}

export
{
	PONY_ENUM_VALUE_MASK_FORMATTER(PonyEngine::RenderDevice::TextureDimension, PonyEngine::RenderDevice::TextureDimensionMask, PonyEngine::RenderDevice::TextureDimensionNames)
}
