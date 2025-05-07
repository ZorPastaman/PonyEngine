/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyBase/Utility/Enum.h"

export module PonyEngine.Render:TextureDimension;

import <algorithm>;
import <array>;
import <bit>;
import <cstddef>;
import <cstdint>;
import <ostream>;
import <span>;
import <string>;
import <string_view>;
import <type_traits>;

namespace PonyEngine::Render
{
	/// @brief Texture dimension names.
	constexpr std::array<std::string_view, 8> TextureDimensionNames
	{
		"Texture1D",
		"Texture2D",
		"Texture3D",
		"TextureCube",
		"Texture1DArray",
		"Texture2DArray",
		"TextureCubeArray",
		"Unknown"
	};
}

export namespace PonyEngine::Render
{
	/// @brief Texture dimensions.
	enum class TextureDimension : std::uint8_t
	{
		Texture1D,
		Texture2D,
		Texture3D,
		TextureCube,
		Texture1DArray,
		Texture2DArray,
		TextureCubeArray
	};

	/// @brief Texture dimension mask.
	enum class TextureDimensionMask : std::uint8_t
	{
		None = 0,
		Texture1D = 1 << 0,
		Texture2D = 1 << 1,
		Texture3D = 1 << 2,
		TextureCube = 1 << 3,
		Texture1DArray = 1 << 4,
		Texture2DArray = 1 << 5,
		TextureCubeArray = 1 << 6,
		All = Texture1D | Texture2D | Texture3D | TextureCube | Texture1DArray | Texture2DArray | TextureCubeArray
	};

	ENUM_VALUE_MASK_FEATURES(TextureDimension, TextureDimensionNames, TextureDimensionMask)
}
