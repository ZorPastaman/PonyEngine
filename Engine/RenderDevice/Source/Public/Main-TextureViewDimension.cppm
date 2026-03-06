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

export module PonyEngine.RenderDevice:TextureViewDimension;

import std;

export namespace PonyEngine::RenderDevice
{
	/// @brief Texture view dimension.
	enum class TextureViewDimension : std::uint8_t
	{
		Texture1D,
		Texture2D,
		Texture3D,
		TextureCube
	};

	/// @brief Texture view dimension mask.
	enum class TextureViewDimensionMask : std::uint8_t
	{
		None = 0,
		Texture1D = 1 << 0,
		Texture2D = 1 << 1,
		Texture3D = 1 << 2,
		TextureCube = 1 << 3,
		All = (1 << 4) - 1
	};

	PONY_ENUM_VALUE_MASK_FEATURES(TextureViewDimension, TextureViewDimensionMask)
}

namespace PonyEngine::RenderDevice
{
	/// @brief Texture view dimension names.
	constexpr std::array<std::string_view, 4> TextureViewDimensionNames
	{
		"Texture1D",
		"Texture2D",
		"Texture3D",
		"TextureCube"
	};
}

export 
{
	PONY_ENUM_VALUE_MASK_FORMATTER(PonyEngine::RenderDevice::TextureViewDimension, PonyEngine::RenderDevice::TextureViewDimensionMask, PonyEngine::RenderDevice::TextureViewDimensionNames)
}
