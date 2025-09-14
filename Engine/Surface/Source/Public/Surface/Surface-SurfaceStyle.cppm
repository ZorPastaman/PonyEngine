/***************************************************
 * MIT License                                     *
 *                                                 *
 * Copyright (c) 2023-present Vladimir Popov       *
 *                                                 *
 * Email: zor1994@gmail.com                        *
 * Repo: https://github.com/ZorPastaman/PonyEngine *
 ***************************************************/

module;

#include "PonyEngine/Utility/Enum.h"

export module PonyEngine.Surface:SurfaceStyle;

import std;

namespace PonyEngine::Surface
{
	constexpr std::array<std::string_view, 7> SurfaceStyleNames
	{
		"Border"
		"Title"
		"Close"
		"Maximize"
		"Minimize"
		"Resizable"
		"AlwaysOnTop"
	};
}

export namespace PonyEngine::Surface
{
	enum class SurfaceStyle : std::uint8_t
	{
		None = 0,
		Border = 1 << 0,
		Title = 1 << 1,
		Close = 1 << 2,
		Maximize = 1 << 3,
		Minimize = 1 << 4,
		Resizable = 1 << 5,
		AlwaysOnTop = 1 << 6,
		All = Border | Title | Close | Maximize | Minimize | Resizable | AlwaysOnTop
	};

	ENUM_MASK_FEATURES(SurfaceStyle, SurfaceStyleNames)
}

export
{
	ENUM_MASK_FORMATTER(PonyEngine::Surface, SurfaceStyle)
}
