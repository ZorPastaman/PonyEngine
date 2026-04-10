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

export module PonyEngine.RenderDevice:TextureFlag;

import std;

export namespace PonyEngine::RenderDevice
{
	/// @brief Texture flags.
	enum class TextureFlag : std::uint8_t
	{
		None = 0,
		SRGB = 1 << 0,
		All = (1 << 1) - 1
	};

	PONY_ENUM_MASK_FEATURES(TextureFlag)
}

namespace PonyEngine::RenderDevice
{
	/// @brief Texture flag names.
	constexpr std::array<std::string_view, 1> TextureFlagNames
	{
		"SRGB"
	};
}

export
{
	PONY_ENUM_MASK_FORMATTER(PonyEngine::RenderDevice::TextureFlag, PonyEngine::RenderDevice::TextureFlagNames)
}
